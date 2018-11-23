// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameModeBase.h"

#include "Combatant.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"

ACombatGameModeBase::ACombatGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACombatGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SpawnCombatants();
}

// Called every frame
void ACombatGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bActionInProgress)
	{
		StartNextTurn();
	}
}

// Spawns the combatants.
void ACombatGameModeBase::SpawnCombatants()
{
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRot = FRotator::ZeroRotator;

	ACombatant * NewCombatant = nullptr;

	TArray<FCharacterProperties*> OutRows;
	CombatantDataTable->GetAllRows<FCharacterProperties>("GENERAL", OutRows);

	SpawnCombatant(SpawnPointA, EnemyRotation, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], true, false);		// Friendly AI
	SpawnCombatant(SpawnPointB, EnemyRotation, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], true, true);		// Player
	SpawnCombatant(SpawnPointC, EnemyRotation, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], true, false);		// Friendly AI
	SpawnCombatant(SpawnPointD, FRotator::ZeroRotator, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], false, false);		// Enemy AI
	SpawnCombatant(SpawnPointE, FRotator::ZeroRotator, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], false, false);		// Enemy AI
	SpawnCombatant(SpawnPointF, FRotator::ZeroRotator, *OutRows[FMath::RandRange(0, OutRows.Num() - 1)], false, false);		// Enemy AI
}

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

// Starts the turn of the next combatant.
void ACombatGameModeBase::StartNextTurn()
{
	if (!IsRoundComplete())
	{
		GetNextToAct()->StartTurn(AllCombatants);
		bActionInProgress = true;
	}

	else
	{
		// TODO: Start new round.
	}
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

