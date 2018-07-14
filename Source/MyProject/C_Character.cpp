// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Character.h"

#include "Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Blueprint/UserWidget.h"
#include "W_Pickup.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "A_Pickup.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "A_Tower.h"

// Sets default values
AC_Character::AC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Grabber = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("Grabby"));
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseMovementSpeed;

	isMoving = false;
	isStunned = false;

	MaxDurability = 100;
	MidDurability = 30;
	MinDurability = 0;

	Durability = 100;
}

// Called every frame
void AC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckMovement();

	if (isMoving)
	{
		UE_LOG(LogTemp, Warning, TEXT("Durability: %f"), Durability); 
		Durability -= GetWorld()->DeltaTimeSeconds * DecayRate;
	}

	if (Durability <= MinDurability) ApplyStun();

	if (isStunned)
	{
		UE_LOG(LogTemp, Warning, TEXT("Durability: %f"), Durability);
		Durability += GetWorld()->DeltaTimeSeconds * ForceRepairRate;
	}

	if (isStunned && Durability >= 50.0f) RemoveStun();

	CheckFront();

}

// Called to bind functionality to input
void AC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AC_Character::PickUp);
	PlayerInputComponent->BindAxis("Joystick-Up/Down", this, &AC_Character::VerticalMove);
	PlayerInputComponent->BindAxis("Joystick-Left/Right", this, &AC_Character::HorizontalMove);
	PlayerInputComponent->BindAxis("Heal", this, &AC_Character::HealRobot);
}

void AC_Character::VerticalMove(float Value)
{
	if (!isStunned)
	{

		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FVector(0, 1, 0), Value);

		SetRotation();
	}

	if (Value != 0) SetRotation();
}

void AC_Character::HorizontalMove(float Value)
{
	if (!isStunned)
	{

		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(FVector(-1, 0, 0), Value);
	}

	if (Value != 0) SetRotation();
}

void AC_Character::HealRobot(float Value)
{
	if (!isMoving && Value != 0 && Durability <= MaxDurability && !isStunned)
	{
		UE_LOG(LogTemp, Warning, TEXT("Durability: %f"), Durability);
		Durability += GetWorld()->DeltaTimeSeconds * HealRate;
	}
}

void AC_Character::ApplyStun()
{
	isStunned = true;
}

void AC_Character::RemoveStun()
{
	isStunned = false;
}







void AC_Character::CheckMovement()
{
	if (GetVelocity().Size() > 1.0f) isMoving = true;
	else isMoving = false;
}

void AC_Character::SetRotation()
{

	if (GetVelocity().Size() > 100)
	{

		FRotator LookAtRot = (GetActorLocation() - (GetActorLocation() + (-GetVelocity().GetSafeNormal()))).Rotation();

		FMath::RInterpTo(GetActorRotation(), LookAtRot, GetWorld()->DeltaTimeSeconds, 1.0f);

		SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRot, GetWorld()->DeltaTimeSeconds, 12.5f));

	}
}

void AC_Character::CheckFront()
{
	SphereTraceQueryParameters.bTraceAsyncScene = false;
	SphereTraceQueryParameters.bTraceComplex = false;
	SphereTraceQueryParameters.bReturnFaceIndex = false;
	SphereTraceQueryParameters.AddIgnoredActor(this);

	SphereCheckShape = FCollisionShape::MakeSphere(15.0f);
	SphereCollisionChannel = ECC_WorldStatic;

	FQuat SphereCheckRotator = FQuat();

	FHitResult TraceResult(ForceInit);
	GetWorld()->SweepSingleByChannel(TraceResult, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 100), SphereCheckRotator, SphereCollisionChannel, SphereCheckShape, SphereTraceQueryParameters, SphereTraceResponseParameters);


	if (TraceResult.bBlockingHit && !CurrentItem)
	{
		if (TraceResult.Actor != this)
		{
			UKismetSystemLibrary::DrawDebugSphere(GetWorld(), TraceResult.Location, 15.0f, 12, FColor(255, 255, 0), 0, 1);

			if (PickUpWidget && WidgetRef == nullptr)
			{
				WidgetRef = CreateWidget<UUserWidget>(Cast<APlayerController>(Controller), PickUpWidget);
				if (WidgetRef)
				{
					WidgetRef->AddToViewport();
					Cast<UW_Pickup>(WidgetRef)->IniButton(TraceResult.GetActor());
				}
			}
		}
	}
	else if (WidgetRef != nullptr)
	{
		WidgetRef->RemoveFromViewport();
		WidgetRef->RemoveFromParent();
		WidgetRef = nullptr;
	}

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 100), FColor(255, 0, 0), 0, 4);
}

void AC_Character::PickUp()
{

	UE_LOG(LogTemp, Warning, TEXT("PICKUP"));

	SphereTraceQueryParameters.bTraceAsyncScene = false;
	SphereTraceQueryParameters.bTraceComplex = false;
	SphereTraceQueryParameters.bReturnFaceIndex = false;
	SphereTraceQueryParameters.AddIgnoredActor(this);

	SphereCheckShape = FCollisionShape::MakeSphere(15.0f);
	SphereCollisionChannel = ECC_WorldStatic;

	FQuat SphereCheckRotator = FQuat();

	FHitResult TraceResult(ForceInit);

	GetWorld()->SweepSingleByChannel(TraceResult, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 100), SphereCheckRotator, SphereCollisionChannel, SphereCheckShape, SphereTraceQueryParameters, SphereTraceResponseParameters);

	if (TraceResult.bBlockingHit && !CurrentItem)
	{
		const AActor* _OtherActor = Cast<AA_Pickup>(TraceResult.GetActor());
		if (_OtherActor)
		{
			CurrentItem = TraceResult.GetActor();
			CurrentItem->SetActorLocationAndRotation(GetMesh()->GetSocketTransform("Arms").GetLocation(), GetMesh()->GetSocketTransform("Arms").GetRotation());
			Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent())->SetSimulatePhysics(false);
			TraceResult.GetActor()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform, "Arms");
		}

		_OtherActor = Cast<AA_Tower>(TraceResult.GetActor());
		if (_OtherActor)
		{
			Cast<AA_Tower>(TraceResult.GetActor())->DamageTower();
		}
	}
	else if (CurrentItem)
	{
		CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent())->SetSimulatePhysics(true);
		Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent())->SetPhysicsLinearVelocity(FVector::ZeroVector, false);
		CurrentItem = nullptr;
	}
}

void AC_Character::IncreaseSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed += SpeedIncrease;
}

