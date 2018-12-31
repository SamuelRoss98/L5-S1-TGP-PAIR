// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "NamedStatPack.h"

#include "CombatantPawn.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class ICombatDecisionInterface;

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

	// Returns the current stats of the combatant.
	UFUNCTION(BlueprintPure)
	FStatPack GetStats() const;

	// Flag whether this combatant has taken their turn or not.
	void SetTurnTaken(bool setting);

	// Returns true if this combatant has taken their turn.
	bool GetTurnTaken() const;

protected:
	// Controller for this combatant.
	ICombatDecisionInterface * Controller = nullptr;

	// Combatants main mesh.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	// Interaction transform.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* InteractionTransform = nullptr;

	// Character this combatant was created as.
	FNamedStatPack CharacterBaseValues;

	// Current state of the combatants stats.
	FStatPack CurrentStats;

	// True if the combatant has taken their turn.
	bool bTurnTaken = false;
};
