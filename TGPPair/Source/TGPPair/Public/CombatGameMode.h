// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Combatant.h"
#include "CombatGameMode.generated.h"

class UTGPGameInstance;

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

private:
	// Creates the player and AI Combatant(s).
	void SpawnCombatants();

	// Spawns a combatant.
	void SpawnCombatant(bool AI, bool PlayerTeam, int PartyPosition, FVector Position);

	// Returns the Combatant with the highest value for a given stat.
	ACombatant* GetCombatantWithHighestStat(ECombatantStat StatType) const;

	// Returns the Combatant with the lowest value for a given stat.
	ACombatant* GetCombatantWithLowestStat(ECombatantStat StatType) const;

public:
	// Combatant type so spawn for the player.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatant> PlayerCombatantToSpawn;

	// Combatant type to spawn for AI.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatant> AICombatantToSpawn;

	// Grid spawn points for player party.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntPoint> PlayerPartyGridPoints;

	// Grid spawn points for player party.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FIntPoint> EncounterPartyGridPoints;

private:
	// Combatants belonging to player party.
	TArray<ACombatant*> PlayerParty;

	// Combatants belonging to encountered party.
	TArray<ACombatant*> EncounteredParty;

	// TGPGameInstance.
	UTGPGameInstance* GameInstance = nullptr;

	// True while the fight is on-going.
	bool bFightOngoing = false;
};
