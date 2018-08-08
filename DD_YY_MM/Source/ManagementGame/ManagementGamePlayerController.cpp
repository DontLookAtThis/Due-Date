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
	CardinalMovement();

	if (bGrabbing)
	{
		iGrabTimer++;
	}
	if (iGrabTimer > 3)
	{
		iGrabTimer = 0;
		bGrabbing = false;
	}
}

void AManagementGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	
	InputComponent->BindAxis("MoveForward" , this, &AManagementGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight" , this, &AManagementGamePlayerController::MoveRight);
}

void AManagementGamePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && Distance > 90.0f)
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AManagementGamePlayerController::MoveForward(float AxisValue)
{
	fMoveForward = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

}

void AManagementGamePlayerController::MoveRight(float AxisValue)
{
	fMoveRight = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);

}

void AManagementGamePlayerController::CardinalMovement()
{
	APawn* const MyPawn = GetPawn();

	FVector Destination = MyPawn->GetActorLocation();
	//if (fMoveRight > 0.0f)
	//{
	//	Destination.Y += 100.0f;
	//}
	//else if(fMoveRight < 0.0f)
	//{
	//	Destination.Y -= 100.0f;
	//}
	//if (fMoveForward > 0.0f)
	//{
	//	Destination.X += 100.0f;
	//}
	//else if(fMoveForward < 0.0f)
	//{
	//	Destination.X -= 100.0f;
	//}

	Destination.Y += (fMoveRight * 100.0f);
	Destination.X -= (fMoveForward * 100.0f);
	SetNewMoveDestination(Destination);
}

void AManagementGamePlayerController::OnSetGrabPressed()
{

}
void AManagementGamePlayerController::OnSetGrabRelease()
{
	
}


