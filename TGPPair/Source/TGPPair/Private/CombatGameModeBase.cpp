// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameModeBase.h"

#include "Combatant.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"

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

	SpawnCombatant(SpawnPointA, *OutRows[0], true, false);		// Friendly AI
	SpawnCombatant(SpawnPointB, *OutRows[0], true, true);		// Player
	SpawnCombatant(SpawnPointC, *OutRows[0], true, false);		// Friendly AI
	SpawnCombatant(SpawnPointD, *OutRows[0], false, false);		// Enemy AI
	SpawnCombatant(SpawnPointE, *OutRows[0], false, false);		// Enemy AI
	SpawnCombatant(SpawnPointF, *OutRows[0], false, false);		// Enemy AI
}

void ACombatGameModeBase::SpawnCombatant(FVector SpawnPoint, FCharacterProperties Character, bool bFriendly, bool bPlayer)
{
	ACombatant * NewCombatant = nullptr;
	FActorSpawnParameters SpawnParams;
	FRotator SpawnRot = FRotator::ZeroRotator;

	// Spawn.
	NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(CombatantClass, &SpawnPoint, &SpawnRot, SpawnParams));
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

