// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupsSpawner.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "BoostSpawner.h"
#include "WeaponSpawner.h"
#include "GameHUD.h"
#include "Net/UnrealNetwork.h"


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
	//SpawnerBoundingBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	LootBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Box"));
	LootBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LootBoxAsset(TEXT("StaticMesh'/Game/Assets/Meshes/CubeMesh.CubeMesh'"));
	if (LootBoxAsset.Object)
	{
		LootBox->SetStaticMesh(LootBoxAsset.Object);
	}

	LockedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Locked Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> LockedMaterialAsset(TEXT("Material'/Game/Materials/LootBoxMaterialLocked.LootBoxMaterialLocked'"));
	if (LockedMaterialAsset.Object)
	{
		LockedMaterial = LockedMaterialAsset.Object;
	}
	UnlockedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Unlocked Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial> UnlockedMaterialAsset(TEXT("Material'/Game/Materials/LootBoxMaterialOpen.LootBoxMaterialOpen'"));
	if (UnlockedMaterialAsset.Object)
	{
		UnlockedMaterial = UnlockedMaterialAsset.Object;
	}

	SpawnTime = 0.1f;
	LockTimer = 30.0f;
	bBoxUnlocked = false;

	BoosterSpawner = nullptr;
	WeaponSpawner = nullptr;

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
			SpawnerBoundingBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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
	//ServerSpawnPickup();

	if (PickupInt == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning boost spawner"));
		/*
		FTimerHandle OutHandle;

		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APickupsSpawner::SpawnBoostSpawner, SpawnTime);*/
		SpawnBoostSpawner();

		UE_LOG(LogTemp, Warning, TEXT("SpawnPickup()"));
	}
	else if (PickupInt == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning weapon spawner"));
		/*FTimerHandle OutHandle;

		GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APickupsSpawner::SpawnWeaponSpawner, SpawnTime);*/
		SpawnWeaponSpawner();

		UE_LOG(LogTemp, Warning, TEXT("SpawnPickup()"));
	}
}

void APickupsSpawner::SpawnBoostSpawner()
{
	ServerSpawnBoostSpawner();
	/*
	if (BoostSpawnerBP)
	{
		FActorSpawnParameters BoostSpawnParams;

		ABoostSpawner* BoosterSpawnerRef = GetWorld()->SpawnActor<ABoostSpawner>(BoostSpawnerBP, GetTransform(), FActorSpawnParameters());
		BoosterSpawnerRef->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		BoosterSpawner = BoosterSpawnerRef;

		UE_LOG(LogTemp, Warning, TEXT("Boost spawner spawned"));
	}*/
}



void APickupsSpawner::SpawnWeaponSpawner()
{
	ServerSpawnWeaponSpawner();
	/*
	if (WeaponSpawnerBP)
	{
		FActorSpawnParameters WeaponSpawnParams;

		AWeaponSpawner* WeaponSpawnerRef = GetWorld()->SpawnActor<AWeaponSpawner>(WeaponSpawnerBP, GetTransform(), FActorSpawnParameters());
		WeaponSpawnerRef->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		WeaponSpawner = WeaponSpawnerRef;

		UE_LOG(LogTemp, Warning, TEXT("Weapon spawner spawned"));
	}*/
}

void APickupsSpawner::OpenBox()
{
	if (bBoxUnlocked)
	{
		if (PickupInt == 1)
		{
			if (BoosterSpawner)
			{
				BoosterSpawner->BoxOpen();
			}
		}
		else if (PickupInt == 2)
		{
			if (WeaponSpawner)
			{
				WeaponSpawner->BoxOpen();
			}
		}
	}
}

void APickupsSpawner::HideSpawner()
{
	ServerHideSpawner();

	if (bBoxUnlocked)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}
}

void APickupsSpawner::ResetSpawner()
{
	ServerResetSpawner();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	PickupInt = FMath::RandRange(1, 2);
	LootBox->SetMaterial(0, LockedMaterial);
	LockTimer = 30.0f;
	bBoxUnlocked = false;
	BoosterSpawner = nullptr;
	WeaponSpawner = nullptr;

	//SpawnPickup();

	UE_LOG(LogTemp, Warning, TEXT("ResetSpawner() has run"));
}
/*
void APickupsSpawner::ServerSpawnPickup_Implementation()
{
	if (PickupInt == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning boost spawner"));

		//FTimerHandle OutHandle;

		//GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APickupsSpawner::SpawnBoostSpawner, SpawnTime);
		SpawnBoostSpawner();

		UE_LOG(LogTemp, Warning, TEXT("SpawnPickup()"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawning weapon spawner"));
		//FTimerHandle OutHandle;

		//GetWorld()->GetTimerManager().SetTimer(OutHandle, this, &APickupsSpawner::SpawnWeaponSpawner, SpawnTime);
		SpawnWeaponSpawner();

		UE_LOG(LogTemp, Warning, TEXT("SpawnPickup()"));
	}
}*/

void APickupsSpawner::ServerHideSpawner_Implementation()
{
	if (bBoxUnlocked)
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}
}

void APickupsSpawner::ServerResetSpawner_Implementation()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	PickupInt = FMath::RandRange(1, 2);
	LootBox->SetMaterial(0, LockedMaterial);
	LockTimer = 30.0f;
	bBoxUnlocked = false;
	//BoosterSpawner = nullptr;
	//WeaponSpawner = nullptr;

	//SpawnPickup();

	UE_LOG(LogTemp, Warning, TEXT("ResetSpawner() has run"));
}

void APickupsSpawner::ServerSpawnBoostSpawner_Implementation()
{
	if (BoostSpawnerBP)
	{
		FActorSpawnParameters BoostSpawnParams;

		ABoostSpawner* BoosterSpawnerRef = GetWorld()->SpawnActor<ABoostSpawner>(BoostSpawnerBP, GetTransform(), FActorSpawnParameters());
		BoosterSpawnerRef->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		BoosterSpawner = BoosterSpawnerRef;

		UE_LOG(LogTemp, Warning, TEXT("Boost spawner spawned"));
	}
}

void APickupsSpawner::ServerSpawnWeaponSpawner_Implementation()
{
	if (WeaponSpawnerBP)
	{
		FActorSpawnParameters WeaponSpawnParams;

		AWeaponSpawner* WeaponSpawnerRef = GetWorld()->SpawnActor<AWeaponSpawner>(WeaponSpawnerBP, GetTransform(), FActorSpawnParameters());
		WeaponSpawnerRef->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		WeaponSpawner = WeaponSpawnerRef;

		UE_LOG(LogTemp, Warning, TEXT("Weapon spawner spawned"));
	}
}

void APickupsSpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APickupsSpawner, LockTimer);
	//DOREPLIFETIME(APickupsSpawner, bBoxUnlocked);
	DOREPLIFETIME(APickupsSpawner, PickupInt);
}
