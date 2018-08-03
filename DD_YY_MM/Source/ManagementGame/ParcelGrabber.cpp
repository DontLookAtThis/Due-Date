// Fill out your copyright notice in the Description page of Project Settings.

#include "ParcelGrabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UParcelGrabber::UParcelGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UParcelGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UParcelGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick and log it
	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(m_PlayerViewPoint, m_PlayerRotation);	

	/// Draw a red trace in the world to visualize
	FVector LineTraceEnd = m_PlayerViewPoint + m_PlayerRotation.Vector() * m_fReach;
	DrawDebugLine(
		GetWorld(),
		m_PlayerViewPoint,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (ray-cast) out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		m_PlayerViewPoint,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// See what we hit
	if (LineTraceHit.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s hit."), *LineTraceHit.GetActor()->GetName());
	}
}

