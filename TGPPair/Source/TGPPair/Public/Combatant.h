// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Combatant.generated.h"

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

	// Called to start this combatants turn.
	void StartTurn();

private:
	// True when this combatant has taken a turn this round.
	bool bTakenTurnThisRound = false;

	// True when this combatant has finished their current turn.
	bool bCurrentTurnComplete = true;
};
