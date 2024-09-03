// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "WeaponDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "AmmoWidget.h"
#include "WeaponBase.generated.h"

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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWeaponDataAsset> WeaponDataAsset;

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	void SetWeaponDataAsset(TObjectPtr<UWeaponDataAsset> DataAsset);
	void SetAmmoWidget(UAmmoWidget* AmmoWidgetToSet);
	
	int CurrentAmmo;
	UAmmoWidget* AmmoWidget;

	void Shoot();
};
