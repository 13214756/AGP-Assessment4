// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "LootBoxWidget.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void ShowWidget();
	UFUNCTION()
	void HideWidget();

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> LootBoxWidgetClass;

	void SetPlayerHealthBarPercent(float Percent);
	void HideHUD();
	void ShowHUD();

	void ShowGameOverHUD();

private:
	ULootBoxWidget* LootBoxWidget;

	TSubclassOf<UUserWidget> GameHUDClass;
	UUserWidget* CurrentGameHUDWidget;
	class UProgressBar* HealthProgressBar;
};
