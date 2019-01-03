// Fill out your copyright notice in the Description page of Project Settings.

#include "TGPPairGameInstance.h"

// Setter for player name.
void UTGPPairGameInstance::SetPlayerName(FString Name)
{
	PlayerName = Name;
}

// Getter for player name.
FString UTGPPairGameInstance::GetPlayerName() const
{
	return PlayerName;
}

// Getter for the players current base stats.
FStatPack UTGPPairGameInstance::GetPlayerCurrentBaseStats() const
{
	return PlayerLevels;
}

// Increment total battles won.
void UTGPPairGameInstance::IncrementWonBattles()
{
	TotalBattlesWon++;
}

// Returns the amount of exp between two levels [a < b].
int UTGPPairGameInstance::GetExpBetweenLevels(int a, int b)
{
	if (a >= b)
		return 0;

	return ExpFunction(b) - ExpFunction(a);
}

// Function used to calculate exp between levels.
int UTGPPairGameInstance::ExpFunction(int level)
{
	return 100 + (25 * (int)(FMath::Pow((float)level, 1.25f)));
}
