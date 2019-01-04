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
<<<<<<< HEAD
=======

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
>>>>>>> combat-2.0
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
<<<<<<< HEAD

=======
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ATGPPairCharacter* MyPawn = Cast<ATGPPairCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
>>>>>>> combat-2.0
}

void ATGPPairPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
<<<<<<< HEAD

=======
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
>>>>>>> combat-2.0
}

void ATGPPairPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
<<<<<<< HEAD

=======
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
>>>>>>> combat-2.0
}

void ATGPPairPlayerController::OnSetDestinationPressed()
{
<<<<<<< HEAD

=======
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
>>>>>>> combat-2.0
}

void ATGPPairPlayerController::OnSetDestinationReleased()
{
<<<<<<< HEAD

=======
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
>>>>>>> combat-2.0
}
