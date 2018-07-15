// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MessageWidget.generated.h"

UCLASS()
class MYPROJECT_API UW_MessageWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

		UFUNCTION(BlueprintImplementableEvent)
		void DisplayMessage(FName Message);
	
	
};
