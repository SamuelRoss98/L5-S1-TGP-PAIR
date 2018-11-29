// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CharacterProperties.h"

#include "CombatGameModeBase.generated.h"

class ACombatant;
class UDataTable;
class ACombatantPlayerController;

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACombatGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Call to alert the game mode that a turn is finished.
	void TurnFinished();

private:
	// Spawns the combatants.
	void SpawnCombatants();

	// Spawns a single combatant.
	void SpawnCombatant(FVector SpawnPoint, FRotator SpawnRotation, FCharacterProperties Character, bool bFriendly, bool bPlayer);

	// Starts the turn of the next combatant.
	void StartNextTurn();

	// Returns true if the round is complete.
	bool IsRoundComplete() const;

	// Return the next combatant to act based on their speed.
	ACombatant * GetNextToAct() const;

private:
	// Spawn points temporarily hardcoded.
	FVector SpawnPointA = FVector(250.0f, 550.0f, 0.0f);
	FVector SpawnPointB = FVector(0.0f, 550.0f, 0.0f);
	FVector SpawnPointC = FVector(-250.0f, 550.0f, 0.0f);
	FVector SpawnPointD = FVector(250.0f, -550.0f, 0.0f);
	FVector SpawnPointE = FVector(0.0f, -550.0f, 0.0f);
	FVector SpawnPointF = FVector(-250.0f, -550.0f, 0.0f);
	FRotator EnemyRotation = FRotator(0.0f, -180.0f, 0.0f);

	// Combatant class to spawn from.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatant> CombatantClass;

	// Array storing all the Combatants in this fight.
	TArray<ACombatant *> AllCombatants;

	UPROPERTY(EditAnywhere)
	UDataTable* CombatantDataTable;

	// True if a combatant is currently acting.
	bool bActionInProgress = false;

	// Player controller for the friendly team.
	ACombatantPlayerController * CombatantPlayerController = nullptr;

	// Has the player decided their actions for the turn.
	bool bPlayerDecisionComplete = false;
};
