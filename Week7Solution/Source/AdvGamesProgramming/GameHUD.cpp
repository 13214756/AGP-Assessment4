// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

AGameHUD::AGameHUD()
{

}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (LootBoxWidgetClass)
	{
		LootBoxWidget = CreateWidget<ULootBoxWidget>(GetWorld(), LootBoxWidgetClass);
		if (LootBoxWidget)
		{
			LootBoxWidget->AddToViewport();
		}
	}
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::ShowWidget()
{
	if (LootBoxWidget)
	{
		LootBoxWidget->ShowWidget();
	}
}

void AGameHUD::HideWidget()
{
	if (LootBoxWidget)
	{
		LootBoxWidget->HideWidget();
	}
}
