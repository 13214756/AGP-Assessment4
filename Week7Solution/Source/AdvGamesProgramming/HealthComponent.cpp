// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Engine.h"
#include "GameHUD.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100.0f;
	DmgPercentTaken = 1.0f;
	DefBoostTime = 0.0f;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		if (GetOwner()->GetLocalRole() == ROLE_Authority && OwnerPawn->IsLocallyControlled())
		{
			UpdateHealthBar();
		}
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (DefBoostTime > 0.0f)
	{
		DefBoostTime -= DeltaTime;
		if (DefBoostTime == 0.0f)
		{
			ResetDefence();
		}
	}

}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}

void UHealthComponent::OnTakeDamage(float Damage)
{
	CurrentHealth -= (DmgPercentTaken * Damage);
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0;
		UE_LOG(LogTemp, Warning, TEXT("Player is Dead"));

		OnDeath();
	}
	if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		if (GetOwner()->GetLocalRole() == ROLE_Authority && OwnerPawn->IsLocallyControlled())
		{
			UpdateHealthBar();
		}
	}
}

void UHealthComponent::OnDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("on death is called"));

	
	/*
	if (GetOwner()->GetLocalRole() == ROLE_AutonomousProxy || (GetOwner()->GetLocalRole() == ROLE_Authority && Cast<APawn>(GetOwner())->IsLocallyControlled()))

	{
		AGameHUD* GameHUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (GameHUD)
		{
			UE_LOG(LogTemp, Warning, TEXT("About to display game over"));

			GameHUD->ShowGameOverScreen();
		}

	}
		//Cast<APlayerCharacterBlueprint>(GetController())->DisableInput();
	
	*/
}

float UHealthComponent::HealthPercentageRemaining()
{
	return CurrentHealth / MaxHealth * 100.0f;
}

void UHealthComponent::Heal(float Health)
{
	CurrentHealth += Health;

	UE_LOG(LogTemp, Warning, TEXT("You have healed %f health"), Health);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("You have healed %f health"), Health));
}

void UHealthComponent::IncreaseDefence(float DefPoints)
{
	DmgPercentTaken -= (0.01f * DefPoints);
	DefBoostTime += 30.0f;

	UE_LOG(LogTemp, Warning, TEXT("Now taking %f percent of damage"), DmgPercentTaken);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("You have gained %f defence"), DefPoints));
}

void UHealthComponent::ResetDefence()
{
	DmgPercentTaken = 1.0f;

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Defence buff has worn off")));
}

void UHealthComponent::UpdateHealthBar()
{
	if (GetOwner()->GetLocalRole() == ROLE_AutonomousProxy || (GetOwner()->GetLocalRole() == ROLE_Authority && Cast<APawn>(GetOwner())->IsLocallyControlled()))
	{
		AGameHUD* GameHUD = Cast<AGameHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (IsValid(GameHUD))
		{
			GameHUD->SetPlayerHealthBarPercent(CurrentHealth / MaxHealth);
		}
	}
}