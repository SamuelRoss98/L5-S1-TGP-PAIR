// Fill out your copyright notice in the Description page of Project Settings.

#include "Combatant.h"


// Sets default values
ACombatant::ACombatant()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatant::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Returns true if the Combatant has already used their attack this turn.
bool ACombatant::HasAttackedThisTurn() const
{
	return bHasAttackedThisTurn;
}

// Flag whether a Combatant has used their attack for the turn.
void ACombatant::SetAttackedThisTurn(bool setting)
{
	bHasAttackedThisTurn = setting;
}

