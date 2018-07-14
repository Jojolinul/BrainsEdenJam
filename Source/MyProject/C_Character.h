// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Character.h"
#include "C_Character.generated.h"

UCLASS()
class MYPROJECT_API AC_Character : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	AC_Character();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	float Durability;

	float MaxDurability;
	float MidDurability;
	float MinDurability;

	bool isMoving;

	UPROPERTY(BlueprintReadOnly)
	bool isStunned;

	UPROPERTY(EditDefaultsOnly)
	UPhysicsHandleComponent* Grabber;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void VerticalMove(float Value);
	void HorizontalMove(float Value);
	void HealRobot(float Value);

	void ApplyStun();
	void RemoveStun();

	FTimerHandle Stun_Timehandle;

	UPROPERTY(EditDefaultsOnly)
	float DecayRate;

	UPROPERTY(EditDefaultsOnly)
	float HealRate;

	UPROPERTY(EditDefaultsOnly)
	float ForceRepairRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PickUpWidget;

	class UUserWidget* WidgetRef;

private:

	void CheckMovement();

	void SetRotation();

	void CheckFront();

	void PickUp();

	FCollisionQueryParams SphereTraceQueryParameters;
	FCollisionResponseParams SphereTraceResponseParameters;
	FCollisionShape SphereCheckShape;
	ECollisionChannel SphereCollisionChannel;

	AActor* CurrentItem;

	bool Holding;
};
