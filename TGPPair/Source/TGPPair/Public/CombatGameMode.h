// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Combatant.h"

#include "CombatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	// Spawns combatants in world.
	void SpawnCombatants();

private:
	ACombatant * Player = nullptr;
	ACombatant * Enemy = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatant> PlayerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatant> EnemyClass;
};
