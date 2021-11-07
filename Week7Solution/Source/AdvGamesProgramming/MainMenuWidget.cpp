// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "MainGameInstance.h"


void UMainMenuWidget::OnHostButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Button Pressed"));
		if (UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance()))
		{
			GameInstance->CreateSession(TEXT("Test Session"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to find the GameInstance"));
		}
}

void UMainMenuWidget::OnJoinButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Button Pressed"));
		if (UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance()))
		{
			GameInstance->FindSession(TEXT("Test Session"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Unable to find GameInstance"));
		}
}

void UMainMenuWidget::OnPlayButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Play Button Pressed"));

		//UGameplayStatics::LoadStreamLevel(this, LevelToLoad, true, true, FLatentActionInfo());
	UGameplayStatics::OpenLevel(this, LevelToLoad, true);
}

void UMainMenuWidget::OnInstructionButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Instruction Button Pressed"));

}

void UMainMenuWidget::OnQuitButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit Button Pressed"));

}

void UMainMenuWidget::OnGame1ButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Game1 Button Pressed"));

}

void UMainMenuWidget::OnGame2ButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Game2 Button Pressed"));

}

void UMainMenuWidget::OnGame3ButtonPressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Game3 Button Pressed"));

}

bool UMainMenuWidget::Initialize()
{
	Super::Initialize();
	if (ButtonHost && ButtonJoin && ButtonInstructions && ButtonQuit && ButtonGame1 && ButtonGame2 && ButtonGame3)
	{
		ButtonHost->OnClicked.AddDynamic(this, &UMainMenuWidget::OnHostButtonPressed);
		ButtonJoin->OnClicked.AddDynamic(this, &UMainMenuWidget::OnJoinButtonPressed);
		ButtonPlay->OnClicked.AddDynamic(this, &UMainMenuWidget::OnPlayButtonPressed);
		ButtonInstructions->OnClicked.AddDynamic(this, &UMainMenuWidget::OnInstructionButtonPressed);
		ButtonQuit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitButtonPressed);
		ButtonGame1->OnClicked.AddDynamic(this, &UMainMenuWidget::OnGame1ButtonPressed);
		ButtonGame2->OnClicked.AddDynamic(this, &UMainMenuWidget::OnGame2ButtonPressed);
		ButtonGame3->OnClicked.AddDynamic(this, &UMainMenuWidget::OnGame3ButtonPressed);
		return true;
	}
	return false;
}