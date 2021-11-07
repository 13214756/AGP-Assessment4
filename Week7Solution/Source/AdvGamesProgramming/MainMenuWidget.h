// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()


private:
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonHost;
	UPROPERTY(meta = (BindWidget))
		UButton* ButtonJoin;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonInstructions;
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;
	UPROPERTY(meta = (BindWidget))
		UButton* ButtonGame1;
	UPROPERTY(meta = (BindWidget))
		UButton* ButtonGame2;
	UPROPERTY(meta = (BindWidget))
		UButton* ButtonGame3;

	UFUNCTION()
		void OnHostButtonPressed();
	UFUNCTION()
		void OnJoinButtonPressed();
	UFUNCTION()
		void OnInstructionButtonPressed();
	UFUNCTION()
		void OnQuitButtonPressed();
	UFUNCTION()
		void OnGame1ButtonPressed();
	UFUNCTION()
		void OnGame2ButtonPressed();
	UFUNCTION()
		void OnGame3ButtonPressed();

	virtual bool Initialize() override;

	
};
