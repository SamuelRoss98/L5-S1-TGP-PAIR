// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"

#include "CharacterProperties.generated.h" // this must be last include in the file

USTRUCT(BlueprintType)
struct FCharacterProperties : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterProperties() :
		XPtoLvl(0),
		AdditionalHP(0)
		{}

	/** The 'Name' column is the same as the XP Level */

	/** XP to get to the given level from the previous level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	int32 XPtoLvl;

	/** Extra HitPoints gained at this level */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	int32 AdditionalHP;
};
