// Fill out your copyright notice in the Description page of Project Settings.

#include "A_RocketProjectile.h"
#include "TempCharacterActor.h"
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

	// Setting up the Projectile Movement Component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = GetRootComponent();
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bInitialVelocityInLocalSpace = true;
	ProjectileMovement->bIsHomingProjectile = false;
}

// Called when the game starts or when spawned
void AA_RocketProjectile::BeginPlay()
{
	Super::BeginPlay();

	TArray<ATempCharacterActor*> playerArray;
	for (TActorIterator<ATempCharacterActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)	playerArray.Push(*ActorItr);
	}

	float closestPlayer = INFINITY;
	int index = INFINITY;
	for (int x = 0; x < playerArray.Num(); x++)
	{
		float temp = FVector::Distance(playerArray[x]->GetActorLocation(), GetActorLocation());
		if (temp < closestPlayer)
		{
			index = x;
			closestPlayer = temp;
		}
	}

	ProjectileMovement->HomingTargetComponent = playerArray[index]->GetRootComponent();

	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AA_RocketProjectile::SetHoming, 0.0f, false, 2.0f);
}

void AA_RocketProjectile::SetHoming()
{
	ProjectileMovement->bIsHomingProjectile = true;
}

// Called every frame
void AA_RocketProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

