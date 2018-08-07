// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBin.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
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
	WorldPointer = GetWorld();
	//Owner = GetOwner();
}


// Called every frame
void UItemBin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get all parcels that exist in the scene	
	for (TActorIterator<AActor> It(WorldPointer, ParcelBlueprint); It; ++It)
	{
		if (PressurePlate->IsOverlappingActor(*It))
		{
			UE_LOG(LogTemp, Warning, TEXT("Parcel placed in bin."));
			(*It)->Destroy(); // UNCOMMENT THIS
			(*It)->DestroyConstructedComponents();
		}
	}
	// Get all crates that exist in the scene	
	for (TActorIterator<AActor> It(WorldPointer, CrateBlueprint); It; ++It)
	{
		if (PressurePlate->IsOverlappingActor(*It))
		{
			UE_LOG(LogTemp, Warning, TEXT("Crate placed in bin."));
			(*It)->Destroy(); // UNCOMMENT THIS
			(*It)->DestroyConstructedComponents();
		}
	}
	// Get all boxes that exist in the scene	
	for (TActorIterator<AActor> It(WorldPointer, BoxBlueprint); It; ++It)
	{
		if (PressurePlate->IsOverlappingActor(*It))
		{
			UE_LOG(LogTemp, Warning, TEXT("Box placed in bin."));
			(*It)->Destroy(); // UNCOMMENT THIS
			(*It)->DestroyConstructedComponents();
		}
	}
}

//// BELOW FUNCTIONS ARE UNTESTED

// UnrealEngine Answers - User: Xenojiva
//template<typename T>
//void FindAllActors(UWorld* World, TArray<T*>& Out)
//{
//	for (TActorIterator<AActor> It(World, T::StaticClass()); It; ++It)
//	{
//		T* Actor = Cast<T>(*It);
//		if (Actor && !Actor->IsPendingKill())
//		{
//			Out.Add(Actor);
//		}
//	}
//}

// Same as above but with a blueprint class to find 
//template<typename T>
//void FindAllActors(UWorld* World, TArray<T*>& Out, TSubclassOf<AActor> ClassToFind)
//{
//	for (TActorIterator<AActor> It(World, ClassToFind); It; ++It)
//	{
//		T* Actor = Cast<T>(*It);
//		if (Actor && !Actor->IsPendingKill())
//		{
//			Out.Add(Actor);
//		}
//	}
//}