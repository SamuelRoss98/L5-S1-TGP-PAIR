// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "CombatantDecisionMaking.h"

#include "CombatantAIController.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatantAIController : public AAIController, public ICombatantDecisionMaking
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Makes a combat decision for the combatant.
	virtual void CombatDecision(TArray<ACombatant*> AllCombatants) override;

private:
	// Minimum time it takes to make a decision (in seconds).
	float DecisionTime = 2.5f;

	// Tracks time passed when waiting for decision.
	float DecisionTimer = 0.0f;

	// True while it's our turn.
	bool bOurTurn = false;
};
