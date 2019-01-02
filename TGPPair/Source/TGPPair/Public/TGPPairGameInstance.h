// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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

private:
	// Players name.
	FString PlayerName = "Rain";
};
