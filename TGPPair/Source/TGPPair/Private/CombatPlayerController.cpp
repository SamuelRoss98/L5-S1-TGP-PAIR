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
	// Hack-y way to get player damage working until named attacks/spells are implemented.
	FCombatAction temp = GetControlledCombatant()->GetCurrentAction();
	if (temp.ActionType == ECombatantActionType::Attack)
	{
		temp.ActionData.Stats.MeleeAttack = GetControlledCombatant()->GetStats().MeleeAttack;
		GetControlledCombatant()->SetCurrentAction(temp);
	}

	ACombatGameModeBase* CombatGameMode = Cast<ACombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if (CombatGameMode != nullptr)
		CombatGameMode->SimulateNextAction();
}

// Returns true if a combatant tooltip should be displayed, outData contains the hit combatants NamedStatPack.
bool ACombatPlayerController::DisplayCombatantTooltip(FNamedStatPack& outData)
{
	FHitResult Hit;

	// Line trace to find combatants.
	if (!GetHitResultUnderCursor(ECC_Visibility, true, Hit))
		return false;

	// Attempt to cast hit actor to combatant.
	ACombatantPawn* HitCombatant = nullptr;
	HitCombatant = Cast<ACombatantPawn>(Hit.Actor);
	if (HitCombatant == nullptr)
		return false;

	// Don't display for player.
	if (HitCombatant->IsPlayer())
		return false;

	outData = FNamedStatPack();
	outData.Name = HitCombatant->GetBaseCharacter().Name;
	outData.Stats = HitCombatant->GetStats();

	return true;
}


