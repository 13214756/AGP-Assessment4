// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkeletalMeshComponent.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"
#include "BoostSpawner.h"





void ABoostSpawner::OnGenerate()
{
	ALootSpawner::OnGenerate();
	/*
	BoostMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boost Mesh"));
	BoostMesh->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BoostMeshAsset(TEXT("SkeletalMesh'/Game/Assets/Meshes/SphereMesh.SphereMesh_SphereMesh'"));
	if (BoostMeshAsset.Object)
	{
		BoostMesh->SetSkeletalMesh(BoostMeshAsset.Object);
	}*/
	/*
	HealthMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Health Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> HealthMaterialAsset(TEXT("Material'/Game/Materials/GreenMaterial.GreenMaterial'"));
	if (HealthMaterialAsset.Object)
	{
		HealthMaterial = HealthMaterialAsset.Object;
	}
	AttackMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Attack Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> AttackMaterialAsset(TEXT("Material'/Game/Materials/RedMaterial.RedMaterial'"));
	if (AttackMaterialAsset.Object)
	{
		AttackMaterial = AttackMaterialAsset.Object;
	}
	DefenceMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Defence Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> DefenceMaterialAsset(TEXT("Material'/Game/Materials/BlueMaterial.BlueMaterial'"));
	if (DefenceMaterialAsset.Object)
	{
		DefenceMaterial = DefenceMaterialAsset.Object;
	}
	SpeedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Speed Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SpeedMaterialAsset(TEXT("Material'/Game/Materials/BrownMaterial.BrownMaterial'"));
	if (SpeedMaterialAsset.Object)
	{
		SpeedMaterial = SpeedMaterialAsset.Object;
	}*/

	RandItem = FMath::RandRange(1, 4);	

	Rand = FMath::RandRange(1, 100);
	if (Rand <= 5)
	{
		Rarity = EBoostPickupRarity::LEGENDARY;

		if (RandItem == 1)
		{
			Type = EBoostPickupType::HEALTH;

			Health = FMath::FRandRange(75.0f, 100.0f);

			//BoostMesh->SetMaterial(0, HealthMaterial);
		}
		else if (RandItem == 2)
		{
			Type = EBoostPickupType::ATTACK;

			Attack = FMath::FRandRange(70.0f, 100.0f);

			//BoostMesh->SetMaterial(0, AttackMaterial);
		}
		else if (RandItem == 3)
		{
			Type = EBoostPickupType::DEFENCE;

			Attack = FMath::FRandRange(70.0f, 100.0f);

			//BoostMesh->SetMaterial(0, DefenceMaterial);
		}
		else
		{
			Type = EBoostPickupType::SPEED;

			Speed = FMath::RandRange(70.0f, 100.0f);

			//BoostMesh->SetMaterial(0, SpeedMaterial);
		}
	}
	else if (Rand > 5 && Rand <= 20)
	{
		Rarity = EBoostPickupRarity::MASTER;

		if (RandItem == 1)
		{
			Type = EBoostPickupType::HEALTH;

			Health = FMath::FRandRange(50.0f, 75.0f);

			//BoostMesh->SetMaterial(0, HealthMaterial);
		}
		else if (RandItem == 2)
		{
			Type = EBoostPickupType::ATTACK;

			Attack = FMath::FRandRange(50.0f, 70.0f);

			//BoostMesh->SetMaterial(0, AttackMaterial);
		}
		else if (RandItem == 3)
		{
			Type = EBoostPickupType::DEFENCE;

			Defence = FMath::RandRange(50.0f, 70.0f);

			//BoostMesh->SetMaterial(0, DefenceMaterial);
		}
		else
		{
			Type = EBoostPickupType::SPEED;

			Speed = FMath::RandRange(50.0f, 70.0f);

			//BoostMesh->SetMaterial(0, SpeedMaterial);
		}
	}
	else if (Rand > 20 && Rand <= 50)
	{
		Rarity = EBoostPickupRarity::RARE;

		if (RandItem == 1)
		{
			Type = EBoostPickupType::HEALTH;

			Health = FMath::FRandRange(20.0f, 50.0f);

			//BoostMesh->SetMaterial(0, HealthMaterial);
		}
		else if (RandItem == 2)
		{
			Type = EBoostPickupType::ATTACK;

			Attack = FMath::FRandRange(25.0f, 50.0f);

			//BoostMesh->SetMaterial(0, AttackMaterial);
		}
		else if (RandItem == 3)
		{
			Type = EBoostPickupType::DEFENCE;

			Defence = FMath::RandRange(25.0f, 50.0f);

			//BoostMesh->SetMaterial(0, DefenceMaterial);
		}
		else
		{
			Type = EBoostPickupType::SPEED;

			Speed = FMath::RandRange(25.0f, 50.0f);

			//BoostMesh->SetMaterial(0, SpeedMaterial);
		}
	}
	else
	{
		Rarity = EBoostPickupRarity::COMMON;

		if (RandItem == 1)
		{
			Type = EBoostPickupType::HEALTH;

			Health = FMath::FRandRange(1.0f, 20.0f);

			//BoostMesh->SetMaterial(0, HealthMaterial);
		}
		else if (RandItem == 2)
		{
			Type = EBoostPickupType::ATTACK;

			Attack = FMath::FRandRange(50.0f, 25.0f);

			//BoostMesh->SetMaterial(0, AttackMaterial);
		}
		else if (RandItem == 3)
		{
			Type = EBoostPickupType::DEFENCE;

			Defence = FMath::RandRange(50.0f, 25.0f);

			//BoostMesh->SetMaterial(0, DefenceMaterial);
		}
		else
		{
			Type = EBoostPickupType::SPEED;

			Speed = FMath::RandRange(5.0f, 25.0f);

			//BoostMesh->SetMaterial(0, SpeedMaterial);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("OnGenerate has run"));
}

/*
void ABoostSpawner::OnPickup(AActor* ActorThatPickedUp)
{
	if (RandItem == 1)
	{
		if (ActorThatPickedUp)
		{
			PickedUpHealthComponent = Cast<UHealthComponent>(ActorThatPickedUp);
			PickedUpHealthComponent->Heal(Health);
			DestroySelf();
		}
	}
	else if (RandItem == 2)
	{
		if (ActorThatPickedUp)
		{
			PickUpActor = ActorThatPickedUp;
			ApplyAttackBoost(Attack);
			DestroySelf();
		}
	}
	else if (RandItem == 3)
	{
		if (ActorThatPickedUp)
		{
			PickedUpHealthComponent = Cast<UHealthComponent>(ActorThatPickedUp);
			PickedUpHealthComponent->IncreaseDefence(Defence);
			DestroySelf();
		}
	}
	else
	{
		if (ActorThatPickedUp)
		{
			PickedUpPlayerCharacter = Cast<APlayerCharacter>(ActorThatPickedUp);
			PickedUpPlayerCharacter->ApplySpeedBoost(Speed);
			DestroySelf();
		}
	}
}*/
