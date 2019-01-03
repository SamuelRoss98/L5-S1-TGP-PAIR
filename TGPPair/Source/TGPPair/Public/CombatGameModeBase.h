// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "NamedStatPack.h"
#include "CombatAction.h"

#include "CombatGameModeBase.generated.h"

class ACombatantPawn;
class UDataTable;
class ACombatAIController;

/**
*
*/
UCLASS()
class TGPPAIR_API ACombatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawns combatants.
	void SpawnCombatants();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Event called at the start of each new round.
	UFUNCTION(BlueprintImplementableEvent)
	void StartNewRound();

	// Resets the combatants ready for a new round.
	UFUNCTION(BlueprintCallable)
	void ResetForNewRound();

	// Called to simulate the next action for this round.
	void SimulateNextAction();
	
	// Return the enemy combatant pawns.
	UFUNCTION(BlueprintCallable)
	TArray<ACombatantPawn*> GetEnemies() const;

	// Returns the item data with the given name.
	UFUNCTION(BlueprintCallable)
	FNamedStatPack GetItemFromName(FString name);

	// Returns the items data table.
	UDataTable* GetItemsData() const;

	// Returns the target of a given action.
	ACombatantPawn* GetActionTarget(bool bIsPlayer, FCombatAction Action);

	// Called to check if the battle is complete.
	void CheckForBattleFinish();

protected:
	// Blueprint event to load/display the defeat UI.
	UFUNCTION(BlueprintImplementableEvent)
	void LoadEndOfBattleUI(bool bVictory);

private:
	// Called regardless of victory or loss to complete shared tasks (hiding battle UI etc.).
	void HandleFinish();

	// Called when the battle has finished with player victory.
	void HandleFinishVictory();

	// Called when the battle has finished with player loss.
	void HandleFinishLoss();

	// Returns a random character from the enemies data table.
	FNamedStatPack GetRandomCharacter();

	// Returns the next combatant to act this round.
	ACombatantPawn* GetNextCombatantToAct() const;

	// Returns true if all combatants have taken their turn.
	bool IsEndOfRound() const;

protected:
	// Number of enemies to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemyCount = 1;

	// Spawn positions for combatants, index 0 is for the player, the next three will be used for enemy 1, 2, then 3 if needed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnLocations;

	// Class type to spawn combatants from.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatantPawn> CombatantClass;

	// Class type for enemy AI controller.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatAIController> AIClass;

	// Combatant controlled by the player.
	ACombatantPawn* PlayerCombatant = nullptr;

	// Contains all enemy combatants.
	TArray<ACombatantPawn*> EnemyCombatants;

	// Contains all combatants, player combatant followed by all enemies.
	TArray<ACombatantPawn*> AllCombatants;

	// Items data.
	UPROPERTY(EditAnywhere)
	UDataTable* ItemsDataTable;

	// Enemy data.
	UPROPERTY(EditAnywhere)
	UDataTable* EnemiesDataTable;

	// True if the battle is over.
	bool bBattleOver = false;
};
