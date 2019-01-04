// Fill out your copyright notice in the Description page of Project Settings.

#include "TGPPairGameInstance.h"

#include "CombatPlayer.h"
#include "TGPPairSaveGame.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

UTGPPairGameInstance::UTGPPairGameInstance()
{
	// Create player object.
	Player = NewObject<UCombatPlayer>();

	// If there is no save file, save the default one.
	if (!DoesSaveFileExist())
		CreateDefaultSave();

	LoadSaveGame();
}

// Creates a default save file.
void UTGPPairGameInstance::CreateDefaultSave() const
{
	UTGPPairSaveGame* SaveInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::CreateSaveGameObject(UTGPPairSaveGame::StaticClass()));
	if (SaveInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to create default save game, UTGPPairSaveGame instance was nullptr"))
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Created default save file."))
	UGameplayStatics::SaveGameToSlot(SaveInstance, SaveInstance->SaveSlotName, SaveInstance->UserID);
}

// Returns true if a save file exists.
bool UTGPPairGameInstance::DoesSaveFileExist() const
{
	UTGPPairSaveGame* LoadInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::CreateSaveGameObject(UTGPPairSaveGame::StaticClass()));
	LoadInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadInstance->SaveSlotName, LoadInstance->UserID));
	if (LoadInstance == nullptr)
		return false;

	return true;
}

// Saves the game.
void UTGPPairGameInstance::SaveGame() const
{
	UTGPPairSaveGame* SaveInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::CreateSaveGameObject(UTGPPairSaveGame::StaticClass()));
	if (SaveInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to save game, UTGPPairSaveGame instance was nullptr"))
		return;
	}

	// Save data.
	SaveInstance->PlayerName = Player->GetPlayerName();
	SaveInstance->AvailableSkillPoints = Player->GetAvailableSkillPoints();
	SaveInstance->OverallLevel = Player->GetOverallLevel();
	SaveInstance->ExpEarnedAtCurrentLevel = Player->GetExpEarnedAtCurrentLevel();
	SaveInstance->SkillLevelMana = Player->GetSkillLevel(EPlayerSkillType::Mana);
	SaveInstance->SkillLevelLuck = Player->GetSkillLevel(EPlayerSkillType::Luck);
	SaveInstance->SkillLevelStrength = Player->GetSkillLevel(EPlayerSkillType::Strength);
	SaveInstance->SkillLevelDefense = Player->GetSkillLevel(EPlayerSkillType::Defense);
	SaveInstance->SkillLevelSpeed = Player->GetSkillLevel(EPlayerSkillType::Speed);
	SaveInstance->TotalBattlesWon = TotalBattlesWon;

	FString Lvl = FString::FromInt(SaveInstance->OverallLevel);
	FString Exp = FString::FromInt(SaveInstance->ExpEarnedAtCurrentLevel);
	UE_LOG(LogTemp, Warning, TEXT("Saved game. [Level %s %s exp]"), *Lvl, *Exp)
	UGameplayStatics::SaveGameToSlot(SaveInstance, SaveInstance->SaveSlotName, SaveInstance->UserID);
}

// Loads a saved game.
void UTGPPairGameInstance::LoadSaveGame()
{
	UTGPPairSaveGame* LoadInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::CreateSaveGameObject(UTGPPairSaveGame::StaticClass()));
	if (LoadInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to save game, UTGPPairSaveGame instance was nullptr"))
		return;
	}
	LoadInstance = Cast<UTGPPairSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadInstance->SaveSlotName, LoadInstance->UserID));

	if (Player != nullptr)
	{
		Player->SetValues(LoadInstance->PlayerName, LoadInstance->AvailableSkillPoints, LoadInstance->OverallLevel, LoadInstance->ExpEarnedAtCurrentLevel,
			LoadInstance->SkillLevelMana, LoadInstance->SkillLevelStrength, LoadInstance->SkillLevelLuck, LoadInstance->SkillLevelDefense, LoadInstance->SkillLevelSpeed);

		FString Lvl = FString::FromInt(LoadInstance->OverallLevel);
		FString Exp = FString::FromInt(LoadInstance->ExpEarnedAtCurrentLevel);
		UE_LOG(LogTemp, Warning, TEXT("Loaded game. [Level %s %s exp]"), *Lvl, *Exp)
	}

	TotalBattlesWon = LoadInstance->TotalBattlesWon;
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