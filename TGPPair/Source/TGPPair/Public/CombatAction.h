// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NamedStatPack.h"

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
		ActionData(FNamedStatPack()),
		TargetIndex(0)
	{};

	// Defines the action type.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatantActionType ActionType;

	// Named statpack that is associated with this action, e.g. a health potion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNamedStatPack ActionData;

	// Index of the target on the target team.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TargetIndex;
};