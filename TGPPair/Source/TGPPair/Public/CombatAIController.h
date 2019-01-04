// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "CombatDecisionInterface.h"

#include "CombatAIController.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatAIController : public AAIController, public ICombatDecisionInterface
{
	GENERATED_BODY()
	
public:
	ACombatantPawn * GetControlledCombatant() const;

	// Starts the combat descision process for this controller.
	void MakeDescision();
};
