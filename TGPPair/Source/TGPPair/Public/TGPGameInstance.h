// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TGPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API UTGPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Returns number of characters in the players party.
	UFUNCTION(BlueprintPure, Category = "Combat")
	int GetPlayerPartySize() const;

	// Returns the number of characters in the encountered party.
	UFUNCTION(BlueprintPure, Category = "Combat")
	int GetEncounterPartySize() const;

private:
	// Number of characters in the players party.
	int PlayerPartySize = 3;

	// Number of characters in the encountered party.
	int EncounterPartySize = 3;
};
