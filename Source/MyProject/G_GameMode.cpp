// Fill out your copyright notice in the Description page of Project Settings.

#include "G_GameMode.h"

#include "Public/EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


#include "A_Tower.h"
#include "W_MessageWidget.h"

AG_GameMode::AG_GameMode()
{
	GameEnd = false;
}

void AG_GameMode::Tick(float DeltaTime) {}

void AG_GameMode::CheckForWinState()
{
	if (!GameEnd)
	{
		TArray<AA_Tower*> _Towers;
		for (TActorIterator<AA_Tower> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			if (ActorItr)	_Towers.Push(*ActorItr);
		}

		static float LooseIndex;

		for (int32 t = 0; t < _Towers.Num(); t++)
		{

			UE_LOG(LogTemp, Warning, TEXT("Stage: %d"), _Towers[t]->TowerStage);

			if (_Towers[t]->TowerStage < 1.0f)
			{
				LooseIndex = _Towers[t]->TowerIndex;
				GameEnd = true;
				break;
			}
		}

		if (GameEnd)
		{
			if (MessageWidget)
			{
				APlayerController* Pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);

				WidgetRef = CreateWidget<UUserWidget>(Pc, MessageWidget);
				if (WidgetRef)
				{
					WidgetRef->AddToViewport();

					UW_MessageWidget* MWidget = Cast<UW_MessageWidget>(WidgetRef);
					if (MWidget)
					{
						if (LooseIndex == 0) MWidget->DisplayMessage("Red Wins!");
						if (LooseIndex == 1) MWidget->DisplayMessage("Blue Wins!");
					}
				}
			}
		}
	}

}
