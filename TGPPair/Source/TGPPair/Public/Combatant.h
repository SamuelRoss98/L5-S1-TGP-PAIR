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

	// Returns true if the Combatant has already used their attack this turn.
	bool HasAttackedThisTurn() const;

	// Flag whether a Combatant has used their attack for the turn.
	void SetAttackedThisTurn(bool setting);

public:
	// Combat level of the combatant.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	int CombatLevel = 0;

	// Damage of combatant before any modifiers are applied.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	int BaseDamage = 0;

private:
	// True is this combatant has used their attack this turn.
	bool bHasAttackedThisTurn = false;
};
