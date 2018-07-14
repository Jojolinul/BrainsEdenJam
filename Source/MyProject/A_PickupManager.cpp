// Fill out your copyright notice in the Description page of Project Settings.

#include "A_PickupManager.h"
#include "Public/EngineUtils.h"
#include "Engine/World.h"


// Sets default values
AA_PickupManager::AA_PickupManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AA_PickupManager::BeginPlay()
{
	Super::BeginPlay();
	CheckRocketComponents();
	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AA_PickupManager::CheckRocketComponents, 3.0f, true);
}

// Called every frame
void AA_PickupManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_PickupManager::CheckRocketComponents()
{
	TArray<AA_Pickup*> pickupArray;
	for (TActorIterator<AA_Pickup> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if(ActorItr)	pickupArray.Push(*ActorItr);
	}

	TArray<AA_Pickup*> leftPickupArray;
	TArray<AA_Pickup*> rightPickupArray;
	TArray<int> PickupIndex = { 0, 1, 2, 3 };

	for (int8 i = 0; i < pickupArray.Num(); i++)
	{
		if (pickupArray[i]->sideIndex != SIDECOMPONENT::RIGHT)
		{
			leftPickupArray.Push(pickupArray[i]);
			UE_LOG(LogTemp, Warning, TEXT("Left Pickup Array Number %d"), pickupArray[i]->componentIndex);
		}
		else
		{
			rightPickupArray.Push(pickupArray[i]);
			UE_LOG(LogTemp, Warning, TEXT("Right Pickup Array Number %d"), pickupArray[i]->componentIndex);
		}
	}

	TArray<int> leftIndex;
	for (int x = 0; x < leftPickupArray.Num(); x++)
	{
		leftIndex.Push(leftPickupArray[x]->componentIndex);
	}
	TArray<int> rightIndex;
	for (int x = 0; x < rightPickupArray.Num(); x++)
	{
		rightIndex.Push(rightPickupArray[x]->componentIndex);
	}

	for (int8 i = 0; i < PickupIndex.Num(); i++)
	{
		if (!leftIndex.Contains(i))
		{
			SpawnRocketComponents(i, SIDECOMPONENT::LEFT);
			leftIndex.Push(i);
		}
		if (!rightIndex.Contains(i))
		{
			SpawnRocketComponents(i, SIDECOMPONENT::RIGHT);
			rightIndex.Push(i);
		}
	}
}

void AA_PickupManager::SpawnRocketComponents(int componentIndex, int componentSide)
{
	FActorSpawnParameters fSpawn;
	FVector spawnLocation = SpawnLocation(componentSide);
	if (componentIndex == SPAWNCOMPONENT::TOP)
	{
		AA_Pickup* Temp = GetWorld()->SpawnActor<AA_Pickup>(RocketComponent_Top, spawnLocation, FRotator::ZeroRotator, fSpawn);
		Temp->Initialise(componentIndex, componentSide);
	}

	if (componentIndex == SPAWNCOMPONENT::MIDDLE)
	{
		AA_Pickup* Temp = GetWorld()->SpawnActor<AA_Pickup>(RocketComponent_Middle, spawnLocation, FRotator::ZeroRotator, fSpawn);
		Temp->Initialise(componentIndex, componentSide);
	}

	if (componentIndex == SPAWNCOMPONENT::BOTTOM)
	{
		AA_Pickup* Temp = GetWorld()->SpawnActor<AA_Pickup>(RocketComponent_Bottom, spawnLocation, FRotator::ZeroRotator, fSpawn);
		Temp->Initialise(componentIndex, componentSide);
	}

	if (componentIndex == SPAWNCOMPONENT::FUEL)
	{
		AA_Pickup* Temp = GetWorld()->SpawnActor<AA_Pickup>(RocketComponent_Fuel, spawnLocation, FRotator::ZeroRotator, fSpawn);
		Temp->Initialise(componentIndex, componentSide);
	}
}

FVector AA_PickupManager::SpawnLocation(int componentSide)
{
	FVector spawnLocation;
	if (componentSide == SIDECOMPONENT::LEFT)
	{
		spawnLocation.X = FMath::RandRange(leftSpawnPosition.X - leftSpawnRange.X, leftSpawnPosition.X + leftSpawnRange.X);
		spawnLocation.Y = FMath::RandRange(leftSpawnPosition.Y - leftSpawnRange.Y, leftSpawnPosition.Y + leftSpawnRange.Y);
	}
	else
	{
		spawnLocation.X = FMath::RandRange(rightSpawnPosition.X - rightSpawnRange.X, rightSpawnPosition.X + rightSpawnRange.X);
		spawnLocation.Y = FMath::RandRange(rightSpawnPosition.Y - rightSpawnRange.Y, rightSpawnPosition.Y + rightSpawnRange.Y);
	}
	return spawnLocation;
}

