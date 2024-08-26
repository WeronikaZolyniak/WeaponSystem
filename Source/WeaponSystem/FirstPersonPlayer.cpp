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
}

// Called when the game starts or when spawned
void AFirstPersonPlayer::BeginPlay()
{
	Super::BeginPlay();
	CrosshairWidget = CreateWidget<UCrosshair>(GetWorld(), CrosshairClass);

	FActorSpawnParameters SpawnParameters;
	WeaponActor = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParameters);
	if (WeaponDataAsset != nullptr)
	{
		WeaponActor->SetWeaponDataAsset(WeaponDataAsset);
	}
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
}

void AFirstPersonPlayer::StartAiming()
{
	if (!CrosshairWidget->GetIsVisible())
	{
		Camera->SetFieldOfView(Camera->FieldOfView * 0.8);
		CrosshairWidget->AddToViewport();
	}
}

void AFirstPersonPlayer::EndAiming()
{
	if (CrosshairWidget->GetIsVisible())
	{
		Camera->SetFieldOfView(Camera->FieldOfView / 0.8);
		CrosshairWidget->RemoveFromViewport();
	}
}
