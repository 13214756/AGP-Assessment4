// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	USceneComponent* PickupSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* PickupBoundingBox;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnEnterPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//virtual void OnExitPickup(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	virtual void OnPickup(AActor* ActorThatPickedUp);
	virtual void OnGenerate();
	/*
	class UBoxComponent* LootBoundingBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* LootBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBoxClosed;

	class AGameHUD* GameHUD;

	//virtual void OnLootBeginOverlap(class AActor* OverlapActor);*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBoxClosed;
};
