// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AmmoWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMagazineAmmoCountText(int MagazineAmmoCount);

	void UpdateCurrentAmmoText(int CurrentAmmo);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* MagazineAmmoCountText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentAmmoText;
};
