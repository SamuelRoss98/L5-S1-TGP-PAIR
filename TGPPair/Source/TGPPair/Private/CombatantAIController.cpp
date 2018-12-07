// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantAIController.h"

#include "Combatant.h"

// Makes a combat decision for the combatant.
FCombatantAction ACombatantAIController::GetAction()
{
	FCombatantAction Action;
	Action.ActionType = ECombatantActionType::Attack;
	Action.bActOnOwnTeam = false;
	Action.TargetIndex = 0;

	return Action;
}