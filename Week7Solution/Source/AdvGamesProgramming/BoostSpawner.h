// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LootSpawner.h"
#include "BoostSpawner.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBoostPickupType : uint8
{
	HEALTH,
	ATTACK,
	DEFENCE,
	SPEED
};

enum class EBoostPickupRarity : uint8
{
	LEGENDARY,
	MASTER,
	RARE,
	COMMON
};

UCLASS()
class ADVGAMESPROGRAMMING_API ABoostSpawner : public ALootSpawner
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnPickup(AActor* ActorThatPickedUp) override;
	//UPROPERTY(EditAnywhere)
	//class USkeletalMeshComponent* BoostMesh;
	UFUNCTION(BlueprintCallable)
	void OnGenerate() override;

	//void BoxOpen() override;

	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float Health;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float Attack;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float Defence;
	UPROPERTY(Replicated, BlueprintReadOnly, VisibleAnywhere)
	float Speed;
	/*
	UFUNCTION(BlueprintImplementableEvent)
	void ApplyAttackBoost(float AttackBoost);

	UPROPERTY(BlueprintReadOnly)
	class AActor* PickUpActor;

	//class UMaterial* HealthMaterial;
	//class UMaterial* AttackMaterial;
	//class UMaterial* DefenceMaterial;
	//class UMaterial* SpeedMaterial;

	class UHealthComponent* PickedUpHealthComponent;
	class APlayerCharacter* PickedUpPlayerCharacter;
	*/
	UPROPERTY(Replicated, BlueprintReadOnly)
		EBoostPickupType Type;

	EBoostPickupRarity Rarity;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int32 Rand;
	int32 RandItem;
};
