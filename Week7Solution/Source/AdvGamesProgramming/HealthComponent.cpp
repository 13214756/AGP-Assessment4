// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine.h"
#include "HealthComponent.h"

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

void UHealthComponent::OnTakeDamage(float Damage)
{
	CurrentHealth -= (DmgPercentTaken * Damage);
	if (CurrentHealth < 0.0f)
	{
		CurrentHealth = 0;
		OnDeath();
	}
}

void UHealthComponent::OnDeath()
{

}

float UHealthComponent::HealthPercentageRemaining()
{
	return CurrentHealth/MaxHealth * 100.0f;
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
