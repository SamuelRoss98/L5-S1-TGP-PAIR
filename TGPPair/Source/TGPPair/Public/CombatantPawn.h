// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NamedStatPack.h"
#include "CombatAction.h"

#include "CombatantPawn.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class ICombatDecisionInterface;
class UInventoryComponent;

UCLASS()
class TGPPAIR_API ACombatantPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACombatantPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Initializes this combatant.
	bool Initialize(FNamedStatPack Character, bool bPlayer, ICombatDecisionInterface * CombatantController);

	// Starts the descision process for this combatant.
	void MakeCombatDescision();

	// Call to start this combatants turn.
	UFUNCTION(BlueprintImplementableEvent)
	void TakeTurn();

	// Called by blueprint to end the combatants turn.
	UFUNCTION(BlueprintCallable)
	void EndTurn();

	// Returns the NamedStatPack this character was created with.
	UFUNCTION(BlueprintPure)
	FNamedStatPack GetBaseCharacter() const;

	// Returns the current stats of the combatant.
	UFUNCTION(BlueprintPure)
	FStatPack GetStats() const;

	// Sets the current actions.
	UFUNCTION(BlueprintCallable)
	void SetCurrentAction(FCombatAction newAction);

	// Flag whether this combatant has taken their turn or not.
	void SetTurnTaken(bool setting);

	// Returns true if this combatant has taken their turn.
	bool GetTurnTaken() const;

	// Returns the combat log description of the current action.
	FString GetActionDescription(ACombatantPawn* Player, TArray<ACombatantPawn*> Enemies);

	// Generates a description for an attack action.
	FString GetAttackActionDescription(ACombatantPawn* Player, TArray<ACombatantPawn*> Enemies);

protected:
	// Controller for this combatant.
	ICombatDecisionInterface * Controller = nullptr;

	// Combatants main mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	// Interaction transform.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* InteractionTransform = nullptr;

	// Inventory.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryComponent* Inventory = nullptr;

	// Character this combatant was created as.
	FNamedStatPack CharacterBaseValues;

	// Current state of the combatants stats.
	FStatPack CurrentStats;

	// Currently set combat action.
	FCombatAction CurrentAction;

	// True if the combatant has taken their turn.
	bool bTurnTaken = false;

	// True if this combatant is the player.
	bool bIsPlayer = false;
};
