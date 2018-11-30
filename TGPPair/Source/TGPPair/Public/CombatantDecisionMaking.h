// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CombatantAction.h"

#include "CombatantDecisionMaking.generated.h"

class ACombatant;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatantDecisionMaking : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TGPPAIR_API ICombatantDecisionMaking
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// Makes a combat decision for the combatant.
	virtual FCombatantAction GetAction(TArray<ACombatant*> AllCombatants) = 0;
};
