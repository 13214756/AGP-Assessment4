// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

AGameHUD::AGameHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> GameHUDObject(TEXT("/Game/Widgets/PlayerHUDWidget"));

	GameHUDClass = GameHUDObject.Class;


	if (GameHUDClass)
	{
		CurrentGameHUDWidget = CreateWidget<UUserWidget>(GetWorld(), GameHUDClass);
		if (CurrentGameHUDWidget)
		{
			CurrentGameHUDWidget->AddToViewport();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unable to find CurrentGameHUDWidget"))
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find the GameHUDClass"))
	}

	if (CurrentGameHUDWidget)
	{
		HealthProgressBar = Cast<UProgressBar>(CurrentGameHUDWidget->GetWidgetFromName(TEXT("ProgHealthBar")));
		GameOverScreen = Cast<UOverlay>(CurrentGameHUDWidget->GetWidgetFromName(TEXT("GameOverScreen")));
		GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	}
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
	/*
	if (GameOverWidgetClass)
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidget)
		{
			GameOverWidget->AddToViewport();
		}
	}
	*/
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

void AGameHUD::ShowGameOverScreen()
{
	GameOverScreen = Cast<UOverlay>(CurrentGameHUDWidget->GetWidgetFromName(TEXT("GameOverScreen")));
	
	UE_LOG(LogTemp, Warning, TEXT("GameOverScreen Cast Pending"));

	if (GameOverScreen)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameOverScreen Cast Successful"));

		GameOverScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameHUD::SetPlayerHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to find the progress bar to update the health"))
	}
}

void AGameHUD::HideHUD()
{
	if (CurrentGameHUDWidget)
	{
		CurrentGameHUDWidget->RemoveFromViewport();
	}
}

void AGameHUD::ShowHUD()
{
	if (CurrentGameHUDWidget)
	{
		CurrentGameHUDWidget->AddToViewport();
	}
}

void AGameHUD::ShowGameOverHUD()
{
	if (CurrentGameHUDWidget)
	{
		CurrentGameHUDWidget->AddToViewport();
	}
}
