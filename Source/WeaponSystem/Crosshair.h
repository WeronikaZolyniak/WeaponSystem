// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Crosshair.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* Image;
};
