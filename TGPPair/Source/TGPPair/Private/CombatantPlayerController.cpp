// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatantPlayerController.h"

#include "Combatant.h"

// Called when the game starts or when spawned
void ACombatantPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Controlled = GetControlledCombatant();
	if (Controlled == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s failed to find the combatant it is controlling."), *(this->GetName()))
	}
}

// Called to setup input.
void ACombatantPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/*InputComponent->BindAction("Destroy", IE_Pressed, this, &ASpaceCraftPlayerController::Destruct);
	InputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceCraftPlayerController::Shoot);*/
}

// Called every frame
void ACombatantPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Returns the combatant this is being controlled.
ACombatant * ACombatantPlayerController::GetControlledCombatant() const
{
	return Cast<ACombatant>(GetPawn());
}


