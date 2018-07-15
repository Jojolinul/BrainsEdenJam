// Fill out your copyright notice in the Description page of Project Settings.

#include "A_RocketProjectile.h"
#include "A_Tower.h"
#include "Public/EngineUtils.h"


// Sets default values
AA_RocketProjectile::AA_RocketProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setting up the Collision Sphere Component

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->SetSphereRadius(6.0f);
	RootComponent = CollisionComponent;
}

// Called when the game starts or when spawned
void AA_RocketProjectile::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AA_Tower> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)	towerArray.Push(*ActorItr);
	}

	float closestPlayer = 0.0f;
	for (int x = 0; x < towerArray.Num(); x++)
	{
		float temp = FVector::Distance(towerArray[x]->GetActorLocation(), GetActorLocation());
		if (temp > closestPlayer)
		{
			index = x;
			closestPlayer = temp;
		}
	}

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AA_RocketProjectile::SetGoingDown, 1.0f, false, 2.0f);
	endLocation = towerArray[index]->GetActorLocation();
}

void AA_RocketProjectile::GoUp(FVector newLocation)
{
	SetActorLocation(newLocation);
}

void AA_RocketProjectile::GoDown(FVector newLocation)
{
	SetActorLocation(newLocation);
}

// Called every frame
void AA_RocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isGoingUp)
	{
		zPosition += DeltaTime * 600.0f;
		FVector newLocation = FVector(GetActorLocation().X, GetActorLocation().Y, zPosition);
		GoUp(newLocation);
	}
	else 
	{ 
		zPosition -= DeltaTime * 600.0f;
		SetActorRotation(FRotator(-180.0f, 0.0f, 0.0f));
		FVector newLocation = FVector(GetActorLocation().X, GetActorLocation().Y, zPosition);
		GoDown(newLocation);
		TowerCollision();
	}
}


void AA_RocketProjectile::SetGoingDown()
{
	float tempX = endLocation.X;
	float tempY = endLocation.Y;

	SetActorLocation(FVector(tempX, tempY, GetActorLocation().Z));

	isGoingUp = false;
}

void AA_RocketProjectile::TowerCollision()
{
	float distanceToTower = FVector::Distance(endLocation, GetActorLocation());
	if (distanceToTower < 25.0f)
	{
		if (towerArray[index])
		{
			towerArray[index]->DamageTower();
			Destroy();
		}
	}
}

