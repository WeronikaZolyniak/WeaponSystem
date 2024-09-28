// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DrawDebugHelpers.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	RootComponent = Collision;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileStartPosition = GetActorLocation();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalTransform(FTransform(FRotator(0, 0, 0), FVector(0, SpeedInMetresPerSecond * DeltaTime, -1 * (GetWorld()->GetGravityZ() / 2) * DeltaTime * DeltaTime), FVector(0, 0, 0)));
	DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorLocation(), FColor::Red);
}

