// Fill out your copyright notice in the Description page of Project Settings.

#include "ParcelGrabber.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ManagementGamePlayerController.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include <iostream>
#include "BoxMechanics.h"
#include <memory>
//#include "BoxMechanics.h"
// Sets default values for this component's properties
UParcelGrabber::UParcelGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	iGrabTimer = 0;
	// ...
}


// Called when the game starts
void UParcelGrabber::BeginPlay()
{
	Super::BeginPlay();
	m_PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetCharacter();
	m_pInputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	// Find physics handle
	m_PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!m_PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle ERROR : Owner = %s"), *GetOwner()->GetName());
	}	
	if (m_pInputComp)
	{
		m_pInputComp->BindAction("Grab&Release", IE_Pressed, this, &UParcelGrabber::OnSetGrabPressed);
		m_pInputComp->BindAction("Grab&Release", IE_Released, this, &UParcelGrabber::OnSetGrabRelease);

		m_pInputComp->BindAction("Yeet", IE_Pressed, this, &UParcelGrabber::OnSetYeetPressed);
		m_pInputComp->BindAction("Yeet", IE_Released, this, &UParcelGrabber::OnSetYeetReleased);
	}
}

void UParcelGrabber::OnSetGrabPressed()
{
	bGrabbing = true;
}
void UParcelGrabber::OnSetGrabRelease()
{
	bGrabbing = false;
}

void UParcelGrabber::OnSetYeetPressed()
{
	if (m_PhysicsHandle->GrabbedComponent != nullptr)
	{
		UPrimitiveComponent* GrabbedComp = m_PhysicsHandle->GrabbedComponent;
		UPrimitiveComponent* thrownitem = m_PhysicsHandle->GrabbedComponent;
		m_PhysicsHandle->ReleaseComponent();
		if (thrownitem)
		{
			thrownitem->SetSimulatePhysics(false);
			thrownitem->SetSimulatePhysics(true);
		}
		FVector YEET = m_PlayerCharacter->GetActorForwardVector();
		YEET.Z += 0.5f;
		GrabbedComp->AddImpulse(YEET * 1500.0f, NAME_None, true);

	}
}

void UParcelGrabber::OnSetYeetReleased()
{

}

void UParcelGrabber::Grab()
{
	UPrimitiveComponent* thrownitem = m_PhysicsHandle->GrabbedComponent;
	m_PhysicsHandle->ReleaseComponent();
	if (thrownitem)
	{
		thrownitem->SetSimulatePhysics(false);
		thrownitem->SetSimulatePhysics(true);
	}
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	
	if (ActorHit)
	{
		ActorHit->FindComponentByClass<UBoxMechanics>()->bPickedUp = true;
		ActorHit->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
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
		/*DrawDebugLine(
		GetWorld(),
		DebugPlayerPosition,
		DebugLineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
		);*/

		if (m_PhysicsHandle->GrabbedComponent)
		{
			// Calculate the end of the raycast
			FVector PlayerForward = m_PlayerCharacter->GetActorForwardVector();
			FVector PlayerPosition = m_PlayerCharacter->GetActorLocation();
			FVector LineTraceEnd = PlayerPosition + PlayerForward * m_fReach;

			UE_LOG(LogTemp, Warning, TEXT("GrabbedComponent FName: %s"), *m_PhysicsHandle->GrabbedComponent->GetReadableName());
			//m_PhysicsHandle->GrabbedComponent->GetReadableName

			// Set the targets location to the end of the raycast
			m_PhysicsHandle->SetTargetLocation(FVector(LineTraceEnd.X, LineTraceEnd.Y, LineTraceEnd.Z + 50.0f));
			m_PhysicsHandle->SetTargetRotation(m_PlayerCharacter->GetActorRotation());

			// If the compenent we're holding is being destroyed, release it so we can go pick up another
			if (m_PhysicsHandle->GrabbedComponent->IsBeingDestroyed())
			{
				m_PhysicsHandle->ReleaseComponent();
			}
		}
		else if(bGrabbing)
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

	// Debug Box Trace
	//DrawDebugBox(
	//	GetWorld(),
	//	LineTraceEnd,
	//	FVector(50, 50, 50),
	//	FColor::Purple,
	//	false,
	//	-1,
	//	0,
	//	10.0f
	//);

	// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Box-trace (ray-cast) out to reach distance
	FHitResult LineTraceHit;
	FCollisionShape Shape = FCollisionShape::MakeBox(FVector(50.0f, 50.0f, 50.0f));
	GetWorld()->SweepSingleByObjectType(
		LineTraceHit,
		PlayerPosition,
		LineTraceEnd,
		FQuat(),
		ECollisionChannel::ECC_PhysicsBody,
		Shape,
		FCollisionQueryParams()			
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

