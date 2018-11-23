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
	// Makes a combat decision for the combatant.
	virtual void CombatDecision(TArray<ACombatant*> AllCombatants) override;
};
