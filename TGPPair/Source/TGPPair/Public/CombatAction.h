// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatAction.generated.h"

UENUM(BlueprintType)
enum class ECombatantActionType : uint8
{
	NullAction  UMETA(DisplayName = "None"),
	Attack	 	UMETA(DisplayName = "Attack"),
	Item		UMETA(DisplayName = "Item"),
	Run			UMETA(DisplayName = "Run")
};

USTRUCT(BlueprintType)
struct FCombatAction
{
	GENERATED_USTRUCT_BODY()

public:
	FCombatAction() :
		ActionType(ECombatantActionType::NullAction),
		TargetIndex(0)
	{};

	// Defines the action type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatantActionType ActionType;

	// Index of the target on the target team.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TargetIndex;
};