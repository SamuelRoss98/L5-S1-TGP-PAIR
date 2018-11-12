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

	SpawnPlayerParty();
	SpawnEncounteredParty();

}

void ACombatGameMode::SpawnPlayerParty()
{
	int PartySize = GameInstance->GetPlayerPartySize();
}

void ACombatGameMode::SpawnEncounteredParty()
{
	int PartySize = GameInstance->GetEncounterPartySize();

	// Spawn encounter party.
	for ( int i = 0; i < PartySize; i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		FVector SpawnLocation = FVector::ZeroVector;
		FRotator SpawnRotation = FRotator::ZeroRotator;

		ACombatant * newEncounterCombatant = Cast<ACombatant>(GetWorld()->SpawnActor(AICombatantToSpawn, &SpawnLocation, &SpawnRotation, SpawnParams));
		if (newEncounterCombatant)
			EncounteredParty.Add(newEncounterCombatant);

		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn encounter party member."));
		}
			
	}
}

void ACombatGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}