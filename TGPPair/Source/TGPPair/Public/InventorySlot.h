// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "NamedStatPack.h"

#include "InventorySlot.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY()

public:
	FInventorySlot() :
		Item(FNamedStatPack()),
		Quantity(0)
	{}

	FInventorySlot(FNamedStatPack item, int initialQuantity) :
		Item(item),
		Quantity(initialQuantity)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNamedStatPack Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
};