// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CombatantPlayerController.generated.h"

class ACombatant;

/**
 * 
 */
UCLASS()
class TGPPAIR_API ACombatantPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to setup input.
	virtual void SetupInputComponent() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	// Returns the combatant this is being controlled.
	ACombatant * GetControlledCombatant() const;

private:
	// Combatant controlled by this controller.
	ACombatant * Controlled = nullptr;
};
