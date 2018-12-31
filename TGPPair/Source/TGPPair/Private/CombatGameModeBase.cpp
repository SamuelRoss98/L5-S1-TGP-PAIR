// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameModeBase.h"

#include "Engine/World.h"
#include "CombatantPawn.h"
#include "CombatDecisionInterface.h"
#include "CombatAIController.h"

// Called when the game starts or when spawned
void ACombatGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnCombatants();
}

// Called every frame
void ACombatGameModeBase::Tick(float DeltaTime)
{
}

// Resets the combatants ready for a new round.
void ACombatGameModeBase::ResetForNewRound()
{
	for (int i = 0; i < EnemyCombatants.Num(); ++i)
	{
		if (EnemyCombatants[i] != nullptr)
		{
			EnemyCombatants[i]->SetTurnTaken(false);
			EnemyCombatants[i]->MakeCombatDescision();
		}
	}

	if (PlayerCombatant != nullptr)
	{
		PlayerCombatant->SetTurnTaken(false);
		PlayerCombatant->MakeCombatDescision();
	}
}

// Returns the items data table.
UDataTable* ACombatGameModeBase::GetItemsData() const 
{
	return ItemsDataTable;
}

// Spawns combatants.
void ACombatGameModeBase::SpawnCombatants()
{
	// Check there are enough spawn locations given to spawn all combatants.
	if (EnemyCount + 1 > SpawnLocations.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("There are no enough spawn points to spawn the combatants."))
			return;
	}

	FVector SpawnLoc = FVector::ZeroVector;
	FRotator SpawnRot = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;

	// Spawn player.
	SpawnLoc = SpawnLocations[0];
	PlayerCombatant = Cast<ACombatantPawn>(GetWorld()->SpawnActor(CombatantClass, &SpawnLoc, &SpawnRot, SpawnParams));
	if (PlayerCombatant == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn the player combatant."))
			return;
	}
	GetWorld()->GetFirstPlayerController()->SetPawn(PlayerCombatant);
	if (!PlayerCombatant->Initialize(FNamedStatPack(), true, Cast<ICombatDecisionInterface>(GetWorld()->GetFirstPlayerController())))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to initialize the player combatant."))
			return;
	}

	// Spawn enemies.
	for (int i = 0; i < EnemyCount; ++i)
	{
		// Create the enemy combatant.
		ACombatantPawn* NewEnemy = nullptr;
		SpawnLoc = SpawnLocations[i + 1];
		NewEnemy = Cast<ACombatantPawn>(GetWorld()->SpawnActor(CombatantClass, &SpawnLoc, &SpawnRot, SpawnParams));
		if (NewEnemy == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn an enemy combatant."))
				return;
		}

		// Create the AI controller.
		ACombatAIController* Controller = nullptr;
		Controller = Cast<ACombatAIController>(GetWorld()->SpawnActor(AIClass, &SpawnLoc, &SpawnRot, SpawnParams));
		if (Controller == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn an enemy combatant AI controller."))
				return;
		}
		Controller->SetPawn(NewEnemy);

		// Init the enemy combatant.
		if (!NewEnemy->Initialize(FNamedStatPack(), false, Cast<ICombatDecisionInterface>(Controller)))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to initialize an enemy combatant."))
				return;
		}
		EnemyCombatants.Add(NewEnemy);
	}

	UE_LOG(LogTemp, Warning, TEXT("Combatants spawned successfully."))
		StartNewRound();
}
