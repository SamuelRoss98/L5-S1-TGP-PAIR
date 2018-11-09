// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TGPPairGameMode.h"
#include "TGPPairPlayerController.h"
#include "TGPPairCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATGPPairGameMode::ATGPPairGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATGPPairPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}