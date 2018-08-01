// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBin.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UItemBin::UItemBin()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemBin::BeginPlay()
{
	Super::BeginPlay();

	ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UItemBin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume
	if (PressurePlate->IsOverlappingActor(ActorThatTriggers))
	{
		// Place parcel in bin
	}
}

