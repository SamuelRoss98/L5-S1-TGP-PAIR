// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CombatAttribute.h"
#include "CharacterProperties.h"
#include "CombatantAction.h"
#include "Combatant.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class ICombatantDecisionMaking;
class ACombatantAIController;
class ACombatantPlayerController;



UCLASS()
class TGPPAIR_API ACombatant : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACombatant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Initialize this combatant with a CharacterProperties structure.
	void LoadCombatant(FCharacterProperties Properties, bool bPlayer, bool bFriendly);

	// Prepares the combatant for a new round.
	void PrepareForNewRound();

	// Starts this combatants turn.
	UFUNCTION(BlueprintImplementableEvent)
	void StartTurn();

	// Ends this combatants turn.
	UFUNCTION(BlueprintCallable)
	void EndTurn();

	// Returns the combatants action for a turn.
	UFUNCTION(BlueprintCallable)
	FCombatantAction GetActionForTurn();

	// Returns the interaction point Transform.
	UFUNCTION(BlueprintPure)
	FTransform GetInteractionTransform() const;

	// Returns the combatants resting transform.
	UFUNCTION(BlueprintPure)
	FTransform GetRestingTransform() const;

	// Return the character name of this combatant.
	UFUNCTION(BlueprintPure)
	FString GetCharacterName() const;

	// Returns the combatants current combat attributes.
	UFUNCTION(BlueprintPure)
	FCombatAttribute GetCurrentCombatAttributes() const;

	// Returns the combatants base combat attributes.
	FCombatAttribute GetBaseCombatAttributes() const;

	// Returns true if the combatant has already acted this turn.
	bool HasTakenTurn() const;

	// Returns true if the combatant is on the players team.
	UFUNCTION(BlueprintPure)
	bool IsOnPlayerTeam() const;

	// Returns true while this combatant is taking its turn.
	bool IsTurnInProgress() const;

public:
	// Attacks a combatant.
	void AttackCombatant(ACombatant * CombatantToAttack);

private:
	// Spawn the controller for this Combatant.
	void SpawnCombatantController(bool bPlayer);

protected:
	// Mesh for the combatant, root component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh = nullptr;

	// World transform other combatants will move to to attack/interact with this combatant.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* InteractionPoint = nullptr;

	// AIController class used for AI controlled combatants.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatantAIController> CombatantAIControllerClass;

	// PlayerController class used for player controlled combatants.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACombatantPlayerController> CombatantPlayerControllerClass;

private:
	// Controller of this Combatant.
	ICombatantDecisionMaking * CombatantController = nullptr;

	// Name of the combatant character.
	FString CharacterName = "";

	// CombatAttribute tracking the combatants current stat values. (e.g. with damage applied)
	FCombatAttribute CurrentCombatAttributes = FCombatAttribute();

	// CombatAttribute tracking the combatants base stat values. (Doesn't change).
	FCombatAttribute BaseCombatAttributes = FCombatAttribute();

	// True if the combatant has acted this turn.
	bool bHasTakenTurn = false;

	// True if combatant is on the players team.
	bool bPlayerTeam = false;

	// True while the combatant is taking its turn.
	bool bActionInProgress = false;

	// True while any animation or movement is is in progress.
	bool bAnimationInProgress = false;

	// Original position of the combatant.
	FTransform OriginalTransform;

	float WaitTime = 3.0f;
	float WaitTimer = 0.0f;

private:
	FCombatantAction TurnAction;

public:
	// Returns the action this combatant has decided to carry out this turn.
	const FCombatantAction GetTurnAction() const;

	// Set the action this combatant next carry out.
	void SetTurnAction(const FCombatantAction Action);
};
