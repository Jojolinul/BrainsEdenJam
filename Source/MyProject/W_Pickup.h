// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Pickup.generated.h"

UCLASS()
class MYPROJECT_API UW_Pickup : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void IniButton(AActor* Location);
	
	
};
