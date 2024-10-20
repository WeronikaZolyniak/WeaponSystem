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
	Collision->SetBoxExtent(FVector(5,5,5));
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->SetGenerateOverlapEvents(false);
	Collision->SetSimulatePhysics(true);
	Collision->SetEnableGravity(false);
	Collision->SetAngularDamping(0);
	Collision->SetLinearDamping(0);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorForwardVector(), FColor::Cyan, true);
	ProjectileStartPosition = GetActorLocation();
	Gravity = FVector(0, 0, GetWorld()->GetGravityZ());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	UE_LOG(LogTemp, Warning, TEXT("Hit: %f %f %f"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z);
	UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHoleMaterial, FVector(10, 4, 4), Hit.Location);
	if (BulletHitParticle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletHitParticle, Hit.Location);
	}
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProjectileStartPosition = GetActorLocation();
	FHitResult Hit;

	if (SpeedInMetresPerSecond != 0)
	{
		Velocity += Gravity * DeltaTime * 0.001;
		AddActorLocalTransform(FTransform(FRotator(0, 0, 0), Velocity, FVector(0, 0, 0)), true, &Hit);
	}
	/*if (Hit.bBlockingHit)
	{
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHoleMaterial, FVector(10, 4, 4), Hit.Location);
		Destroy();
	}*/

	DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorLocation(), FColor::Red, true);
}

void AProjectile::SetSpeedInMetresPerSecond(int SpeedInMetresPerSecondToSet)
{
	SpeedInMetresPerSecond = SpeedInMetresPerSecondToSet;
	Velocity = FVector(0, SpeedInMetresPerSecond,0);
}

