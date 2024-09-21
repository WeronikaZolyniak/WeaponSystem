// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::SetWeaponDataAsset(TObjectPtr<UWeaponDataAsset> DataAsset)
{
	WeaponDataAsset = DataAsset;
	Mesh->SetStaticMesh(WeaponDataAsset->Mesh);
	CurrentAmmo = WeaponDataAsset->MagazineAmmoCount;
}

void AWeaponBase::Shoot()
{
	if (CurrentAmmo > 0)
	{
		CurrentAmmo--;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponDataAsset->GunshotSound, GetActorLocation());
		BulletCountChangedDelegate.Broadcast(CurrentAmmo);
	}
}

void AWeaponBase::Reload()
{
	if (CurrentAmmo == WeaponDataAsset->MagazineAmmoCount) return;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WeaponDataAsset->ReloadSound, GetActorLocation());

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
	{
			CurrentAmmo = WeaponDataAsset->MagazineAmmoCount;
			BulletCountChangedDelegate.Broadcast(WeaponDataAsset->MagazineAmmoCount);
	}, WeaponDataAsset->ReloadTimeinSec, false);
}

