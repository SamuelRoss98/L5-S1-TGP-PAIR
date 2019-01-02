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

