// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ManagementGameGameMode.h"
#include "ManagementGamePlayerController.h"
#include "ManagementGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AManagementGameGameMode::AManagementGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AManagementGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}