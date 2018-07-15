// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Pickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AA_Pickup::AA_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting up the Collision Sphere Component
	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = CollisionSphereComponent;

	disablePhysics = false;

}

// Called when the game starts or when spawned
void AA_Pickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AA_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (!disablePhysics)
	{
		if (GetActorLocation().Z <= FreezeZ)
		{
			UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(GetRootComponent());
			if (Prim)
			{
				Prim->SetSimulatePhysics(false);
			}
		}
	}
}

void AA_Pickup::Initialise(int cI, int sI)
{
	componentIndex = cI;
	sideIndex = sI;
}

