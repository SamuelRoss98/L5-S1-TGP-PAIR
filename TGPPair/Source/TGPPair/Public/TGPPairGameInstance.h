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

private:
	// Players name.
	FString PlayerName = "Sam";

	// Player levels.
	FStatPack PlayerLevels = { 100, 50, 10, 0, 1, 1, 4, 1, 1, 1 };
};
