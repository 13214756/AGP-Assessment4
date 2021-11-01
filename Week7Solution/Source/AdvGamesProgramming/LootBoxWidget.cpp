// Fill out your copyright notice in the Description page of Project Settings.


#include "LootBoxWidget.h"

ULootBoxWidget::ULootBoxWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	
}

void ULootBoxWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULootBoxWidget::ShowWidget()
{
	if(TXTLootBox)
	{
		if (TXTLootBox->Visibility == ESlateVisibility::Hidden)
		{
			TXTLootBox->SetVisibility(ESlateVisibility::Visible);
		}
		TXTLootBox->SetText(FText::FromString("Press 'E' to unlock"));
	}
}

void ULootBoxWidget::HideWidget()
{
	if (TXTLootBox)
	{
		TXTLootBox->SetVisibility(ESlateVisibility::Hidden);
	}
}
