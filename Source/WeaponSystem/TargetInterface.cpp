// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "FirstPersonPlayer.h"

// Add default functionality here for any ITargetInterface functions that are not pure virtual.

void ITargetInterface::TargetGotHit(int PointsToAdd, UObject* WorldRef)
{
	AFirstPersonPlayer* Player = Cast<AFirstPersonPlayer>(UGameplayStatics::GetPlayerCharacter(WorldRef, 0));

	if (Player)
	{
		Player->Points += PointsToAdd;
		Player->PointsWidget->SetPointsText(Player->Points);
	}
}
