// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Component.generated.h"

UCLASS()
class MYPROJECT_API AA_Component : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AA_Component();

	virtual void PostInitializeComponents();

	UPROPERTY(EditDefaultsOnly, Category = "ComponentSettings")
	TArray<UStaticMesh*> ComponentMeshes;

	bool InitComponent(int32 ComponentIndex);


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* Mesh;

	int32 ComponentIndex;


	
	
};
