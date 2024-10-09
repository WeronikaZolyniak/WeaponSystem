// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonPlayer.h"

// Sets default values
AFirstPersonPlayer::AFirstPersonPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetRelativeLocation(FVector(0, 0, 55));
	SpringArm->TargetArmLength = 0;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	WeaponSocket = CreateDefaultSubobject<USceneComponent>(FName("WeaponSocket"));
	WeaponSocket->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AFirstPersonPlayer::BeginPlay()
{
	Super::BeginPlay();
	CrosshairWidget = CreateWidget<UCrosshair>(GetWorld(), CrosshairClass);

	AmmoWidget = CreateWidget<UAmmoWidget>(GetWorld(), AmmoWidgetClass);
	AmmoWidget->AddToViewport();

	FActorSpawnParameters SpawnParameters;
	WeaponActor = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(), WeaponSocket->GetComponentLocation(), WeaponSocket->GetComponentRotation(), SpawnParameters);
	if (WeaponActor == nullptr) return;
	if (WeaponDataAsset != nullptr)
	{
		WeaponActor->SetWeaponDataAsset(WeaponDataAsset);
		AmmoWidget->SetOnBulletCountChangedDelegate(WeaponActor);
	}
	
	WeaponActor->AttachToComponent(WeaponSocket, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called every frame
void AFirstPersonPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstPersonPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &AFirstPersonPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFirstPersonPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Aim"), IE_Pressed, this, &AFirstPersonPlayer::StartAiming);
	PlayerInputComponent->BindAction(TEXT("Aim"), IE_Released, this, &AFirstPersonPlayer::EndAiming);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AFirstPersonPlayer::Shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AFirstPersonPlayer::Reload);
}

void AFirstPersonPlayer::StartAiming()
{
	if (WeaponDataAsset->Zoom == 1) return;

	if (!CrosshairWidget->IsInViewport() && WeaponActor != nullptr)
	{
		Camera->SetFieldOfView(Camera->FieldOfView *(1- WeaponDataAsset->Zoom));
		CrosshairWidget->AddToViewport();
	}
}

void AFirstPersonPlayer::EndAiming()
{
	if (WeaponDataAsset->Zoom == 1) return;

	if (CrosshairWidget->IsInViewport())
	{
		Camera->SetFieldOfView(Camera->FieldOfView /(1 - WeaponDataAsset->Zoom));
		CrosshairWidget->RemoveFromViewport();
	}
}

void AFirstPersonPlayer::Shoot()
{
	WeaponActor->Shoot(GetActorRotation().Pitch);
}

void AFirstPersonPlayer::Reload()
{
	WeaponActor->Reload();
}
