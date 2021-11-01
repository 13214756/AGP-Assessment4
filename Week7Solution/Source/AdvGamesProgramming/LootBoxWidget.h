// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "LootBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API ULootBoxWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ULootBoxWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	void ShowWidget();
	void HideWidget();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TXTLootBox;
};
