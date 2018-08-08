// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ManagementGamePlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ManagementGameCharacter.h"
#include "Engine/World.h"

AManagementGamePlayerController::AManagementGamePlayerController()
{
	fMoveForward = 0.0f;
	fMoveRight = 0.0f;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bGrabbing = false;
	iGrabTimer = 0;
}

void AManagementGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired


	//CardinalMovement();

}

void AManagementGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	
}




void AManagementGamePlayerController::OnSetGrabPressed()
{

}
void AManagementGamePlayerController::OnSetGrabRelease()
{
	
}


