// Fill out your copyright notice in the Description page of Project Settings.

#include "TempCharacterActor.h"


// Sets default values
ATempCharacterActor::ATempCharacterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATempCharacterActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATempCharacterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

