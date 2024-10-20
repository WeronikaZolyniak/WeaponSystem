// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingTarget.h"

// Sets default values
AShootingTarget::AShootingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collision->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Collision->SetNotifyRigidBodyCollision(true);
	Collision->SetGenerateOverlapEvents(false);
	Collision->SetSimulatePhysics(true);
	Collision->SetEnableGravity(false);
	Collision->SetAngularDamping(0);
	Collision->SetLinearDamping(0);
	Collision->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void AShootingTarget::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentHit.AddDynamic(this, &AShootingTarget::OnHit);
}

// Called every frame
void AShootingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootingTarget::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TargetGotHit(Points, GetWorld());
}

void AShootingTarget::TargetGotHit(int PointsToAdd, UObject* WorldRef)
{
	ITargetInterface::TargetGotHit(PointsToAdd, WorldRef);
}

