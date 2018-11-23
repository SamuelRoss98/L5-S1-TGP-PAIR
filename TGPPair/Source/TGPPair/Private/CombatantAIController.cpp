// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantAIController.h"

#include "Combatant.h"

// Makes a combat decision for the combatant.
void ACombatantAIController::CombatDecision(TArray<ACombatant*> AllCombatants)
{
	ACombatant* ControlledCombatant = Cast<ACombatant>(GetPawn());

	ACombatant * CombatantToAttack = AllCombatants[FMath::RandRange(0, AllCombatants.Num() - 1)];
	while (CombatantToAttack == ControlledCombatant)
		CombatantToAttack = AllCombatants[FMath::RandRange(0, AllCombatants.Num() - 1)];

	UE_LOG(LogTemp, Warning, TEXT("Attack decision"))
	ControlledCombatant->AttackCombatant(CombatantToAttack);
}