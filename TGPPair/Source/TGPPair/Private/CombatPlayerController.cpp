// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPlayerController.h"

#include "CombatantPawn.h"

ACombatantPawn* ACombatPlayerController::GetControlledCombatant() const
{
	return Cast<ACombatantPawn>(GetPawn());
}

// Starts the combat descision process for this controller.
void ACombatPlayerController::MakeDescision()
{
	PlayerDecisionStart();
}

// Called by blueprint once the player has decided their action using the UI.
void ACombatPlayerController::DecisionComplete()
{
	UE_LOG(LogTemp, Warning, TEXT("Player decision made."))
}


