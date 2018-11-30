// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantPlayerController.h"

// Makes a combat decision for the combatant.
FCombatantAction ACombatantPlayerController::GetAction(TArray<ACombatant *> FriendlyTeam, TArray<ACombatant *> EnemyTeam)
{
	return GetAction();
}

void ACombatantPlayerController::StartCombatDecisions()
{
	StartCombatDecisionEvent();
}

