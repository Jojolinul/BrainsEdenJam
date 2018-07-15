// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Pickup.h"
#include "Components/BoxComponent.h"
#include "A_RocketProjectile.h"
#include "A_PickupZone.generated.h"

UCLASS()
class MYPROJECT_API AA_PickupZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_PickupZone();

	UPROPERTY(EditAnywhere)
	float VolumeX;

	UPROPERTY(EditAnywhere)
	float VolumeY;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* Volume;

	//Allow Actors To Initialize Themselves.
	virtual void PostInitializeComponents();
	void CheckOverlapPickups();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AA_RocketProjectile> RocketBP;

	UPROPERTY(EditAnywhere)
	FVector rocketLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
