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

	UPROPERTY(EditDefaultsOnly)
	int Zoom;

	UPROPERTY(EditDefaultsOnly)
	int Range;

	UPROPERTY(EditDefaultsOnly)
	int ReloadTimeinSec;


};
