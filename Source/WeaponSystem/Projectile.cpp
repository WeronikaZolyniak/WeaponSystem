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
	Collision->SetBoxExtent(FVector(1,1,1));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBoxBeginOverlap);
	ProjectileStartPosition = GetActorLocation();
	Gravity = FVector(0, 0, GetWorld()->GetGravityZ());
}

void AProjectile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector HitLocation = GetActorLocation();
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHoleMaterial, FVector(30, 4, 4), HitLocation);

	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProjectileStartPosition = GetActorLocation();

	if (SpeedInMetresPerSecond != 0)
	{
		Velocity += Gravity * DeltaTime * 0.001;
		AddActorLocalTransform(FTransform(FRotator(0, 0, 0), Velocity, FVector(0, 0, 0)));
	}

	DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorLocation(), FColor::Red, true);
}

void AProjectile::SetSpeedInMetresPerSecond(int SpeedInMetresPerSecondToSet)
{
	SpeedInMetresPerSecond = SpeedInMetresPerSecondToSet;
	Velocity = FVector(0, SpeedInMetresPerSecond,0);
}

