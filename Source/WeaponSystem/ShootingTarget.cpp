// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingTarget.h"
#include "FirstPersonPlayer.h"

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
}

// Called every frame
void AShootingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShootingTarget::TargetGotHit()
{
	AFirstPersonPlayer* Player = Cast<AFirstPersonPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Player)
	{
		Player->Points += Points;
		Player->PointsWidget->SetPointsText(Player->Points);
	}
}

