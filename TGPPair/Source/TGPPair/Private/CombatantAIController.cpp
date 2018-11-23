// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantAIController.h"

#include "Combatant.h"

// Called every frame
void ACombatantAIController::Tick(float DeltaTime)
{

}

// Makes a combat decision for the combatant.
void ACombatantAIController::CombatDecision(TArray<ACombatant*> AllCombatants)
{
	bOurTurn = true;

	ACombatant* ControlledCombatant = Cast<ACombatant>(GetPawn());
	
	if (ControlledCombatant)
	{
		if (ControlledCombatant == AllCombatants[0])
			ControlledCombatant->AttackCombatant(AllCombatants[1]);
		else
			ControlledCombatant->AttackCombatant(AllCombatants[0]);
	}
}