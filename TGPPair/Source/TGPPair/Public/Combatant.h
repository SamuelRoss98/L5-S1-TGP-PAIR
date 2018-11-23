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
	void LoadCombatant(FCharacterProperties Properties, bool bPlayer);

	// Returns the interaction point Transform.
	FTransform GetInteractionTransform() const;

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
};
