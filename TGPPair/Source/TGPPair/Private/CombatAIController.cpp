// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatAIController.h"

#include "CombatantPawn.h"

ACombatantPawn* ACombatAIController::GetControlledCombatant() const
{
	return Cast<ACombatantPawn>(GetPawn());
}

// Starts the combat descision process for this controller.
void ACombatAIController::MakeDescision()
{
	ACombatantPawn* OurPawn = GetControlledCombatant();

	FCombatAction Action;

	Action.ActionType = ECombatantActionType::Attack;
	Action.TargetIndex = 0;

	OurPawn->SetCurrentAction(Action);
}


