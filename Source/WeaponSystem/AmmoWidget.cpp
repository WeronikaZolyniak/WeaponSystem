// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoWidget.h"

void UAmmoWidget::UpdateMagazineAmmoCountText(int MagazineAmmoCount)
{
	if (MagazineAmmoCountText)
	{
		FString Text = FString::FromInt(MagazineAmmoCount);
		MagazineAmmoCountText->SetText(FText::FromString(Text));
	}
}

void UAmmoWidget::UpdateCurrentAmmoText(int CurrentAmmo)
{
	if (MagazineAmmoCountText)
	{
		FString Text = FString::FromInt(CurrentAmmo);
		CurrentAmmoText->SetText(FText::FromString(Text));
	}
}

void UAmmoWidget::SetOnBulletCountChangedDelegate(AWeaponBase* WeaponBase)
{
	UpdateCurrentAmmoText(WeaponBase->CurrentAmmo);
	UpdateMagazineAmmoCountText(WeaponBase->WeaponDataAsset->MagazineAmmoCount);
	WeaponBase->BulletCountChangedDelegate.AddDynamic(this, &UAmmoWidget::UpdateCurrentAmmoText);
}
