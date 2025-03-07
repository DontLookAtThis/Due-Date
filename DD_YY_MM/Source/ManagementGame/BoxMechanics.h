// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BoxMechanics.generated.h"

class UStaticMeshComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MANAGEMENTGAME_API UBoxMechanics : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UBoxMechanics();
	bool bOnConvey;
	bool bPickedUp;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	bool bStartup;
	UStaticMeshComponent* m_pMyMesh;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere)
		int iHealth = 1;
	int deathTimer;
	void BreakItem();
};
