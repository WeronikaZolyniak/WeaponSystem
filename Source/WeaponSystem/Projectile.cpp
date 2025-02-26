// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "DrawDebugHelpers.h"
#include "TargetInterface.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(5,5,5));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	//Collision->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorForwardVector(), FColor::Cyan, true);
	ProjectileStartPosition = GetActorLocation();
	AddActorLocalRotation(FQuat::MakeFromEuler(FVector(0,0,90)));
	Gravity = FVector(0, 0, GetWorld()->GetGravityZ());
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	UE_LOG(LogTemp, Warning, TEXT("Hit: %f %f %f"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z);
	FRotator DecalRotation = UKismetMathLibrary::MakeRotFromX(Hit.Normal);
	UE_LOG(LogTemp, Warning, TEXT("Rotation: %f %f %f"), DecalRotation.Pitch, DecalRotation.Yaw, DecalRotation.Roll);


	if (OtherActor->Implements<UTargetInterface>())
	{
		Cast<ITargetInterface>(OtherActor)->TargetGotHit();
	}
	else
	{
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHoleMaterial, FVector(100, 4, 4), Hit.Location, DecalRotation);
	}

	if (BulletHitParticle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletHitParticle, Hit.Location);
	}
	Destroy();
}

void AProjectile::OnLineTraceHit(const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("LineTrace Hit"));
	UE_LOG(LogTemp, Warning, TEXT("LineTrace Hit: %f %f %f"), Hit.Location.X, Hit.Location.Y, Hit.Location.Z);
	FRotator DecalRotation = UKismetMathLibrary::MakeRotFromX(Hit.Normal);
	UE_LOG(LogTemp, Warning, TEXT("LineTrace Rotation: %f %f %f"), DecalRotation.Pitch, DecalRotation.Yaw, DecalRotation.Roll);

	AActor* OtherActor = Hit.GetActor();

	if (OtherActor->Implements<UTargetInterface>())
	{
		Cast<ITargetInterface>(OtherActor)->TargetGotHit();
	}
	else
	{
		UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHoleMaterial, FVector(100, 4, 4), Hit.Location, DecalRotation);
	}

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
		FVector Direction = GetActorForwardVector() * SpeedInMetresPerSecond;
		bool ProjectileCollided = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() + Direction, ECollisionChannel::ECC_Visibility);
		if (ProjectileCollided)
		{

			DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorLocation() + Direction, FColor::Green, true);
			OnLineTraceHit(Hit);
		}
		else
		{
			AddActorLocalTransform(FTransform(FRotator(0, 0, 0), Velocity, FVector(0, 0, 0)), true);
		}
	}

	DrawDebugLine(GetWorld(), ProjectileStartPosition, GetActorLocation(), FColor::Red, true);
}

void AProjectile::SetSpeedInMetresPerSecond(int SpeedInMetresPerSecondToSet)
{
	SpeedInMetresPerSecond = SpeedInMetresPerSecondToSet;
	Velocity = FVector(SpeedInMetresPerSecond, 0,0);
}

