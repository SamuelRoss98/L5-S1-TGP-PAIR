// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "StatPack.h"

#include "TGPPairGameInstance.generated.h"

class UCombatPlayer;

/**
 * 
 */
UCLASS()
class TGPPAIR_API UTGPPairGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTGPPairGameInstance();

	// Returns true if a save file exists.
	UFUNCTION(BlueprintCallable)
	bool DoesSaveFileExist() const;

	// Creates a default save file.
	UFUNCTION(BlueprintCallable)
	void CreateDefaultSave() const;

	// Saves the game.
	UFUNCTION(BlueprintCallable)
	void SaveGame() const;

	// Loads a save game.
	UFUNCTION(BlueprintCallable)
	void LoadSaveGame();

	// Returns the player.
	UFUNCTION(BlueprintPure)
	UCombatPlayer* GetPlayer() const;

	// Increment total battles won.
	void IncrementWonBattles();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCombatPlayer* Player = nullptr;

private:
	// Counts total number of battles the player has won.
	int TotalBattlesWon;
};
