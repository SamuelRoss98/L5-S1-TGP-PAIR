// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatantAction.generated.h"

UENUM(BlueprintType)
enum class ECombatantActionType : uint8
{
	NullAction UMETA(DisplayName = "None"),
	Attack	 	UMETA(DisplayName = "Attack"),
	Magic 		UMETA(DisplayName = "Magic"),
	Item		UMETA(DisplayName = "Item"),
	Run			UMETA(DisplayName = "Run")
};

USTRUCT(BlueprintType)
struct FCombatantAction
{
	GENERATED_USTRUCT_BODY()

public:
	FCombatantAction() :
		ActionType(ECombatantActionType::NullAction),
		bActOnOwnTeam(false),
		TargetIndex(0)
		{};

	// Defines the action type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatantActionType ActionType;

	// True if the teamIndex represents a slot on the acting combatants own team (e.g. friendly fire).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActOnOwnTeam;

	// Index of the target on the target team.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TargetIndex;
};
