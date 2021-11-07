// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSpawner.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"



void AWeaponSpawner::OnGenerate()
{
	ALootSpawner::OnGenerate();

	/*WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->AttachTo(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMeshAsset(TEXT("SkeletalMesh'/Game/Assets/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	if (WeaponMeshAsset.Object)
	{
		WeaponMesh->SetSkeletalMesh(WeaponMeshAsset.Object);
	}*/
	/*
	LegendaryMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Legendary Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> LegendaryMaterialAsset(TEXT("Material'/Game/Materials/PickupMaterials/LegendaryMaterial.LegendaryMaterial'"));
	if (LegendaryMaterialAsset.Object)
	{
		LegendaryMaterial = LegendaryMaterialAsset.Object;
	}
	MasterMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Master Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MasterMaterialAsset(TEXT("Material'/Game/Materials/PickupMaterials/MasterMaterial.MasterMaterial'"));
	if (MasterMaterialAsset.Object)
	{
		MasterMaterial = MasterMaterialAsset.Object;
	}
	RareMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Rare Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> RareMaterialAsset(TEXT("Material'/Game/Materials/PickupMaterials/RareMaterial.RareMaterial'"));
	if (RareMaterialAsset.Object)
	{
		RareMaterial = RareMaterialAsset.Object;
	}
	CommonMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Common Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> CommonMaterialAsset(TEXT("Material'/Game/Materials/PickupMaterials/CommonMaterial.CommonMaterial'"));
	if (CommonMaterialAsset.Object)
	{
		CommonMaterial = CommonMaterialAsset.Object;
	}*/

	float RarityValue = FMath::RandRange(0.0f, 1.0f);
	TArray<bool> RandBoolArray;

	if (RarityValue <= 0.05f)
	{
		Rarity = EWeaponSpawnerRarity::LEGENDARY;
		GenerateRandomBoolArray(4, 4, RandBoolArray);

		//WeaponMesh->SetMaterial(0, LegendaryMaterial);
	}
	else if (RarityValue <= 0.20f)
	{
		Rarity = EWeaponSpawnerRarity::MASTER;
		GenerateRandomBoolArray(4, 3, RandBoolArray);

		//WeaponMesh->SetMaterial(0, MasterMaterial);
	}
	else if (RarityValue <= 0.50f)
	{
		Rarity = EWeaponSpawnerRarity::RARE;
		GenerateRandomBoolArray(4, 1, RandBoolArray);

		//WeaponMesh->SetMaterial(0, RareMaterial);
	}
	else
	{
		Rarity = EWeaponSpawnerRarity::COMMON;
		GenerateRandomBoolArray(4, 0, RandBoolArray);

		//WeaponMesh->SetMaterial(0, CommonMaterial);
	}

	//Assign the good or bad weapon characteristics based on the result of the random boolean array.
	BulletDamage = (RandBoolArray[0] ? FMath::RandRange(15.0f, 30.0f) : FMath::RandRange(2.0f, 15.0f));
	MuzzleVelocity = (RandBoolArray[1] ? FMath::RandRange(10000.0f, 20000.0f) : FMath::RandRange(5000.0f, 10000.0f));
	MagazineSize = (RandBoolArray[2] ? FMath::RandRange(20, 100) : FMath::RandRange(1, 20));
	WeaponAccuracy = (RandBoolArray[3] ? FMath::RandRange(0.95f, 1.0f) : FMath::RandRange(0.8f, 0.95f));
}

void AWeaponSpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWeaponSpawner, Rarity);
	DOREPLIFETIME(AWeaponSpawner, BulletDamage);
	DOREPLIFETIME(AWeaponSpawner, MuzzleVelocity);
	DOREPLIFETIME(AWeaponSpawner, MagazineSize);
	DOREPLIFETIME(AWeaponSpawner, WeaponAccuracy);
}


void AWeaponSpawner::GenerateRandomBoolArray(int32 ArrayLength, int32 NumTrue, TArray<bool>& RandBoolArray)
{
	for (int32 i = 0; i < ArrayLength; i++)
	{
		//Ternary Condition
		RandBoolArray.Add(i < NumTrue ? true : false);
	}

	//Card Shuffling Algorithm
	for (int32 i = 0; i < RandBoolArray.Num(); i++)
	{
		int32 RandIndex = FMath::RandRange(0, RandBoolArray.Num() - 1);
		bool Temp = RandBoolArray[i];
		RandBoolArray[i] = RandBoolArray[RandIndex];
		RandBoolArray[RandIndex] = Temp;
	}
}
