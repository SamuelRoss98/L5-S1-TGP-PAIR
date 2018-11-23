// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "CombatantDecisionMaking.h"

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
	virtual void CombatDecision(TArray<ACombatant*> AllCombatants) override;
};
