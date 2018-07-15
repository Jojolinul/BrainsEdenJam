// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "A_Pickup.generated.h"

UCLASS()
class MYPROJECT_API AA_Pickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_Pickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Sphere Component
	UPROPERTY(VisibleDefaultsOnly)
	class USphereComponent* CollisionSphereComponent;

	UPROPERTY(EditAnywhere)
	int componentIndex;

	UPROPERTY(EditAnywhere)
	int sideIndex;

	void Initialise(int componentIndex, int componentSide);

	bool disablePhysics;

	UPROPERTY(EditAnywhere)
		float FreezeZ;
};
