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
}

