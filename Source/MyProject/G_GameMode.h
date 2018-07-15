// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "G_GameMode.generated.h"

UCLASS()
class MYPROJECT_API AG_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	AG_GameMode();

public:

	virtual void Tick(float DeltaTime) override;

	void CheckForWinState();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MessageWidget;

	class UUserWidget* WidgetRef;

private:

	bool GameEnd;
	
	
};
