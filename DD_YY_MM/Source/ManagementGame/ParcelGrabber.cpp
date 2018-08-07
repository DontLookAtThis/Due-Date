// Fill out your copyright notice in the Description page of Project Settings.

#include "ParcelGrabber.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
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
	m_PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();

	// Find physics handle
	m_PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!m_PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle ERROR : Owner = %s"), *GetOwner()->GetName());
	}	
}

void UParcelGrabber::Grab()
{
	m_PhysicsHandle->ReleaseComponent();

	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabbing parcel."));
		m_PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // allow rotation
		);
	}	
}

// Called every frame
void UParcelGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	if (m_PhysicsHandle)
	{
		if (m_PhysicsHandle->GrabbedComponent)
		{
			// Calculate the end of the raycast
			FVector PlayerForward = m_PlayerCharacter->GetActorForwardVector();
			FVector PlayerPosition = m_PlayerCharacter->GetActorLocation();
			FVector LineTraceEnd = PlayerPosition + PlayerForward * m_fReach;

			// Set the targets location to the end of the raycast
			m_PhysicsHandle->SetTargetLocation(FVector(LineTraceEnd.X, LineTraceEnd.Y, LineTraceEnd.Z + 50.0f));
			m_PhysicsHandle->SetTargetRotation(m_PlayerCharacter->GetActorRotation());

			// If the compenent we're holding is being destroyed, release it so we can go pick up another
			if (m_PhysicsHandle->GrabbedComponent->IsBeingDestroyed())
			{
				m_PhysicsHandle->ReleaseComponent();
			}
		}
		else
		{			
			// If we haven't grabbed anything, try grab something!
			Grab();
		}
	}
}

FHitResult UParcelGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerForward = m_PlayerCharacter->GetActorForwardVector();
	FVector PlayerPosition = m_PlayerCharacter->GetActorLocation();	
	FVector LineTraceEnd = PlayerPosition + PlayerForward * m_fReach;

	/*DrawDebugLine(
		GetWorld(),
		PlayerPosition,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);*/

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (ray-cast) out to reach distance
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		FVector(PlayerPosition.X, PlayerPosition.Y, PlayerPosition.Z - 120.0f),
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// See what we hit
	AActor* ActorHit = LineTraceHit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s hit."), *LineTraceHit.GetActor()->GetName());
		return LineTraceHit;
	}	
	else
	{
		return FHitResult();
	}
}

