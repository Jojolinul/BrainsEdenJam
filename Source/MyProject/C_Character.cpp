// Fill out your copyright notice in the Description page of Project Settings.

#include "C_Character.h"

#include "Public/TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Blueprint/UserWidget.h"
#include "W_Pickup.h"

// Sets default values
AC_Character::AC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AC_Character::BeginPlay()
{
	Super::BeginPlay();

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

	PlayerInputComponent->BindAxis("Joystick-Up/Down", this, &AC_Character::VerticalMove);
	PlayerInputComponent->BindAxis("Joystick-Left/Right", this, &AC_Character::HorizontalMove);
	PlayerInputComponent->BindAxis("Heal", this, &AC_Character::HealRobot);
}

void AC_Character::VerticalMove(float Value)
{
	if (!isStunned)
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);

		SetRotation();
	}

	if (Value != 0) SetRotation();
}

void AC_Character::HorizontalMove(float Value)
{
	if (!isStunned)
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(-Direction, Value);
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

	//if (Durability < MidDurability) CharacterMovement->MaxWalkSpeed = 100.f;
	//else CharacterMovement()->MaxWalkSpeed = 150.f;
}

void AC_Character::SetRotation()
{

	if (GetVelocity().Size() > 100)
	{

		FRotator LookAtRot = (GetActorLocation() - (GetActorLocation() + (-GetVelocity().GetSafeNormal()))).Rotation();

		FMath::RInterpTo(GetActorRotation(), LookAtRot, GetWorld()->DeltaTimeSeconds, 1.0f);

		SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRot, GetWorld()->DeltaTimeSeconds, 20.0f));

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

	//TArray<FHitResult> TraceResult;
	FHitResult TraceResult(ForceInit);
	//GetWorld()->SweepSingleByChannel(TraceResult, Start, End, SphereCheckRotator, SphereCollisionChannel, SphereCheckShape, SphereTraceQueryParameters, SphereTraceResponseParameters);

	//GetWorld()->SweepMultiByChannel(TraceResult, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 100), SphereCheckRotator, SphereCollisionChannel, SphereCheckShape, SphereTraceQueryParameters, SphereTraceResponseParameters);
	GetWorld()->SweepSingleByChannel(TraceResult, GetActorLocation(), GetActorLocation() + (GetActorForwardVector() * 100), SphereCheckRotator, SphereCollisionChannel, SphereCheckShape, SphereTraceQueryParameters, SphereTraceResponseParameters);

	//for (size_t i = 0; i < TraceResult.Num(); i++)
	//{
	//	if (TraceResult[i].bBlockingHit && TraceResult[i].GetActor() != this)
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("ADSADAS"));
	//		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), TraceResult[i].Location, 15.0f, 12, FColor(255, 255, 0), 0, 1);

	//		if (PickUpWidget && WidgetRef == nullptr)
	//		{
	//			WidgetRef = CreateWidget<UUserWidget>(Cast<APlayerController>(Controller), PickUpWidget);
	//			if (WidgetRef)
	//			{
	//				WidgetRef->AddToViewport();
	//				Cast<UW_Pickup>(WidgetRef)->IniButton(TraceResult[i].GetActor()->GetActorLocation());
	//			}
	//		}
	//	}
	//	else if (WidgetRef != nullptr && TraceResult.Num() < 1)
	//	{
	//		WidgetRef->RemoveFromViewport();
	//		WidgetRef->RemoveFromParent();
	//		WidgetRef = nullptr;
	//	}
	//}

	if (TraceResult.bBlockingHit)
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
					Cast<UW_Pickup>(WidgetRef)->IniButton(TraceResult.GetActor()->GetActorLocation());
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

