// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "CombatDecisionInterface.h"

#include "CombatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatPlayerController : public APlayerController, public ICombatDecisionInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	ACombatantPawn * GetControlledCombatant() const;

	// Starts the combat descision process for this controller.
	void MakeDescision();

	// Blueprint event called at the start of the player decision process.
	UFUNCTION(BlueprintImplementableEvent)
	void PlayerDecisionStart();

	// Called by blueprint once the player has decided their action using the UI.
	UFUNCTION(BlueprintCallable)
	void DecisionComplete();
};
