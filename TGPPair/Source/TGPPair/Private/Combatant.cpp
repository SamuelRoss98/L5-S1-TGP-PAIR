// Fill out your copyright notice in the Description page of Project Settings.

#include "Combatant.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

#include "CombatantAIController.h"
#include "CombatantPlayerController.h"
#include "CombatGameModeBase.h"

// Sets default values
ACombatant::ACombatant()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("CombatantStaticMesh");
	InteractionPoint = CreateDefaultSubobject<USceneComponent>("InteractionPoint");

	RootComponent = Mesh;
	InteractionPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACombatant::BeginPlay()
{
	Super::BeginPlay();
	OriginalTransform = GetActorTransform();
}

// Called every frame
void ACombatant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACombatant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Initialize this combatant with a CharacterProperties structure.
void ACombatant::LoadCombatant(FCharacterProperties Properties, bool bPlayer, bool bFriendly)
{
	CharacterName = Properties.CharacterName;
	BaseCombatAttributes = Properties.CombatAttributes;
	CurrentCombatAttributes = BaseCombatAttributes;
		
	bPlayerTeam = bFriendly;

	if (!bPlayerTeam)
		SpawnCombatantController(bPlayer);
	else
	{
		CombatantController = Cast<ACombatantPlayerController>(GetWorld()->GetFirstPlayerController());

		if (!CombatantController)
		{
			UE_LOG(LogTemp, Error, TEXT("Player controlled combatant failed to find the player controller."))
		}
	}
}

// Prepares the combatant for a new round.
void ACombatant::PrepareForNewRound()
{
	bHasTakenTurn = false;
}

// Ends this combatants turn.
void ACombatant::EndTurn()
{
	bHasTakenTurn = true;
	ACombatGameModeBase * GameMode = Cast<ACombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->NotifyEndTurn();
}

// Returns the combatants action for a turn.
FCombatantAction ACombatant::GetActionForTurn()
{
	return CombatantController->GetAction();
}

// Returns the interaction point Transform.
FTransform ACombatant::GetInteractionTransform() const
{
	return InteractionPoint->GetComponentTransform();
}

// Returns the combatants resting transform.
FTransform ACombatant::GetRestingTransform() const
{
	return OriginalTransform;
}

// Return the character name of this combatant.
FString ACombatant::GetCharacterName() const
{
	return CharacterName;
}

// Returns the combatants current combat attributes.
FCombatAttribute ACombatant::GetCurrentCombatAttributes() const
{
	return CurrentCombatAttributes;
}

// Returns the combatants base combat attributes.
FCombatAttribute ACombatant::GetBaseCombatAttributes() const
{
	return BaseCombatAttributes;
}

// Returns true if the combatant has already acted this turn.
bool ACombatant::HasTakenTurn() const
{
	return bHasTakenTurn;
}

// Returns true if the combatant is on the players team.
bool ACombatant::IsOnPlayerTeam() const
{
	return bPlayerTeam;
}

// Returns true while this combatant is taking its turn.
bool ACombatant::IsTurnInProgress() const
{
	return bActionInProgress;
}

// Attacks a combatant.
void ACombatant::AttackCombatant(ACombatant * CombatantToAttack)
{
	UE_LOG(LogTemp, Warning, TEXT("%s attacks %s"), *(CharacterName), *(CombatantToAttack->GetCharacterName()))
	SetActorLocation(CombatantToAttack->GetInteractionTransform().GetLocation());
	SetActorRotation(CombatantToAttack->GetInteractionTransform().GetRotation());
}

// Spawn the controller for this Combatant.
void ACombatant::SpawnCombatantController(bool bPlayer)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.OverrideLevel = GetLevel();

	if(bPlayer)
		CombatantController = GetWorld()->SpawnActor<ICombatantDecisionMaking>(CombatantPlayerControllerClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	else
		CombatantController = GetWorld()->SpawnActor<ICombatantDecisionMaking>(CombatantAIControllerClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (CombatantController != nullptr)
		Cast<AController>(CombatantController)->Possess(this);
}

// Returns the action this combatant has decided to carry out this turn.
const FCombatantAction ACombatant::GetTurnAction() const
{
	return TurnAction;
}

// Set the action this combatant next carry out.
void ACombatant::SetTurnAction(const FCombatantAction Action)
{
	TurnAction = Action;
}
