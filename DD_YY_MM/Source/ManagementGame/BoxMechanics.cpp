// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxMechanics.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UBoxMechanics::UBoxMechanics()
{
	bStartup = true;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//GetOwner()->FindComponentByClass<UStaticMeshComponent>()->OnComponentBeginOverlap.AddDynamic(this, &UBoxMechanics::OnConveyor);
}


// Called when the game starts
void UBoxMechanics::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBoxMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bStartup)
	{
		//myActor = GetOwner();
		//myMesh = myActor->FindComponentByClass<UStaticMeshComponent>();
		//myMesh->OnComponentBeginOverlap.AddDynamic(this, &UBoxMechanics::OnConveyor);
	}

	// ...
}

void UBoxMechanics::OnConveyor()
{
}





