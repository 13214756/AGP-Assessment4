// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "FirstPersonAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//Set default member variable values
	LookSensitivity = 1.0f;
	SprintMultiplier = 1.5f;

	SpeedPercentage = 1.0f;
	bSpeedBoost = false;
	SpeedBoostTime = 0.0f;

	bCurrentlyColliding = false;
	CollidedSpawner = nullptr;

	CapsuleCollider = GetCapsuleComponent();
	//CapsuleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Capsule Collider"));
	CapsuleCollider->AttachTo(RootComponent);
	CapsuleCollider->SetGenerateOverlapEvents(true);
	CapsuleCollider->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initialise the camera variable
	Camera = FindComponentByClass<UCameraComponent>();

	// Get the skeletal mesh and then get the anim instance from it cast to the first person anim instance.
	USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(GetDefaultSubobjectByName(TEXT("Arms")));
	if (SkeletalMesh) // Make sure the skeletal mesh was found
	{
		AnimInstance = Cast<UFirstPersonAnimInstance>(SkeletalMesh->GetAnimInstance());
	}
	CapsuleCollider->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	CapsuleCollider->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpeedBoost)
	{
		SpeedBoostTime -= DeltaTime;
		if (SpeedBoostTime <= 0)
		{
			ResetSpeed();
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &APlayerCharacter::SprintEnd);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::MoveForward(float Value) 
{
	/*
		What is frame rate independence?

		This is when object movement is not tied to the frame rate. Regardless of how quickly
		each frame is calculated, objects will move the same amount over the same period
		of time. If something was frame rate dependent, the speed of movement of objects
		in the world would be tied to the framerate, so players with a higher frame rate
		would be able to move quicker than those players with weaker machines that are
		running on a lower framerate.

		Why don't we use DeltaSeconds for movement?
		
		The CharacterMovementComponent attached to the ACharacter class automatically
		deals with frame rate independence of movement. This is only the case for the 
		ACharacter class and is not the case for movement applied to APawn class derived
		actors.
	*/
	FRotator ForwardRotation = GetControlRotation();
	ForwardRotation.Roll = 0.0f;
	ForwardRotation.Pitch = 0.0f;
	if (bSpeedBoost)
	{
		Value *= SpeedPercentage;
	}
	AddMovementInput(ForwardRotation.Vector(), Value);
}

void APlayerCharacter::Strafe(float Value) 
{
	if (bSpeedBoost)
	{
		Value *= SpeedPercentage;
	}
	AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::LookUp(float Value) 
{
	/*
		Why don't we use DeltaSeconds for mouse input?

		The Value of a mouse input axis is sampled every frame by calculating the distance
		that the mouse has moved over that frame in the X and Y axes. So moving the mouse a
		certain distance over a certain period of time is the same regardless of the frame rate.
		If the frame rate is higher, the incremental distances of the mouse movement per frame
		(i.e. the Value passed into this function) will be smaller than if the frame rate was slower.
		If the frame rate is slower then those incremental distances per frame would be larger.
	*/
	FRotator LookUpRotation = FRotator::ZeroRotator;
	LookUpRotation.Pitch = Value * LookSensitivity;
	if (Camera->RelativeRotation.Pitch + LookUpRotation.Pitch < 90.0f
		&& Camera->RelativeRotation.Pitch + LookUpRotation.Pitch > -90.0f)
	{
		Camera->AddRelativeRotation(LookUpRotation);
		Camera->RelativeRotation.Yaw = 0.0f;
		Camera->RelativeRotation.Roll = 0.0f;
	}
}

void APlayerCharacter::Turn(float Value) 
{
	AddControllerYawInput(Value * LookSensitivity);
}

void APlayerCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintMultiplier;

	if (AnimInstance)
	{
		AnimInstance->bIsSprinting = true;
	}
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintMultiplier;

	if (AnimInstance)
	{
		AnimInstance->bIsSprinting = false;
	}
}

void APlayerCharacter::Reload()
{
	BlueprintReload();
}

void APlayerCharacter::Interact()
{
	if (bCurrentlyColliding)
	{
		CollidedSpawner->HideSpawner();
	}
}

void APlayerCharacter::ApplySpeedBoost(float SpeedIncrease)
{
	SpeedPercentage += (0.01f * SpeedIncrease);
	SprintMultiplier *= SpeedPercentage;
	bSpeedBoost = true;
	SpeedBoostTime += 30.0f;
	
	UE_LOG(LogTemp, Warning, TEXT("Speed is now increased by %f percent"), SpeedIncrease);

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Speed is now increased by %f percent"), SpeedIncrease));
	
}

void APlayerCharacter::ResetSpeed()
{
	bSpeedBoost = false;
	SprintMultiplier = 1.5f;
	SpeedPercentage = 1.0f;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Speed has now returned to normal")));
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//if (OtherActor && (OtherActor != this) && OtherComponent)
	//{
		CollidedSpawner = Cast<APickupsSpawner>(OtherActor);
		bCurrentlyColliding = true;
		UE_LOG(LogTemp, Warning, TEXT("Colliding with spawner"));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Can interact with spawner")));
	//}
}

void APlayerCharacter::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, int32 OtherBodyIndex)
{
	//if (OtherActor && (OtherActor != this) && OtherComponent)
	//{
		CollidedSpawner = nullptr;
		bCurrentlyColliding = false;
		UE_LOG(LogTemp, Warning, TEXT("No longer colliding with spawner"));
	//}
}
