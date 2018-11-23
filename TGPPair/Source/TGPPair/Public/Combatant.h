// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CombatAttribute.h"
#include "CharacterProperties.h"
#include "Combatant.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class ICombatantDecisionMaking;
class ACombatantAIController;
class ACombatantPlayerController;

UENUM(BlueprintType)
enum class ECombatantActions : uint8 
{
	Attack	 	UMETA(DisplayName = "Attack"),
	UseItem 	UMETA(DisplayName = "Item")
};

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

	// Starts this combatants turn.
	void StartTurn(TArray<ACombatant*> AllCombatants);

	// Ends this combants turn.
	void EndTurn();

	// Returns the interaction point Transform.
	FTransform GetInteractionTransform() const;

	// Return the character name of this combatant.
	FString GetCharacterName() const;

	// Returns the combatants current combat attributes.
	FCombatAttribute GetCurrentCombatAttributes() const;

	// Returns the combatants base combat attributes.
	FCombatAttribute GetBaseCombatAttributes() const;

	// Returns true if the combatant has already acted this turn.
	bool HasActedThisTurn() const;

	// Returns true if the combatant is on the players team.
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
	bool bActedThisTurn = false;

	// True if combatant is on the players team.
	bool bPlayerTeam = false;

	// True while the combatant is taking its turn.
	bool bTurnInProgress = false;

	// Original position of the combatant.
	FTransform OriginalTransform;

	float WaitTime = 3.0f;
	float WaitTimer = 0.0f;
};
