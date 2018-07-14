// Fill out your copyright notice in the Description page of Project Settings.

#include "A_PickupZone.h"
#include "Engine/World.h"

// Sets default values
AA_PickupZone::AA_PickupZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("PickUpVolume"));
	Volume->SetCollisionObjectType(ECC_WorldStatic);
	Volume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	RootComponent = Volume;
}

void AA_PickupZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Volume->SetBoxExtent(FVector(VolumeX, VolumeY, 10.0f));
}

// Called when the game starts or when spawned
void AA_PickupZone::BeginPlay()
{
	Super::BeginPlay();
	Volume->SetBoxExtent(FVector(VolumeX, VolumeY, 10.0f));
}

// Called every frame
void AA_PickupZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckOverlapPickups();
}

void AA_PickupZone::CheckOverlapPickups()
{
	TArray<AActor*> PickupsIn;
	GetOverlappingActors(PickupsIn, TSubclassOf<AA_Pickup>());
	if (PickupsIn.Num() == 4)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AA_RocketProjectile* Rocket = GetWorld()->SpawnActor<AA_RocketProjectile>(RocketBP, rocketLocation, FRotator::ZeroRotator, SpawnInfo);

		for (int x = 0; x < PickupsIn.Num(); x++)
		{
			if (PickupsIn[x])
			{
				PickupsIn[x]->Destroy();
			}
		}
	}
}

