// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "StatPack.h"

#include "TGPPairGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API UTGPPairGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Setter for player name.
	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString Name);

	// Getter for player name.
	UFUNCTION(BlueprintPure)
	FString GetPlayerName() const;

	// Getter for the players current base stats.
	UFUNCTION(BlueprintPure)
	FStatPack GetPlayerCurrentBaseStats() const;

	// Increment total battles won.
	void IncrementWonBattles();

	// Returns the amount of exp between two levels [a < b].
	UFUNCTION(BlueprintPure)
	int GetExpBetweenLevels(int a, int b);

private:
	// Function used to calculate exp between levels.
	int ExpFunction(int level);

private:
	// Players name.
	FString PlayerName = "Sam";

	// Player levels.
	FStatPack PlayerLevels = { 100, 50, 15, 0, 1, 1, 4, 1, 1, 1 };

	// Counts total number of battles the player has won.
	int TotalBattlesWon;

	// Players current level.
	int CurrentLevel = 1;

	// Total gained since last level up.
	int ExpGainedThisLevel = 0;
};
