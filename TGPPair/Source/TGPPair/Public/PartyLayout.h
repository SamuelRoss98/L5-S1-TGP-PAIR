// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PartyLayout.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TGPPAIR_API UPartyLayout : public UObject
{
	GENERATED_BODY()
	
public:
	// Returns the size in cm represented by each grid unit.
	float GetGridUnitSizeInCm() const;

	// Returns array of spawn positions.
	TArray<FIntPoint> GetSpawnPoints() const;

protected:
	// Amount of world space (cm) represented by each grid point.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GridTileSizeCm = 100.0f;

	// List of grid positions for party members to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntPoint> PartySpawnPoints;
};
