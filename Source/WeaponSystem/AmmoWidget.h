// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "WeaponBase.h"
#include "AmmoWidget.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void UpdateMagazineAmmoCountText(int MagazineAmmoCount);

	UFUNCTION()
	void UpdateCurrentAmmoText(int CurrentAmmo);

	void SetOnBulletCountChangedDelegate(AWeaponBase* WeaponBase);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* MagazineAmmoCountText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentAmmoText;
};
