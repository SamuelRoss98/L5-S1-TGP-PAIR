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
}

// Creates the player and AI Combatant(s).
void ACombatGameMode::SpawnCombatants()
{
	SpawnPlayerCombatant();

	// Spawn AI members of player party.
	for (int i = 0; i < GameInstance->GetPlayerPartySize() - 1; i++)
		SpawnAICombatant(true, i + 1);

	// Spawn encountered party.
	for (int i = 0; i < GameInstance->GetEncounterPartySize(); i++)
		SpawnAICombatant(false, i);
}

// Spawns the player Combatant.
void ACombatGameMode::SpawnPlayerCombatant()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	ACombatant * PlayerCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(PlayerCombatantToSpawn, &SpawnLocation, &SpawnRotation, SpawnParams));
	if (PlayerCombatant)
		PlayerParty.Add(PlayerCombatant);
}

// Creates an AI Combatant for a given team.
void ACombatGameMode::SpawnAICombatant(bool PlayerTeam, int PartyIndex)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	ACombatant * NewAICombatant = Cast<ACombatant>(GetWorld()->SpawnActor(AICombatantToSpawn, &SpawnLocation, &SpawnRotation, SpawnParams));
	if (NewAICombatant)
		EncounteredParty.Add(NewAICombatant);
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