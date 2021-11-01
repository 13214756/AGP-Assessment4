// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupsSpawner.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "BoostSpawner.h"
#include "WeaponSpawner.h"
#include "GameHUD.h"

// Sets default values
APickupsSpawner::APickupsSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnerSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SpawnerSceneComponent;

	SpawnerBoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounding Box"));
	SpawnerBoundingBox->AttachTo(RootComponent);
	SpawnerBoundingBox->SetGenerateOverlapEvents(true);
	SpawnerBoundingBox->OnComponentBeginOverlap.AddDynamic(this, &APickupsSpawner::OnEnterSpawner);
	SpawnerBoundingBox->OnComponentEndOverlap.AddDynamic(this, &APickupsSpawner::OnExitSpawner);
	SpawnerBoundingBox->SetWorldScale3D(FVector(4.0f, 4.0f, 4.0f));

	LootBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Box"));
	LootBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LootBoxAsset(TEXT("StaticMesh'/Game/Assets/Meshes/CubeMesh.CubeMesh'"));
	if (LootBoxAsset.Object)
	{
		LootBox->SetStaticMesh(LootBoxAsset.Object);
	}

	LockedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Locked Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> LockedMaterialAsset(TEXT("Material'/Game/Materials/BlackMaterial.BlackMaterial'"));
	if (LockedMaterialAsset.Object)
	{
		LockedMaterial = LockedMaterialAsset.Object;
	}
	UnlockedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Unlocked Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> UnlockedMaterialAsset(TEXT("Material'/Game/Materials/WhiteMaterial.WhiteMaterial'"));
	if (UnlockedMaterialAsset.Object)
	{
		UnlockedMaterial = UnlockedMaterialAsset.Object;
	}

	SpawnTime = 0.1f;
	LockTimer = 30.0f;
	bBoxUnlocked = false;
}

// Called when the game starts or when spawned
void APickupsSpawner::BeginPlay()
{
	Super::BeginPlay();

	PickupInt = FMath::RandRange(1, 2);
	LootBox->SetMaterial(0, LockedMaterial);
	SpawnPickup();
	UE_LOG(LogTemp, Warning, TEXT("SpawnPickup() has run."));
}

// Called every frame
void APickupsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bBoxUnlocked)
	{
		LockTimer -= DeltaTime;
		if (LockTimer <= 0.0f)
		{
			bBoxUnlocked = true;
			LootBox->SetMaterial(0, UnlockedMaterial);
		}
	}
}

void APickupsSpawner::OnEnterSpawner(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bBoxUnlocked)
	{
		GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (GameHUD)
		{
			GameHUD->ShowWidget();
		}
	}
}

void APickupsSpawner::OnExitSpawner(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	GameHUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	if (GameHUD)
	{
		GameHUD->HideWidget();
	}
}

void APickupsSpawner::SpawnPickup()
{
	if (PickupInt == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning boost spawner"));
		/*
		FTimerHandle OutHandle;

		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APickupsSpawner::SpawnBoostSpawner, SpawnTime);*/
		SpawnBoostSpawner();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning weapon spawner"));
		/*FTimerHandle OutHandle;

		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APickupsSpawner::SpawnWeaponSpawner, SpawnTime);*/
		SpawnWeaponSpawner();
	}
}

void APickupsSpawner::SpawnBoostSpawner()
{
	if (BoostSpawnerBP)
	{
		FActorSpawnParameters BoostSpawnParams;

		ABoostSpawner* BoosterSpawnerRef = GetWorld()->SpawnActor<ABoostSpawner>(BoostSpawnerBP, GetTransform(), BoostSpawnParams);

		UE_LOG(LogTemp, Warning, TEXT("Boost spawner spawned"));
	}
}

void APickupsSpawner::SpawnWeaponSpawner()
{
	if (WeaponSpawnerBP)
	{
		FActorSpawnParameters WeaponSpawnParams;

		AWeaponSpawner* WeaponSpawnerRef = GetWorld()->SpawnActor<AWeaponSpawner>(WeaponSpawnerBP, GetTransform(), WeaponSpawnParams);

		UE_LOG(LogTemp, Warning, TEXT("Weapon spawner spawned"));
	}
}

void APickupsSpawner::HideSpawner()
{
	if (bBoxUnlocked)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}
}
