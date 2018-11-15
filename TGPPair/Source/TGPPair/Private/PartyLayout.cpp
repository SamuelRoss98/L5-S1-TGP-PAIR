// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyLayout.h"

// Returns the size in cm represented by each grid unit.
float UPartyLayout::GetGridUnitSizeInCm() const
{
	return GridTileSizeCm;
}

// Returns array of spawn positions.
TArray<FIntPoint> UPartyLayout::GetSpawnPoints() const
{
	return PartySpawnPoints;
}
