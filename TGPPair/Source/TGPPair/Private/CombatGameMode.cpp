// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatGameMode.h"

#include "TGPGameInstance.h"
#include "Combatant.h"
#include "Engine/World.h"

void ACombatGameMode::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// Get and check the custom game instance.
	GameInstance = Cast<UTGPGameInstance>(GetGameInstance());
	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CombatGameMode failed to get the TGPGameInstance."))
	}

	SpawnCombatants();

	UE_LOG(LogTemp, Warning, TEXT("Player party has %s members."), *(FString::FromInt(PlayerParty.Num())))
	UE_LOG(LogTemp, Warning, TEXT("Encounter party has %s members."), *(FString::FromInt(EncounteredParty.Num())))

	bFightOngoing = true;
}

// Creates the player and AI Combatant(s).
void ACombatGameMode::SpawnCombatants()
{
	float TileSize = 100.0f;
	float DistFromCentre = 300.0f;

	// Spawn player party.
	SpawnCombatant(false, true, 0, FVector(PlayerPartyGridPoints[0].X * TileSize + (TileSize/2.0f), PlayerPartyGridPoints[0].Y * TileSize + (TileSize / 2.0f) - DistFromCentre, 0.1f));
	for (int i = 1; i < GameInstance->GetPlayerPartySize(); i++)
	{
		FVector Position = FVector(PlayerPartyGridPoints[i].X * TileSize + (TileSize / 2.0f), PlayerPartyGridPoints[i].Y * TileSize + (TileSize / 2.0f) - DistFromCentre, 0.1f);
		SpawnCombatant(true, true, i, Position);
	}

	for (int i = 0; i < GameInstance->GetEncounterPartySize(); i++)
	{
		FVector Position = FVector(EncounterPartyGridPoints[i].X * TileSize + (TileSize / 2.0f), EncounterPartyGridPoints[i].Y * TileSize + (TileSize / 2.0f) + DistFromCentre, 0.1f);
		SpawnCombatant(true, false, i, Position);
	}
}

// Spawns a combatant.
void ACombatGameMode::SpawnCombatant(bool AI, bool PlayerTeam, int PartyPosition, FVector Position)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	FVector SpawnLocation = Position;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	ACombatant * NewCombatant = nullptr;
	if(AI)
		NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(AICombatantToSpawn, &SpawnLocation, &SpawnRotation, SpawnParams));
	else
		NewCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(PlayerCombatantToSpawn, &SpawnLocation, &SpawnRotation, SpawnParams));

	if (NewCombatant)
	{
		if (PlayerTeam)
			PlayerParty.Add(NewCombatant);
		else
			EncounteredParty.Add(NewCombatant);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn combatant."))
	}
}

// Returns the Combatant with the highest value for a given stat.
ACombatant * ACombatGameMode::GetCombatantWithHighestStat(ECombatantStat StatType) const
{
	int HighestValue = -999;
	ACombatant * CombatantToReturn = nullptr;

	for (int i = 0; i < PlayerParty.Num(); i++)
	{
		if (PlayerParty[i]->GetStat(StatType) > HighestValue)
		{
			HighestValue = PlayerParty[i]->GetStat(StatType);
			CombatantToReturn = PlayerParty[i];
		}
	}

	for (int i = 0; i < EncounteredParty.Num(); i++)
	{
		if (EncounteredParty[i]->GetStat(StatType) > HighestValue)
		{
			HighestValue = EncounteredParty[i]->GetStat(StatType);
			CombatantToReturn = EncounteredParty[i];
		}
	}

	return CombatantToReturn;
}

// Returns the Combatant with the lowest value for a given stat.
ACombatant * ACombatGameMode::GetCombatantWithLowestStat(ECombatantStat StatType) const
{
	int LowestValue = 999;
	ACombatant * CombatantToReturn = nullptr;

	for (int i = 0; i < PlayerParty.Num(); i++)
	{
		if (PlayerParty[i]->GetStat(StatType) < LowestValue)
		{
			LowestValue = PlayerParty[i]->GetStat(StatType);
			CombatantToReturn = PlayerParty[i];
		}
	}

	for (int i = 0; i < EncounteredParty.Num(); i++)
	{
		if (EncounteredParty[i]->GetStat(StatType) < LowestValue)
		{
			LowestValue = EncounteredParty[i]->GetStat(StatType);
			CombatantToReturn = EncounteredParty[i];
		}
	}

	return CombatantToReturn;
}

void ACombatGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}