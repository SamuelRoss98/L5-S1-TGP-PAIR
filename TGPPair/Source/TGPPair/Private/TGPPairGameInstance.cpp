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

// Called to give exp to the player.
void UTGPPairGameInstance::GainExp(int Amount)
{
	//FString print = FString::FromInt(GetExpToNextLevel());
	//UE_LOG(LogTemp, Error, TEXT("Exp to next level: %s"), *print)

	if (Amount < GetExpToNextLevel())
		CurrentLevelExp += Amount;

	else if (Amount == GetExpToNextLevel())
	{
		CurrentLevel++;
		CurrentLevelExp = 0;
	}

	else
	{
		Amount -= GetExpToNextLevel();
		CurrentLevel++;
		CurrentLevelExp = 0;
		GainExp(Amount);
	}
}

// Returns the amount of exp between two levels [a < b].
int UTGPPairGameInstance::GetExpBetweenLevels(int a, int b)
{
	if (a >= b)
		return 0;

	return ExpFunction(b) - ExpFunction(a);
}

// Returns the amount of exp needed to level up.
int UTGPPairGameInstance::GetExpToNextLevel()
{
	return GetExpBetweenLevels(CurrentLevel, CurrentLevel + 1) - CurrentLevelExp;
}

// Returns how much experience the player has at their current level.
int UTGPPairGameInstance::GetCurrentLevelTotalExp()
{
	return CurrentLevelExp;
}

// Returns the players current level.
int UTGPPairGameInstance::GetPlayerLevel()
{
	return CurrentLevel;
}

// Function used to calculate exp between levels.
int UTGPPairGameInstance::ExpFunction(int level)
{
	float exp = 100.0f + (25.0f * FMath::Pow((float)level, 1.64f));
	return (int)exp;
}
