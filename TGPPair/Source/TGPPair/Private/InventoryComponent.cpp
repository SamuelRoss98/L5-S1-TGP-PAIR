// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

#include "Engine/World.h"
#include "CombatGameModeBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// Get the items data from the gamemode.
	ACombatGameModeBase* GameMode = nullptr;
	GameMode = Cast<ACombatGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode != nullptr)
		ItemsData = GameMode->GetItemsData();
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Add a specified item to the inventory.
void UInventoryComponent::AddItem(FString itemName)
{
	if (ItemsData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Item cannot be added to inventory as item data table is nullptr"))
		return;
	}

	FNamedStatPack Item;
	if (!GetNamedItemFromTable(itemName, Item))
	{
		UE_LOG(LogTemp, Error, TEXT("Item cannot be added to inventory as no item named '%s' could be found in item data table"), *itemName)
		return;
	}

	// Add to existing stack if one exists.
	int StackIndex = -1;
	bool bExistingStack = CheckForStack(itemName, StackIndex);
	if (bExistingStack)
	{
		Slots[StackIndex].Quantity++;
		return;
	}

	// If there is no current stack and the slots are taken the new item isn't added.
	if (IsFull())
		return;

	// Else we can create the new slot.
	Slots.Add(FInventorySlot(Item, 1));
}

// Returns true if the inventory is full.
bool UInventoryComponent::IsFull() const
{
	return Slots.Num() > MaxAllowedSlots;
}

// Returns the contents of the inventory.
TArray<FInventorySlot> UInventoryComponent::GetContents() const
{
	return Slots;
}

// Returns true if there is already a stack of the given item, outIndex will be set to the index of that stack in the slots array.
bool UInventoryComponent::CheckForStack(FString itemName, int& outIndex)
{
	for (int i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i].Item.Name == itemName)
		{
			outIndex = i;
			return true;
		}
	}

	return false;
}

// Returns false if the requested item is not in the table, out parameter will contain the requested item if success.
bool UInventoryComponent::GetNamedItemFromTable(FString itemName, FNamedStatPack& outItem)
{
	if (ItemsData == nullptr)
		return false;

	TArray<FNamedStatPack*> outItems;
	ItemsData->GetAllRows<FNamedStatPack>("GENERAL", outItems);

	for (int i = 0; i < outItems.Num(); ++i)
	{
		if (outItems[i]->Name == itemName)
		{
			outItem = *outItems[i];		
			return true;
		}
	}

	return false;
}
