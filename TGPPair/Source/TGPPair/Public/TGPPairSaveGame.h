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
	// Save properties
	// --------------------------------------------------
	UPROPERTY(VisibleAnywhere)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere)
	uint32 UserID;
	// --------------------------------------------------

	// Player stats
	// --------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString PlayerName = "Ivar the Nameless";
	int AvailableSkillPoints = 0;
	int OverallLevel = 1;
	int ExpEarnedAtCurrentLevel = 0;
	int SkillLevelMana = 0;
	int SkillLevelLuck = 0;
	int SkillLevelStrength = 0;
	int SkillLevelDefense = 0;
	int SkillLevelSpeed = 0;
	// --------------------------------------------------
	

	// Misc. stats
	// --------------------------------------------------
	UPROPERTY(VisibleAnywhere)
	int TotalBattlesWon = 0;
	// --------------------------------------------------
};
