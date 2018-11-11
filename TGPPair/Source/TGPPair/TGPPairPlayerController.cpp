// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TGPPairPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "TGPPairCharacter.h"
#include "Engine/World.h"

ATGPPairPlayerController::ATGPPairPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATGPPairPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATGPPairPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATGPPairPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATGPPairPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATGPPairPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATGPPairPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ATGPPairPlayerController::OnResetVR);
}

void ATGPPairPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATGPPairPlayerController::MoveToMouseCursor()
{

}

void ATGPPairPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{

}

void ATGPPairPlayerController::SetNewMoveDestination(const FVector DestLocation)
{

}

void ATGPPairPlayerController::OnSetDestinationPressed()
{

}

void ATGPPairPlayerController::OnSetDestinationReleased()
{

}
