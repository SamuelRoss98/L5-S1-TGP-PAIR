// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "StatPack.h"
#include "Engine/DataTable.h"

#include "NamedStatPack.generated.h"

USTRUCT(BlueprintType)
struct FNamedStatPack : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FNamedStatPack() :
		Name(""),
		Stats(FStatPack())
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FStatPack Stats;
};