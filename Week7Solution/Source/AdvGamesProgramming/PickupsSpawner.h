// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoostSpawner.h"
#include "WeaponSpawner.h"
#include "PickupsSpawner.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API APickupsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupsSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	USceneComponent* SpawnerSceneComponent;
	UPROPERTY(EditAnywhere)
	class UBoxComponent* SpawnerBoundingBox;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LootBox;
	class UMaterial* LockedMaterial;
	class UMaterial* UnlockedMaterial;
	float LockTimer;
	bool bBoxUnlocked;
	int32 PickupInt;
	class AGameHUD* GameHUD;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnInfo;

	UPROPERTY(EditDefaultsOnly, Category = "BoostSpawning")
	TSubclassOf<ABoostSpawner> BoostSpawnerBP;
	UPROPERTY(EditDefaultsOnly, Category = "WeaponSpawning")
	TSubclassOf<AWeaponSpawner> WeaponSpawnerBP;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnTime;

	UFUNCTION()
	void SpawnBoostSpawner();
	UFUNCTION()
	void SpawnWeaponSpawner();

	UFUNCTION()
	virtual void OnEnterSpawner(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnExitSpawner(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
	void SpawnPickup();
	void HideSpawner();

	class ABoostSpawner* BoosterSpawner;
	class AWeaponSpawner* WeaponSpawner;

	void ResetSpawner();

};
