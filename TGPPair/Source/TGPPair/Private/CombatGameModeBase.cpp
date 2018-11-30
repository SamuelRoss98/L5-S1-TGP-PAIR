// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameModeBase.h"

#include "Combatant.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "CombatantPlayerController.h"

ACombatGameModeBase::ACombatGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACombatGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ...

	CombatantPlayerController = Cast<ACombatantPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!CombatantPlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Gamemode failed to find a combatant player controller"))
	}

	SpawnCombatants();
}

// Called every frame
void ACombatGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Run actions.
	if (bActionsInProgress)
		RunActions();

	// Check if actions are ready.
	else
	{
		if (bPlayerDecisionComplete)
			StartRoundActions();

		// Check if the player is done deciding.
		else
			if (CombatantPlayerController)
				bPlayerDecisionComplete = CombatantPlayerController->IsDecisionFinished();
	}
}

// Calls spawning code for all combatants in this battle.
void ACombatGameModeBase::SpawnCombatants()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRot = FRotator::ZeroRotator;

	ACombatant * NewCombatant = nullptr;

	TArray<FCharacterProperties*> OutRows;
	CombatantDataTable->GetAllRows<FCharacterProperties>("GENERAL", OutRows);

	SpawnCombatant(SpawnPointB, FRotator::ZeroRotator, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], true, true);		// Player
	SpawnCombatant(SpawnPointD, EnemyRotation, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], false, false);				// Enemy AI
	SpawnCombatant(SpawnPointE, EnemyRotation, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], false, false);				// Enemy AI
	SpawnCombatant(SpawnPointF, EnemyRotation, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], false, false);				// Enemy AI
}

// Spawns a single combatant.
void ACombatGameModeBase::SpawnCombatant(FVector SpawnPoint, FRotator SpawnRotation, FCharacterProperties Character, bool bFriendly, bool bPlayer)
{
	ACombatant * NewCombatant = nullptr;
	FActorSpawnParameters SpawnParams;

	// Spawn.
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPoint, &SpawnRotation, SpawnParams));
	if (NewCombatant)
	{
		NewCombatant->LoadCombatant(Character, bPlayer, bFriendly);
		AllCombatants.Add(NewCombatant);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load combatant."))
	}
}

// Starts the next combat round.
void ACombatGameModeBase::StartRound()
{
	if (CombatantPlayerController)
		CombatantPlayerController->StartCombatDecisions();
}

// Ends the current round.
void ACombatGameModeBase::EndRound()
{
	bActionsInProgress = false;
	bPlayerDecisionComplete = false;

	// Next round starts immediately.
	StartRound();
}

// Returns true if the round is complete.
bool ACombatGameModeBase::IsRoundComplete() const
{
	for (ACombatant* Combatant : AllCombatants)
		if (!Combatant->HasActedThisTurn())
			return false;

	return true;
}

// Return the next combatant to act based on their speed.
ACombatant * ACombatGameModeBase::GetNextToAct() const
{
	int HighestSpeed = -999;
	ACombatant * NextToAct = nullptr;

	for (ACombatant* Combatant : AllCombatants)
	{
		if (!Combatant->HasActedThisTurn())
		{
			int Speed = Combatant->GetCurrentCombatAttributes().Speed;
			if (Speed > HighestSpeed)
			{
				HighestSpeed = Speed;
				NextToAct = Combatant;
			}
		}
	}

	return NextToAct;
}

// Starts the process of carrying out the actions for the round.
void ACombatGameModeBase::StartRoundActions()
{
	bActionsInProgress = true;
}

// Main loop for actions logic.
void ACombatGameModeBase::RunActions()
{
	if (!bCombatantActing)
	{
		if (IsRoundComplete())
			EndRound();

		else
			StartNextTurn();
	}
}

// Starts the turn of the next combatant to carry out their action.
void ACombatGameModeBase::StartNextTurn()
{
	bCombatantActing = true;
	UE_LOG(LogTemp, Warning, TEXT("Next turn started"));
}