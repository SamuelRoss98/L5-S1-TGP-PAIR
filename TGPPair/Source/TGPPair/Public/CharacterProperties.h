// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CombatAttribute.h"

#include "CharacterProperties.generated.h"

USTRUCT(BlueprintType)
struct FCharacterProperties : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterProperties() :
		CharacterName(""),
		CombatAttributes(FCombatAttribute())
		{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCombatAttribute CombatAttributes;
};
