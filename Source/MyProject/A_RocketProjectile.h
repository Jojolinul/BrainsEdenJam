// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "A_Tower.h"
#include "A_RocketProjectile.generated.h"

UCLASS()
class MYPROJECT_API AA_RocketProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_RocketProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Sphere Component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComponent;
	
	void GoUp(FVector newLocation);
	void GoDown(FVector newLocation);
	void SetGoingDown();
	void TowerCollision();

	float zPosition = 0.0f;
	int index = INFINITY;
	TArray<AA_Tower*> towerArray;

	FVector endLocation;
	bool isGoingUp = true;

};
