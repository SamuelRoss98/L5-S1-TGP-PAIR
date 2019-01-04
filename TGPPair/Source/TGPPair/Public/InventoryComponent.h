// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "InventorySlot.h"

#include "InventoryComponent.generated.h"

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TGPPAIR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	// Add a specified item to the inventory.
	void AddItem(FString itemName, int quantity);

	// Returns true if the inventory is full.
	bool IsFull() const;

	// Returns the contents of the inventory.
	UFUNCTION(BlueprintCallable)
	TArray<FInventorySlot> GetContents() const;

private:
	// Returns true if there is already a stack of the given item, outIndex will be set to the index of that stack in the slots array.
	bool CheckForStack(FString itemName, int& outIndex);

	// Returns false if the requested item is not in the table, out parameter will contain the requested item if success.
	bool GetNamedItemFromTable(FString itemName, FNamedStatPack& outItem);

protected:
	// Total inventory slots.
	int MaxAllowedSlots = 5;

	// Items/empty slots in the inventory.
	TArray<FInventorySlot> Slots;

	// Item data.
	UDataTable* ItemsData = nullptr;
};
