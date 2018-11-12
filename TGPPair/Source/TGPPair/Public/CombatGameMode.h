// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
};
