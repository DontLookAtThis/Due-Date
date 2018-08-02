// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DD_YY_MMGameMode.h"
#include "DD_YY_MMPlayerController.h"
#include "DD_YY_MMCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADD_YY_MMGameMode::ADD_YY_MMGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADD_YY_MMPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}