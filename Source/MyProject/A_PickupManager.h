// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "A_Pickup.h"
#include "GameFramework/Actor.h"
#include "A_PickupManager.generated.h"

#define MAXCOMPONENTS 4

enum SPAWNCOMPONENT
{
	TOP,
	MIDDLE,
	BOTTOM,
	FUEL
};

enum SIDECOMPONENT
{
	LEFT,
	RIGHT
};

UCLASS()
class MYPROJECT_API AA_PickupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_PickupManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Bot Projectile
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AA_Pickup> RocketComponent_Top;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AA_Pickup> RocketComponent_Middle;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AA_Pickup> RocketComponent_Bottom;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AA_Pickup> RocketComponent_Fuel;

	UPROPERTY(EditAnywhere)
	FVector leftSpawnRange;
	UPROPERTY(EditAnywhere)
	FVector leftSpawnPosition;

	UPROPERTY(EditAnywhere)
	FVector rightSpawnRange;
	UPROPERTY(EditAnywhere)
	FVector rightSpawnPosition;

	void CheckRocketComponents();
	void SpawnRocketComponents(int componentIndex, int componentSide);
	FVector SpawnLocation(int componentSide);
};
