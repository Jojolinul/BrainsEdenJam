// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Component.h"


// Sets default values
AA_Component::AA_Component()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ComponentMesh"));
	Mesh->SetSimulatePhysics(true);
	//RootComponent = Mesh;
}

void AA_Component::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

bool AA_Component::InitComponent(int32 _ComponentIndex)
{
	if (!ComponentMeshes[_ComponentIndex]) return false;

	Mesh->SetStaticMesh(ComponentMeshes[_ComponentIndex]);
	ComponentIndex = _ComponentIndex;

	return true;
}

// Called when the game starts or when spawned
void AA_Component::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Component::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

