// Fill out your copyright notice in the Description page of Project Settings.

#include "PartyLayout.h"

// Returns the size in cm represented by each grid unit.
float UPartyLayout::GetGridUnitSizeInCm() const
{
	return GridTileSizeCm;
}

// Returns array of spawn positions.
TArray<FIntPoint> UPartyLayout::GetSpawnPointsGrid() const
{
	return PartySpawnPoints;
}

// Returns array of world positions from the grid tiles.
TArray<FVector> UPartyLayout::GetSpawnPointsWorld() const
{
	TArray<FVector> Positions;

	for (int i = 0; i < PartySpawnPoints.Num(); i++)
	{
		FVector NewPosition = FVector(static_cast<float>(PartySpawnPoints[i].X) * GridTileSizeCm + (GridTileSizeCm / 2.0f), static_cast<float>(PartySpawnPoints[i].Y) * GridTileSizeCm + (GridTileSizeCm / 2.0f), 0.0f);
		Positions.Add(NewPosition);
	}

	return Positions;
}
