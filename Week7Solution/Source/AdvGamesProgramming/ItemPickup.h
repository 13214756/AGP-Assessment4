// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "ItemPickup.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemPickupType : uint8
{
	HEALTH,
	ATTACK,
	DEFENCE,
	SPEED
};

UENUM(BlueprintType)
enum class EItemPickupRarity : uint8
{
	LEGENDARY,
	MASTER,
	RARE,
	COMMON
};


UCLASS()
class ADVGAMESPROGRAMMING_API AItemPickup : public APickup
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnPickup(AActor* ActorThatPickedUp) override;

	UFUNCTION(BlueprintCallable)
		void OnGenerate() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float Health;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float Attack;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float Defence;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		float Speed;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		EItemPickupType Type;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		EItemPickupRarity Rarity;

	int32 rand;
	int32 randMaster;
	int32 randRare;
	int32 randItem;
};
