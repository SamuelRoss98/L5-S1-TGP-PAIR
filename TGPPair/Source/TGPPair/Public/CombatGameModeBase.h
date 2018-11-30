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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Notifies the GameMode that the acting combatant has finished their turn.
	void NotifyEndTurn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Calls spawning code for all combatants in this battle.
	void SpawnCombatants();

	// Spawns a single combatant.
	void SpawnCombatant(FVector SpawnPoint, FRotator SpawnRotation, FCharacterProperties Character, bool bFriendly, bool bPlayer);

	// Starts the next combat round.
	void StartRound();

	// Ends the current round.
	void EndRound();

	// Returns true if the round is complete.
	bool IsRoundComplete() const;

	// Return the next combatant to act based on their speed.
	ACombatant * GetNextToAct() const;

	// Starts the process of carrying out the actions for the round.
	void StartRoundActions();

	// Main loop for actions logic.
	void RunActions();

	// Starts the turn of the next combatant to carry out their action.
	void StartNextTurn();

private:
	// Spawn points temporarily hardcoded.
	FVector SpawnPointA = FVector(250.0f, 400.0f, 0.0f);
	FVector SpawnPointB = FVector(0.0f, -400.0f, 0.0f);
	FVector SpawnPointC = FVector(-250.0f, 400.0f, 0.0f);
	FVector SpawnPointD = FVector(250.0f, 400.0f, 0.0f);
	FVector SpawnPointE = FVector(0.0f, 400.0f, 0.0f);
	FVector SpawnPointF = FVector(-250.0f, 400.0f, 0.0f);
	FRotator EnemyRotation = FRotator(0.0f, -180.0f, 0.0f);

	// Combatant class to spawn from.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatant> CombatantClass;

	// Array storing all the Combatants in this fight.
	TArray<ACombatant *> AllCombatants;

	// Data for combatant types.
	UPROPERTY(EditAnywhere)
	UDataTable* CombatantDataTable;

	// Player controller for the friendly team.
	ACombatantPlayerController * CombatantPlayerController = nullptr;

	// True if the player has made their decision(s) for this round.
	bool bPlayerDecisionComplete = false;

	// True while the actions for this round are being carried out.
	bool bActionsInProgress = false;

	// True while a single combatant is acting (animating etc.).
	bool bCombatantActing = false;
};
