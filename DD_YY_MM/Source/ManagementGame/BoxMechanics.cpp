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
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UBoxMechanics::UBoxMechanics()
{
	bStartup = true;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//GetOwner()->FindComponentByClass<UStaticMeshComponent>()->OnComponentBeginOverlap.AddDynamic(this, &UBoxMechanics::OnConveyor);
	bOnConvey = false;
	bPickedUp = false;
}


// Called when the game starts
void UBoxMechanics::BeginPlay()
{
	Super::BeginPlay();
	// ...

	m_pMyMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	m_pMyMesh->bGenerateOverlapEvents = true;
	m_pMyMesh->OnComponentBeginOverlap.AddDynamic(this, &UBoxMechanics::OnOverlapBegin);
	m_pMyMesh->OnComponentEndOverlap.AddDynamic(this, &UBoxMechanics::OnOverlapEnd);
}


// Called every frame
void UBoxMechanics::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bOnConvey && !bPickedUp)
	{
		FVector loca = GetOwner()->GetActorLocation();
		//FVector Movement(0.0f,-100000.0f,0.0f);
		//loca = loca + Movement;
		loca.X += 0.4f;
		GetOwner()->SetActorLocation(loca);
		//m_pMyMesh->AddForce(Movement);
	}

	// ...
}

void UBoxMechanics::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Error, TEXT("Box On Belt;"), *GetOwner()->GetName());
	bOnConvey = true; 
	m_pMyMesh->SetSimulatePhysics(false);
}

void UBoxMechanics::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bOnConvey = false;
	m_pMyMesh->SetSimulatePhysics(true);
}




