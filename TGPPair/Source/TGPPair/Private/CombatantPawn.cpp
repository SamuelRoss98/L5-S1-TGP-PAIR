// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "CombatDecisionInterface.h"
#include "InventoryComponent.h"

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
	if (Controller == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid controller passed to ACombatantPawn on initialization"))
			return false;
	}

	CharacterBaseValues = Character;
	CurrentStats = CharacterBaseValues.Stats;

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

	//Controller->MakeDescision();
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

void ACombatantPawn::SetCurrentAction(FCombatAction newAction)
{
	CurrentAction = newAction;

	FString targetIndex = FString::FromInt(CurrentAction.TargetIndex);
	FString type = FString::FromInt((int32)CurrentAction.ActionType);

	UE_LOG(LogTemp, Warning, TEXT("New action set. [Type: %s, Target: %s]"), *type, *targetIndex)
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

