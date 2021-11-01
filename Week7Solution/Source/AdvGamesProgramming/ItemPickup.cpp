// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"

void AItemPickup::OnGenerate()
{
	APickup::OnGenerate();
	randItem = FMath::RandRange(1, 4);

	rand = FMath::RandRange(1, 100);
	if (rand <= 5)
	{
		Rarity = EItemPickupRarity::LEGENDARY;

		if (randItem == 1)
		{
			Type = EItemPickupType::HEALTH;

			Health = FMath::FRandRange(75.0f, 100.0f);
		}
		else if (randItem == 2)
		{
			Type = EItemPickupType::ATTACK;

			Attack = FMath::FRandRange(70.0f, 100.0f);
		}
		else if (randItem == 3)
		{
			Type = EItemPickupType::DEFENCE;

			Defence = FMath::RandRange(70.0f, 100.0f);
		}
		else
		{
			Type = EItemPickupType::SPEED;

			Speed = FMath::RandRange(70.0f, 100.0f);
		}
	}
	else if (rand > 5 && rand <= 20)
	{
		Rarity = EItemPickupRarity::MASTER;

		if (randItem == 1)
		{
			Type = EItemPickupType::HEALTH;

			Health = FMath::FRandRange(50.0f, 75.0f);
		}
		else if (randItem == 2)
		{
			Type = EItemPickupType::ATTACK;

			Attack = FMath::FRandRange(50.0f, 70.0f);
		}
		else if (randItem == 3)
		{
			Type = EItemPickupType::DEFENCE;

			Defence = FMath::RandRange(50.0f, 70.0f);
		}
		else
		{
			Type = EItemPickupType::SPEED;

			Speed = FMath::RandRange(50.0f, 70.0f);
		}
	}
	else if (rand > 20 && rand <= 50)
	{
		Rarity = EItemPickupRarity::RARE;


		if (randItem == 1)
		{
			Type = EItemPickupType::HEALTH;

			Health = FMath::FRandRange(20.0f, 50.0f);
		}
		else if (randItem == 2)
		{
			Type = EItemPickupType::ATTACK;

			Attack = FMath::FRandRange(25.0f, 50.0f);
		}
		else if (randItem == 3)
		{
			Type = EItemPickupType::DEFENCE;

			Defence = FMath::RandRange(25.0f, 50.0f);
		}
		else
		{
			Type = EItemPickupType::SPEED;

			Speed = FMath::RandRange(25.0f, 50.0f);
		}
	}
	else
	{
		Rarity = EItemPickupRarity::COMMON;

		if (randItem == 1)
		{
			Type = EItemPickupType::HEALTH;

			Health = FMath::FRandRange(1.0f, 20.0f);
		}
		else if (randItem == 2)
		{
			Type = EItemPickupType::ATTACK;

			Attack = FMath::FRandRange(5.0f, 25.0f);
		}
		else if (randItem == 3)
		{
			Type = EItemPickupType::DEFENCE;

			Defence = FMath::RandRange(5.0f, 25.0f);
		}
		else
		{
			Type = EItemPickupType::SPEED;

			Speed = FMath::RandRange(5.0f, 25.0f);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Rarity is %i"), Rarity);

}