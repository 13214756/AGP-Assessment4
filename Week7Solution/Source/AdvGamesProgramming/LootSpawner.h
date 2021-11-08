// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootSpawner.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API ALootSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALootSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	USceneComponent* LootSceneComponent;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* LootBoundingBox;

	UFUNCTION()
		virtual void OnEnterLoot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnPickup(AActor* ActorThatPickedUp);
	virtual void OnGenerate();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		bool bBoxClosed;
	float TimeTillAutoDestroy;

	FVector SpawnLocation;
	FRotator SpawnRotation;
	FActorSpawnParameters SpawnInfo;

	UFUNCTION(BlueprintCallable)
		void SpawnNewPickup();
	virtual void BoxOpen();
	void DestroySelf();

	class APickupsSpawner* AssociatedSpawner;

	UFUNCTION(Server, Reliable)
		void ServerSpawnNewPickup();
	UFUNCTION(Server, Reliable)
		void ServerDestroySelf();
};
