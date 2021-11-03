// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ArenaAndWall.generated.h"

UCLASS()
class ADVGAMESPROGRAMMING_API AArenaAndWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArenaAndWall();
	UProceduralMeshComponent* Floor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<AActor>> WallClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> WallClass;



	UPROPERTY(EditAnywhere)
		int32 Width;
	UPROPERTY(EditAnywhere)
		int32 Height;
	UPROPERTY(EditAnywhere)
		float GridSize;
	UPROPERTY(EditAnywhere)
		float PerlinRoughness;
	UPROPERTY(EditAnywhere)
		float PerlinOffset;
	UPROPERTY(EditAnywhere)
		bool bRegenerateMap;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVCoords;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

	UFUNCTION(BlueprintCallable)
		void GenerateMap();

	virtual bool ShouldTickIfViewportsOnly() const override;

	void ClearMap();

	UPROPERTY(EditAnywhere)
		float WallHeight;
	UPROPERTY(EditAnywhere)
		float WallLength;
	UPROPERTY(EditAnywhere)
		float WallWidth;
	UPROPERTY(EditAnywhere)
		float WallRadius;
	UPROPERTY(EditAnywhere)
		bool bAddPerlinNoise;

	TArray<AActor*> WallsGenerated;

	void GenerateWalls();

	void CreateOuterWall();

	FVector GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
