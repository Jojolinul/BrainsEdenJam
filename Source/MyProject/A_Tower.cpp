// Fill out your copyright notice in the Description page of Project Settings.

#include "A_Tower.h"
#include "C_Character.h"
#include "DestructibleComponent.h"
#include "G_GameMode.h"

// Sets default values
AA_Tower::AA_Tower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FakeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = FakeRoot;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);

	StageOne = CreateDefaultSubobject<UDestructibleComponent>(TEXT("TowerBottom"));
	StageOne->SetupAttachment(RootComponent);

	StageTwo = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Tower Middle"));
	StageTwo->SetupAttachment(RootComponent);

	StageThree = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Tower Top"));
	StageThree->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AA_Tower::BeginPlay()
{
	Super::BeginPlay();

	TowerStage = 3;

	if (isMainPlayer)
	{
		UGameplayStatics::GetPlayerController(GetWorld(), TowerIndex)->Possess(SpawnPlayer());
	}
	else
	{
		UGameplayStatics::CreatePlayer(GetWorld())->Possess(SpawnPlayer());
	}
	
}

APawn* AA_Tower::SpawnPlayer()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = UGameplayStatics::GetPlayerCharacter(GetWorld(), TowerIndex);

	if (PlayerBP != NULL)
	{
		PlayerRef = GetWorld()->SpawnActor<AC_Character>(PlayerBP, SpawnVetor, SpawnRotator, SpawnParams);
	}

	return PlayerRef;
}

void AA_Tower::DamageTower()
{
	if (TowerStage == 3) StageThree->ApplyDamage(1000.0f, StageThree->GetComponentLocation() + FVector(0, 0, 100), FVector(1, 0, 0), 1000.0f); 	
	if (TowerStage == 2) StageTwo->ApplyDamage(1000.0f, StageTwo->GetComponentLocation() + FVector(0, 0, 100), FVector(1, 0, 0), 1000.0f);
	if (TowerStage == 1) StageOne->ApplyDamage(1000.0f, StageOne->GetComponentLocation() + FVector(0, 0, 100), FVector(1, 0, 0), 1000.0f);

	TowerStage -= 1;
	
	PlayerRef->IncreaseSpeed();

	GetWorldTimerManager().SetTimer(Hide_Timehandle, this, &AA_Tower::RemoveDeb, 3.0f);

	AG_GameMode* _GameMode = Cast<AG_GameMode>(GetWorld()->GetAuthGameMode());
	if (_GameMode)
	{
		_GameMode->CheckForWinState();
	}
}

void AA_Tower::RemoveDeb()
{
	if (TowerStage == 2)
	{
		StageThree->SetHiddenInGame(true);
		StageThree->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (TowerStage == 1)
	{
		StageTwo->SetHiddenInGame(true);
		StageTwo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (TowerStage == 0)
	{
		StageOne->SetHiddenInGame(true);
		StageOne->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called every frame
void AA_Tower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

