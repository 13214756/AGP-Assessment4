// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PickupsSpawner.h"
#include "HealthComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float SprintMovementSpeed;
	float NormalMovementSpeed;

public:	

	UPROPERTY(EditAnywhere)
	float LookSensitivity;
	UPROPERTY(EditInstanceOnly)
	float SprintMultiplier;

	UHealthComponent* HealthComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void Strafe(float Value);
	void LookUp(float Value);
	void Turn(float Value);
	void SprintStart();
	void SprintEnd();
	void Reload();
	void Interact();

	UFUNCTION(BlueprintImplementableEvent)
	void BlueprintReload();

	UFUNCTION(Server, Reliable)
		void ServerSprintStart();
	UFUNCTION(Server, Reliable)
		void ServerSprintEnd();

	float SpeedPercentage;
	bool bSpeedBoost;
	float SpeedBoostTime;

	UFUNCTION(BlueprintCallable)
	virtual void ApplySpeedBoost(float SpeedIncrease);
	void ResetSpeed();

	class APickupsSpawner* CollidedSpawner;
	//class AActor* EmptyActor;
	bool bCurrentlyColliding;

	//UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleCollider;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

private:

	UCameraComponent* Camera;
	class UFirstPersonAnimInstance* AnimInstance;
};
