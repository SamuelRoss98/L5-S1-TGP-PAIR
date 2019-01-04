// Fill out your copyright notice in the Description page of Project Settings.

#include "TGPPairGameInstance.h"

#include "CombatPlayer.h"
#include "TGPPairSaveGame.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

// Saves the game.
void UTGPPairGameInstance::SaveGame() const
{
	//UTGPPairSaveGame* SaveInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::CreateSaveGameObject(UTGPPairSaveGame::StaticClass()));
	//if (SaveInstance == nullptr)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Unable to save game, UTGPPairSaveGame instance was nullptr"))
	//	return;
	//}

	//// Save data.
	//SaveInstance->PlayerName = PlayerName;
	//SaveInstance->PlayerOverallLevel = CurrentLevel;
	//SaveInstance->PlayerExpEarnedTowardsNextLevel = CurrentLevelExp;
	//SaveInstance->PlayerSkillLevels = PlayerLevels;
	//SaveInstance->TotalBattlesWon = TotalBattlesWon;

	//UGameplayStatics::SaveGameToSlot(SaveInstance, SaveInstance->SaveSlotName, SaveInstance->UserID);
}

// Loads a saved game.
void UTGPPairGameInstance::LoadSaveGame()
{
	Player = NewObject<UCombatPlayer>();

	/*UTGPPairSaveGame* LoadInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::CreateSaveGameObject(UTGPPairSaveGame::StaticClass()));
	LoadInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadInstance->SaveSlotName, LoadInstance->UserID));
	if (LoadInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to save game, UTGPPairSaveGame instance was nullptr, likely save file is missing."))
		return;
	}
	
	PlayerName = LoadInstance->PlayerName;
	CurrentLevel = LoadInstance->PlayerOverallLevel;
	CurrentLevelExp = LoadInstance->PlayerExpEarnedTowardsNextLevel;
	PlayerLevels = LoadInstance->PlayerSkillLevels;
	TotalBattlesWon = LoadInstance->TotalBattlesWon;*/
}

// Returns the player.
UCombatPlayer* UTGPPairGameInstance::GetPlayer() const
{
	return Player;
}

// Increment total battles won.
void UTGPPairGameInstance::IncrementWonBattles()
{
	TotalBattlesWon++;
}