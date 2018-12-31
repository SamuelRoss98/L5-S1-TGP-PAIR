// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatGameModeBase.generated.h"

class ACombatantPawn;
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

public:
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
	TArray<ACombatantPawn*> EnemyCombatants = { nullptr };
};
