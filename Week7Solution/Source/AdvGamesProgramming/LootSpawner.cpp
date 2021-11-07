// Fill out your copyright notice in the Description page of Project Settings.


#include "LootSpawner.h"
#include "Components/BoxComponent.h"
#include "PickupsSpawner.h"
#include "Engine/World.h"

// Sets default values
ALootSpawner::ALootSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = LootSceneComponent;
	LootBoundingBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Bounding Box"));
	LootBoundingBox->AttachTo(RootComponent);
	LootBoundingBox->SetGenerateOverlapEvents(true);
	LootBoundingBox->OnComponentBeginOverlap.AddDynamic(this, &ALootSpawner::OnEnterLoot);
	LootBoundingBox->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

	SpawnLocation = GetActorLocation();
	SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	bBoxClosed = true;
	TimeTillAutoDestroy = 30.0f;

	AssociatedSpawner = nullptr;
}

// Called when the game starts or when spawned
void ALootSpawner::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

// Called every frame
void ALootSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bBoxClosed)
	{
		TimeTillAutoDestroy -= DeltaTime;
		if (TimeTillAutoDestroy <= 0.0f)
		{
			//SpawnNewPickup();
			DestroySelf();
		}
	}
}

void ALootSpawner::OnEnterLoot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnPickup(OtherActor);
}

void ALootSpawner::OnPickup(AActor* ActorThatPickedUp)
{

}

void ALootSpawner::OnGenerate()
{

}

void ALootSpawner::BoxOpen()
{
	bBoxClosed = false;
}

void ALootSpawner::SpawnNewPickup()
{
	//ServerSpawnNewPickup();
	//GetWorld()->SpawnActor<APickupsSpawner>(SpawnLocation, SpawnRotation, SpawnInfo);
	/*
	UE_LOG(LogTemp, Warning, TEXT("SpawnNewPickup() running"));
	AssociatedSpawner = Cast<APickupsSpawner>(GetAttachParentActor());
	if (AssociatedSpawner)
	{
		AssociatedSpawner->ResetSpawner();
		UE_LOG(LogTemp, Warning, TEXT("Found AssociatedSpawner"));
	}*/
}

void ALootSpawner::DestroySelf()
{
	ServerDestroySelf();
	Destroy();
}

void ALootSpawner::ServerSpawnNewPickup_Implementation()
{
	//GetWorld()->SpawnActor<APickupsSpawner>(SpawnLocation, SpawnRotation, SpawnInfo);
	UE_LOG(LogTemp, Warning, TEXT("SpawnNewPickup() running"));
	AssociatedSpawner = Cast<APickupsSpawner>(GetAttachParentActor());
	if (AssociatedSpawner)
	{
		AssociatedSpawner->ResetSpawner();
		UE_LOG(LogTemp, Warning, TEXT("Found AssociatedSpawner"));
	}
}

void ALootSpawner::ServerDestroySelf_Implementation()
{
	Destroy();
}
