// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "CombatDecisionInterface.h"
#include "CombatGameModeBase.h"
#include "Engine/World.h"
#include "InventoryComponent.h"
#include "TGPPairGameInstance.h"
#include "CombatGameModeBase.h"

// Sets default values
ACombatantPawn::ACombatantPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	InteractionTransform = CreateDefaultSubobject<USceneComponent>("InteractionTransform");
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	RootComponent = Mesh;
	InteractionTransform->SetupAttachment(Mesh);

	AddOwnedComponent(Inventory);
}

// Called when the game starts or when spawned
void ACombatantPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACombatantPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatantPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Initializes this combatant.
bool ACombatantPawn::Initialize(FNamedStatPack Character, bool bPlayer, ICombatDecisionInterface * CombatantController)
{
	Controller = CombatantController;
	bIsPlayer = bPlayer;
	CharacterBaseValues = Character;
	CurrentStats = CharacterBaseValues.Stats;

	OriginalLocation = GetActorTransform();

	// Check the controller.
	if (Controller == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid controller passed to ACombatantPawn on initialization"))
			return false;
	}
	
	// If we are the player grab our name from the game instance.
	if (bIsPlayer)
	{
		UTGPPairGameInstance* TGPGI = nullptr;
		TGPGI = Cast<UTGPPairGameInstance>(GetGameInstance());
		if (TGPGI != nullptr)
		{
			CharacterBaseValues.Name = TGPGI->GetPlayerName();
			CharacterBaseValues.Stats = TGPGI->GetPlayerCurrentBaseStats();
			CurrentStats = CharacterBaseValues.Stats;
			FString dmg = FString::FromInt(CurrentStats.MeleeAttack);
			UE_LOG(LogTemp, Error, TEXT("Player melee damage: %s"), *dmg)
		}
	}

	// Enemy only.
	else
	{
		LoadEnemyCombatantUI();
	}

	Inventory->AddItem("Health Potion", 2);
	Inventory->AddItem("Health Potion", 1);
	Inventory->AddItem("Mana Potion", 2);
	Inventory->AddItem("Super Mana Potion", 1);

	return true;
}

// Starts the descision process for this combatant.
void ACombatantPawn::MakeCombatDescision()
{
	if (Controller == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Combatant has no controller."))
			return;
	}

	Controller->MakeDescision();
}

// Called by blueprint to end the combatants turn.
UFUNCTION(BlueprintCallable)
void ACombatantPawn::EndTurn()
{
	bTurnTaken = true;
	ACombatGameModeBase* CombatGameMode = nullptr;
	CombatGameMode = Cast<ACombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if (CombatGameMode != nullptr)
		CombatGameMode->SimulateNextAction();
}

// Returns the NamedStatPack this character was created with.
FNamedStatPack ACombatantPawn::GetBaseCharacter() const
{
	return CharacterBaseValues;
}

// Returns the current stats of the combatant.
FStatPack ACombatantPawn::GetStats() const
{
	return CurrentStats;
}

// Setter for current action.
void ACombatantPawn::SetCurrentAction(FCombatAction newAction)
{
	CurrentAction = newAction;

	FString targetIndex = FString::FromInt(CurrentAction.TargetIndex);
	FString type = FString::FromInt((int32)CurrentAction.ActionType);
	FString dataName = newAction.ActionData.Name;
}

// Getter for current action.
FCombatAction ACombatantPawn::GetCurrentAction() const
{
	return CurrentAction;
}

// Flag whether this combatant has taken their turn or not.
void ACombatantPawn::SetTurnTaken(bool setting)
{
	bTurnTaken = setting;
}

// Returns true if this combatant has taken their turn.
bool ACombatantPawn::GetTurnTaken() const
{
	return bTurnTaken;
}

// Returns true if this combatant is the player.
bool ACombatantPawn::IsPlayer() const
{
	return bIsPlayer;
}

// Returns true if this combatant is dead.
bool ACombatantPawn::IsDead() const
{
	return bIsDead;
}

// Returns the combat log description of the current action.
FString ACombatantPawn::GetActionDescription(ACombatantPawn* Player, TArray<ACombatantPawn*> Enemies)
{
	FString MyName = GetBaseCharacter().Name;

	switch (CurrentAction.ActionType)
	{
	case ECombatantActionType::Attack:
		return GetAttackActionDescription(Player, Enemies);
	case ECombatantActionType::Item:
		return MyName + " uses a " + CurrentAction.ActionData.Name + ".";
	case ECombatantActionType::Run:
		return MyName + " flees the battle.";
	default:
		return "Invalid action.";
	}

	return "Invalid action.";
}

// Generates a description for an attack action.
FString ACombatantPawn::GetAttackActionDescription(ACombatantPawn* Player, TArray<ACombatantPawn*> Enemies)
{
	// Player attacking enemies.
	if (bIsPlayer)
		return Player->GetBaseCharacter().Name + " attacks " + Enemies[CurrentAction.TargetIndex]->GetBaseCharacter().Name + ".";

	// Enemies attacking player.
	else
		return CharacterBaseValues.Name + " attacks " + Player->GetBaseCharacter().Name;
}

// Returns the interaction transform of this combatant.
FTransform ACombatantPawn::GetInteractionTransform() const
{
	if (InteractionTransform != nullptr)
		return InteractionTransform->GetComponentTransform();

	return FTransform();
}

// Returns the resting location/rotation of this combatant.
FTransform ACombatantPawn::GetRestingTransform() const
{
	return OriginalLocation;
}

// Returns the target of the current action.
ACombatantPawn* ACombatantPawn::GetActionTargetCombatant()
{
	if (CurrentAction.ActionType == ECombatantActionType::Item)
		return this;

	ACombatGameModeBase* CombatGameMode = nullptr;
	CombatGameMode = Cast<ACombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if (CombatGameMode == nullptr)
		return nullptr;

	return CombatGameMode->GetActionTarget(bIsPlayer, CurrentAction);
}

// Applies the effect to an action to this combatants stats.
void ACombatantPawn::ApplyAction()
{
	ACombatantPawn* Target = GetActionTargetCombatant();
	if (Target == nullptr)
		return;
	
	switch (CurrentAction.ActionType)
	{
	case ECombatantActionType::Attack:
		Target->ApplyDamage(CurrentAction.ActionData.Stats);
		break;
	case ECombatantActionType::Item:
		Target->ApplyItem(CurrentAction.ActionData.Stats);
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Attempted to apply unrecognised action type."))
		break;
	}
}

// Applies damage to combatant.
void ACombatantPawn::ApplyDamage(FStatPack DamageStatPack)
{
	// Calculate health damage.
	int MeleeDamage = FMath::Clamp(DamageStatPack.MeleeAttack - CurrentStats.MeleeDefense, 0, DamageStatPack.MeleeAttack);
	int MagicDamage = FMath::Clamp(DamageStatPack.MagicAttack - CurrentStats.MagicDefense, 0, DamageStatPack.MagicAttack);
	int HealthDamage = MeleeDamage + MagicDamage;

	FString MeleeStr = FString::FromInt(MeleeDamage);
	FString MagicStr = FString::FromInt(MagicDamage);
	UE_LOG(LogTemp, Error, TEXT("Melee damage: %s, Magic damage: %s."), *MeleeStr, *MagicStr)

	// Apply stat changes.
	CurrentStats.Health -= HealthDamage;
	CheckForDeath();
}

// Applies an item to combatant.
void ACombatantPawn::ApplyItem(FStatPack ItemStatPack)
{
	// Apply/clamp health.
	CurrentStats.Health += ItemStatPack.Health;
	if (CurrentStats.Health > CharacterBaseValues.Stats.Health)
		CurrentStats.Health = CharacterBaseValues.Stats.Health;
	
	// Potentially damaging items so check for death.
	if (CheckForDeath())
		return;

	// Apply/clamp mana.
	CurrentStats.Mana += ItemStatPack.Mana;
	if (CurrentStats.Mana > CharacterBaseValues.Stats.Mana)
		CurrentStats.Mana = CharacterBaseValues.Stats.Mana;

	// Other stats aren't clamped.
	CurrentStats.Charisma += ItemStatPack.Charisma;
	CurrentStats.Luck += ItemStatPack.Luck;
	CurrentStats.MagicAttack += ItemStatPack.MagicAttack;
	CurrentStats.MagicDefense += ItemStatPack.MagicDefense;
	CurrentStats.MeleeAttack += ItemStatPack.MeleeAttack;
	CurrentStats.MeleeDefense += ItemStatPack.MeleeDefense;
	CurrentStats.Speed += ItemStatPack.Speed;
}

// Checks if this combatants has run out of health.
bool ACombatantPawn::CheckForDeath()
{
	if (CurrentStats.Health <= 0)
	{
		CurrentStats.Health = 0;
		Death();
		return true;
	}

	return false;
}

// Handles combatant death.
void ACombatantPawn::Death()
{
	bIsDead = true;
	DeathEvent();
}