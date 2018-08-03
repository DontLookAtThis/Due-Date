// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ItemBin.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANAGEMENTGAME_API UItemBin : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemBin();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Pointer to the trigger volume that will destroy the parcel upon overlap
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	// Actor pointer to the blueprint of the parcel
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ParcelBlueprint;

	// Array to contain the instances of the blueprint found in the scene
	TArray<AActor*> FoundActors;	

	// Pointer to world
	UWorld* WorldPointer;
};
