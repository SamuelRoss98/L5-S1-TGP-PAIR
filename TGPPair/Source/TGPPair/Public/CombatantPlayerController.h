// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "CombatantDecisionMaking.h"
#include "CombatantAction.h"

#include "CombatantPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatantPlayerController : public APlayerController, public ICombatantDecisionMaking
{
	GENERATED_BODY()
	
public:
	// Makes a combat decision for the combatant.
	virtual FCombatantAction GetAction(TArray<ACombatant *> FriendlyTeam, TArray<ACombatant *> EnemyTeam) override;

	// Called by the gamemode to start the players action selection process each turn.
	void StartCombatDecisions();

	// Blueprint implementable event for combat decisions.
	UFUNCTION(BlueprintImplementableEvent)
	void StartCombatDecisionEvent();

	UFUNCTION(BlueprintImplementableEvent)
	bool IsDecisionFinished();

	UFUNCTION(BlueprintImplementableEvent)
	FCombatantAction GetAction();
};
