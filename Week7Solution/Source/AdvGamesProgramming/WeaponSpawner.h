// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootSpawner.h"
//#include "PickupsSpawner.h"
#include "WeaponSpawner.generated.h"

UENUM(BlueprintType)
enum class EWeaponSpawnerRarity : uint8
{
	LEGENDARY,
	MASTER,
	RARE,
	COMMON
};

/**
 * 
 */
UCLASS()
class ADVGAMESPROGRAMMING_API AWeaponSpawner : public ALootSpawner
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	EWeaponSpawnerRarity Rarity;

	//UPROPERTY(EditAnywhere)
	//class USkeletalMeshComponent* WeaponMesh;

	//class UMaterial* LegendaryMaterial;
	//class UMaterial* MasterMaterial;
	//class UMaterial* RareMaterial;
	//class UMaterial* CommonMaterial;

	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float BulletDamage;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float MuzzleVelocity;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	int32 MagazineSize;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float WeaponAccuracy;

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickup(AActor* ActorThatPickedUp) override;
	UFUNCTION(BlueprintCallable)
	void OnGenerate() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void GenerateRandomBoolArray(int32 ArrayLength, int32 NumTrue, TArray<bool>& RandBoolArray);
};
