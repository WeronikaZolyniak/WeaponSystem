// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.generated.h"

UCLASS()
class WEAPONSYSTEM_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpeedInMetresPerSecond(int SpeedInMetresPerSecondToSet);

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* Collision;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BulletHoleMaterial;

	int SpeedInMetresPerSecond = 0;

	FVector ProjectileStartPosition;

	FVector Velocity;
	FVector Gravity;

};
