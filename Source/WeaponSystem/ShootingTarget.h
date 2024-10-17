// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetInterface.h"
#include "Components/BoxComponent.h"
#include "ShootingTarget.generated.h"

UCLASS()
class WEAPONSYSTEM_API AShootingTarget : public AActor, public ITargetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootingTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void TargetGotHit(int PointsToAdd, UObject* WorldRef) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
	int Points = 1;

};
