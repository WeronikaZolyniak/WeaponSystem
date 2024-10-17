// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "WeaponDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "PointsWidget.h"
#include "WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoCountChangedDelegate, int, CurrentAmmo);

UCLASS()
class WEAPONSYSTEM_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnAmmoCountChangedDelegate BulletCountChangedDelegate;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	void SetWeaponDataAsset(TObjectPtr<UWeaponDataAsset> DataAsset);
	
	int CurrentAmmo;

	void Shoot(float PlayerPitchRotation);
	void Reload();
};
