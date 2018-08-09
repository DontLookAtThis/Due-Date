// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include <string>
#include "ItemBin.generated.h"

UENUM(BlueprintType)
enum class EBinType : uint8
{
	BT_Box UMETA(DisplayName="Box Bin"),
	BT_Crate UMETA(DisplayName = "Crate Bin"),
	BT_Parcel UMETA(DisplayName = "Parcel Bin")
};

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

	//// Blueprint pointers
	// Actor pointer to the blueprint of the parcel
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ParcelBlueprint;
	// Actor pointer to the blueprint of the crate
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> CrateBlueprint;
	// Actor pointer to the blueprint of the box
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> BoxBlueprint;

	// enum variable to contain the type of Bin this is
	UPROPERTY(EditAnywhere, Category=Enum)
	EBinType TypeOfBin;
	// Array to contain the instances of the blueprint found in the scene
	TArray<AActor*> FoundActors;	

	// Pointer to world
	UWorld* WorldPointer;


};
