// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	// Spawn points temporarily hardcoded.
	FVector SpawnPointA = FVector(250.0f, 550.0f, 50.0f);
	FVector SpawnPointB = FVector(0.0f, 550.0f, 50.0f);
	FVector SpawnPointC = FVector(-250.0f, 550.0f, 50.0f);
};
