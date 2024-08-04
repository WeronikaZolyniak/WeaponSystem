// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.h"
#include "GameFramework/SpringArmComponent.h"
#include "FirstPersonPlayer.generated.h"

UCLASS()
class WEAPONSYSTEM_API AFirstPersonPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartAiming();
	void EndAiming();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCrosshair> CrosshairClass;

	UCrosshair* CrosshairWidget;
};
