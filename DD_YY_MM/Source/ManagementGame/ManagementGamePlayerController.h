// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ManagementGamePlayerController.generated.h"

UCLASS()
class AManagementGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AManagementGamePlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	float fMoveForward;
	float fMoveRight;
	bool bGrabbing;
	int iGrabTimer;
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */

	void OnSetGrabPressed();
	void OnSetGrabRelease();

};


