// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Tower.generated.h"

UCLASS()
class MYPROJECT_API AA_Tower : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AA_Tower();

	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* Base;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* FakeRoot;

	UPROPERTY(VisibleDefaultsOnly)
		class UDestructibleComponent* StageOne;

	UPROPERTY(VisibleDefaultsOnly)
		class UDestructibleComponent* StageTwo;

	UPROPERTY(VisibleDefaultsOnly)
		class UDestructibleComponent* StageThree;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* _SpawnLocation;

	int32 TowerStage;

	void DamageTower();

	void RemoveDeb();

	FTimerHandle Hide_Timehandle;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	APawn* SpawnPlayer();


public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	bool isMainPlayer;

	UPROPERTY(EditAnywhere)
	int32 TowerIndex;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AC_Character> PlayerBP;

private:

	AC_Character* PlayerRef;



	
	
};
