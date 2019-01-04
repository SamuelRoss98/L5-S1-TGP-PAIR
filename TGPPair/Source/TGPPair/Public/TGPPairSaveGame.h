// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "StatPack.h"

#include "TGPPairSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API UTGPPairSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UTGPPairSaveGame();

public:
	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere)
	uint32 UserID;

	UPROPERTY(VisibleAnywhere)
	FString PlayerName;

	UPROPERTY(VisibleAnywhere)
	int PlayerOverallLevel;

	UPROPERTY(VisibleAnywhere)
	int PlayerExpEarnedTowardsNextLevel;
	
	UPROPERTY(VisibleAnywhere)
	FStatPack PlayerSkillLevels;

	UPROPERTY(VisibleAnywhere)
	int TotalBattlesWon;
};
