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
#include <string>
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UBoxMechanics::UBoxMechanics()
{
	deathTimer = 60;
	bStartup = true;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//GetOwner()->FindComponentByClass<UStaticMeshComponent>()->OnComponentBeginOverlap.AddDynamic(this, &UBoxMechanics::OnConveyor);
	bOnConvey = false;
	bPickedUp = false;
	//if (iBoxType == 1)
	//{
	//	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Parcel_Assets/Small_Box/DestrucibleFragileBox.DestrucibleFragileBox'"));
	//	if (ItemBlueprint.Object) {
	//		DestrucitbleBox = (UClass*)ItemBlueprint.Object->GeneratedClass;
	//	}
	//}
	//else if(iBoxType == 2)
	//{
	//	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Parcel_Assets/NormalParcel/3rdBoxDestructible.3rdBoxDestructible'"));
	//	if (ItemBlueprint.Object) {
	//		DestrucitbleBox = (UClass*)ItemBlueprint.Object->GeneratedClass;
	//	}
	//}
	//else if(iBoxType == 3)
	//{
	//	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Parcel_Assets/Crate/CrateDestructible.CrateDestructible'"));
	//	if (ItemBlueprint.Object) {
	//		DestrucitbleBox = (UClass*)ItemBlueprint.Object->GeneratedClass;
	//	}
	//}
}


// Called when the game starts
void UBoxMechanics::BeginPlay()
{
	Super::BeginPlay();
	// ...
	//m_pMyBoxCollider = GetOwner()->FindComponentByClass<UBoxComponent>();
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
		FVector Movement(-100000.0f, 0.0f, 0.0f);
		//loca = loca + Movement;
		loca.X += 2.0f;
		GetOwner()->SetActorLocation(loca);
		//m_pMyMesh->AddForce(Movement);
	}
	//BreakItem();
	//if (bOnConvey)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("boolOncConvey: True"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("boolOncConvey: False"));
	//}
	//if (bPickedUp)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("boolPickedUP : True"));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("boolPickedUP : False"));
	//}
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

void UBoxMechanics::BreakItem()
{
	//if (iHealth <= 0)
	//{
	//	deathTimer--;
	//}
	//if (deathTimer <= 0)
	//{
		FActorSpawnParameters params;
		params.Owner = GetOwner();

		FRotator rotation = GetOwner()->GetActorRotation();
		FVector location = GetOwner()->GetActorLocation();


		GetWorld()->SpawnActor<AActor>(DestrucitbleBox, location, rotation);
		GetOwner()->Destroy();
	//}
}




