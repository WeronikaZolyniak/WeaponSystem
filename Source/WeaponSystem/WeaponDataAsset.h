// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/StaticMesh.h"
#include "Sound/SoundWave.h"
#include "WeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* GunshotSound;

	UPROPERTY(EditDefaultsOnly)
	USoundWave* ReloadSound;

	//range from 0.1 to 0.99
	UPROPERTY(EditDefaultsOnly)
	float Zoom;

	UPROPERTY(EditDefaultsOnly)
	int BulletSpeedInMetresPerSecond;

	UPROPERTY(EditDefaultsOnly)
	int ReloadTimeinSec;

	UPROPERTY(EditDefaultsOnly)
	int MagazineAmmoCount;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BulletHoleMaterial;
};
