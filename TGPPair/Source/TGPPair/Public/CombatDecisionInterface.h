// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatDecisionInterface.generated.h"

class ACombatantPawn;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatDecisionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TGPPAIR_API ICombatDecisionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	// Returns the combatant that is controlled by this controller.
	virtual ACombatantPawn * GetControlledCombatant() const = 0;

	// Starts the combat descision process for this controller.
	virtual void MakeDescision() = 0;
	
};
