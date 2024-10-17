// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsWidget.h"

void UPointsWidget::SetPointsText(int points)
{
	FString Text = FString::FromInt(points);
	PointsText->SetText(FText::FromString(Text));
}
