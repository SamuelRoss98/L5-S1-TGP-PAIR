// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPlayerController.h"

#include "Engine/World.h"
#include "CombatGameModeBase.h"
#include "CombatantPawn.h"

ACombatantPawn* ACombatPlayerController::GetControlledCombatant() const
{
	return Cast<ACombatantPawn>(GetPawn());
}

void ACombatPlayerController::UpdateCombatLogText(FString NewText)
{
	CombatLogText = NewText;
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
	ACombatGameModeBase* CombatGameMode = Cast<ACombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if (CombatGameMode != nullptr)
		CombatGameMode->SimulateNextAction();
}


