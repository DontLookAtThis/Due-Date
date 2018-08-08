// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ManagementGameGameMode.h"
#include "ManagementGamePlayerController.h"
#include "ManagementGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AManagementGameGameMode::AManagementGameGameMode()
{
	//// use our custom PlayerController class
	PlayerControllerClass = AManagementGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player_Assets/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Default Class Set Successfully."));
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Default Class Not Set Successfully."));
	}
}