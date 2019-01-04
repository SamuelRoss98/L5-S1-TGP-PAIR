// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "StatPack.h"

#include "CombatPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API UCombatPlayer : public UObject
{
	GENERATED_BODY()
	
public:
	// Returns the player stat pack based on their level/skills.
	UFUNCTION(BlueprintPure)
	FStatPack GetPlayerStatPack() const;

	// Called to award the player exp.
	UFUNCTION(BlueprintCallable)
	void AwardExp(int Amount);

	// Returns the amount of exp between two levels [a < b].
	UFUNCTION(BlueprintPure)
	int GetExpBetweenLevels(int a, int b);

	// Returns the amount of exp needed to level up.
	UFUNCTION(BlueprintPure)
	int GetExpToNextLevel();

	// Returns how much experience the player has at their current level.
	UFUNCTION(BlueprintPure)
	int GetExpEarnedAtCurrentLevel();

	// Returns the players current level.
	UFUNCTION(BlueprintPure)
	int GetOverallLevel();

private:
	// Increases the players level.
	void LevelUp();

	// Function used to calculate exp between levels.
	int ExpFunction(int level);

protected:
	// Players overall level.
	UPROPERTY(VisibleAnywhere)
	FString PlayerName = "Ivar the Nameless";

	// Unspent skill points.
	UPROPERTY(VisibleAnywhere)
	int AvailableSkillPoints = 0;

	// Players overall level.
	UPROPERTY(VisibleAnywhere)
	int OverallLevel = 1;

	// Experience earned towards the current level.
	UPROPERTY(VisibleAnywhere)
	int ExpEarnedAtCurrentLevel = 0;

	// Number of skill points for mana skill.
	UPROPERTY(VisibleAnywhere)
	int SkillInvestmentMana = 0;

	// Number of skill points for luck skill.
	UPROPERTY(VisibleAnywhere)
	int SkillInvestmentLuck = 0;

	// Number of skill points for strength skill.
	UPROPERTY(VisibleAnywhere)
	int SkillInvestmentStrength = 0;

	// Number of skill points for defense skill.
	UPROPERTY(VisibleAnywhere)
	int SkillInvestmentDefense = 0;

	// Number of skill points for speed skill.
	UPROPERTY(VisibleAnywhere)
	int SkillInvestmentSpeed = 0;
};
