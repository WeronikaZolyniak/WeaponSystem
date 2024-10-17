// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PointsWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UPointsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPointsText(int points);
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PointsText;
};
