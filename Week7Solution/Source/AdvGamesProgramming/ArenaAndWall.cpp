// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaAndWall.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
AArenaAndWall::AArenaAndWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh Component"));
	RootComponent = Floor;

	Width = 50.0f;
	Height = 50.0f;
	GridSize = 100.0f;

	bRegenerateMap = false;
	//Initalization of variables to fit wall dimensions 400x20x300
	WallLength = 400.0f;
	WallWidth = 20.0f;
	WallHeight = 300.0f;
	WallRadius = 400.f;
	//Addition of Perlin Noise is off by default with the offset randomly generated
	bAddPerlinNoise = false;
	PerlinRoughness = 0.1f;
	PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);
}

// Called when the game starts or when spawned
void AArenaAndWall::BeginPlay()
{
	Super::BeginPlay();
	
	//Creates both the inner and outer walls
	GenerateWalls();
	CreateOuterWall();
}

// Called every frame
void AArenaAndWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRegenerateMap)
	{
		ClearMap();
		GenerateMap();

		bRegenerateMap = false;
	}

}

bool AArenaAndWall::ShouldTickIfViewportsOnly() const
{
	return true;
}

//Map creation from lab 6 without the different Z values
void AArenaAndWall::GenerateMap()
{
	for (int32 Y = 0; Y < Height; Y++)
	{
		for (int32 X = 0; X < Width; X++)
		{
			Vertices.Add(FVector(X * GridSize, Y * GridSize, 0.0));
			UVCoords.Add(FVector2D(X, Y));

			if (X != Width - 1 && Y != Height - 1)
			{
				Triangles.Add(Y * Width + X);
				Triangles.Add((Y + 1) * Width + X);
				Triangles.Add(Y * Width + X + 1);
				Triangles.Add(Y * Width + X + 1);
				Triangles.Add((Y + 1) * Width + X);
				Triangles.Add((Y + 1) * Width + X + 1);
			}
		}
	}

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVCoords, Normals, Tangents);

	Floor->CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords, TArray<FColor>(), Tangents, true);

	UE_LOG(LogTemp, Warning, TEXT("Vertices Count: %i | UVCoords Count: %i | Triangles Count: %i"), Vertices.Num(), UVCoords.Num(), Triangles.Num())

}

//Clears the map so that it can be regenerated
void AArenaAndWall::ClearMap()
{
	Triangles.Empty();
	Vertices.Empty();
	UVCoords.Empty();
	Floor->ClearAllMeshSections();

	WallsGenerated.Empty();

}

FVector AArenaAndWall::GetRandomPointInSquare(const FVector& UpperLeft, const FVector& LowerRight)
{

	float RandomX = FMath::FRandRange(UpperLeft.X, LowerRight.X);
	float RandomY = FMath::FRandRange(UpperLeft.Y, LowerRight.Y);
	if (RandomX < (WallRadius / 2))
	{
		RandomX = FMath::FRandRange((WallRadius / 2), ((Width * GridSize) - (WallLength * 2) + GridSize));
	}
	if (RandomY < WallRadius)
	{
		RandomY = FMath::FRandRange(WallRadius, ((Height * GridSize) - WallLength));
	}
	if (RandomX > ((Width * GridSize) - (WallLength * 2)))
	{
		RandomX = FMath::FRandRange(((Width * GridSize) - (WallLength * 3)), ((Width * GridSize) - (WallLength * 2) + GridSize));
	}
	if (RandomY > (Height * GridSize) - WallLength)
	{
		RandomY = FMath::FRandRange(((Height * GridSize) - WallLength * 2), ((Height * GridSize) - WallLength));
	}

	return FVector(RandomX, RandomY, 1.f);
}


/* Function to generate the walls, contains the perlin noise calculation, random wall type selection spawn location and collsion prevention algorithm */
void AArenaAndWall::GenerateWalls()
{

	for (int32 i = 0; i < (((Width * GridSize) / WallLength)); i++)
	{
		for (int32 j = 0; j < (((Height * GridSize) / WallLength)); j++)
		{
			//Assigns the wall spawn point based on the Width and height of the Floor,the wall length and wall radius to prevent collisions 
			FVector UpperLeft = FVector((i * (WallLength * 1.5f)) + (WallRadius), (j * (WallLength * 1.5f)) + (WallRadius), 1.0f);
			FVector LowerRight = FVector(((i * (WallLength * 1.5f)) - (WallRadius), ((j * (WallLength * 1.5f)) - (WallRadius), 1.0f)));
			FVector SetPointInSquare = FVector((UpperLeft.X + LowerRight.X / 2), (UpperLeft.Y + LowerRight.Y / 2), 2.0f);

			//RandomYaw to determine the rotation of each wall
			float RandomYaw = 0.0f;
			RandomYaw = FMath::FRandRange(0.0f, 360.0f);
			// bool to prevent walls spawning if they are out of bounds 
			bool bDontSpawn = false;

			//Adds a noise function to the wall spawns so that some walls will not spawn (these locations will be the same based on the Perlin Offset)
			if (bAddPerlinNoise)
			{
				float NoiseOffset = FMath::PerlinNoise2D((FVector2D(SetPointInSquare.X * PerlinRoughness + PerlinOffset, SetPointInSquare.Y * PerlinRoughness + PerlinOffset)));

				if (NoiseOffset < 0.0f)
				{
					bDontSpawn = true;
				}
				if (NoiseOffset >= 0.0f)
				{
					bDontSpawn = false;
				}
			}





			//Boundary conditions for wall generation - these walls will not spawn or will have their rotations restricted to prevent collisions
			if (SetPointInSquare.X > ((Width * GridSize) - (WallLength * 0.75f)))
			{
				bDontSpawn = true;
			}
			if (SetPointInSquare.Y > (Height * GridSize))
			{
				bDontSpawn = true;
			}
			if (SetPointInSquare.X < ((Width * GridSize) - (WallLength * 0.75f)) && SetPointInSquare.X >((Width * GridSize) - (WallLength * 2)))
			{
				RandomYaw = FMath::FRandRange(90.0f, 270.0f);
			}
			if (SetPointInSquare.Y > ((Height * GridSize) - WallLength) && SetPointInSquare.Y < (Height * GridSize))
			{
				RandomYaw = FMath::FRandRange(180.f, 270.f);
			}

			//This WallTypeValue determines the kind of wall that will be spawned based on an array of blueprint objects in the derived blueprint BP_PCG_Wall
			int32 WallTypeValue = FMath::RandRange(1, 3);
			if (WallTypeValue == 1)
			{
				WallClass = WallClasses[0];
			}
			if (WallTypeValue == 2)
			{
				WallClass = WallClasses[1];
			}
			if (WallTypeValue == 3)
			{
				WallClass = WallClasses[2];
			}
			//SpawnInfo determines the spawn collision handling system for the spawned walls, as the boundary formulas prevent collisions this is set to always spawn
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

			//Will spawn a wall within the bounds at a set location with a RandomYaw rotation
			if (!bDontSpawn)
			{
				WallsGenerated.Add(GetWorld()->SpawnActor<AActor>(WallClass, SetPointInSquare, FRotator(0, RandomYaw, 0), SpawnInfo));
				/*
				WallsGenerated.Add(GetWorld()->SpawnActorDeferred<AActor>(WallClass, FTransform(FRotator(0, RandomYaw, 0), GetRandomPointInSquare(UpperLeft,LowerRight),  FVector(1.f))));
				WallsGenerated[WallsGenerated.Num() - 1]->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
				WallsGenerated[WallsGenerated.Num() - 1]->FinishSpawning(FTransform(FRotator(0, RandomYaw, 0), GetRandomPointInSquare(UpperLeft, LowerRight), FVector(1.f)));


				WallsGenerated.Add(GetWorld()->SpawnActorDeferred<AActor>(WallClass, FTransform(FRotator(0, 220.f, 0), SetPointInSquare, FVector(1.f))));
				WallsGenerated[WallsGenerated.Num() - 1]->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
				WallsGenerated[WallsGenerated.Num() - 1]->FinishSpawning(FTransform(FRotator(0, RandomYaw, 0), SetPointInSquare, FVector(1.f)));
				*/
			}

		}
	}

}



void AArenaAndWall::CreateOuterWall()
{
	//Takes a different wall type than the inner walls to prevent collisions
	WallClass = WallClasses[3];

	//Creates the first part of the walls except the final wall
	for (int32 i = 0; i < (Width * GridSize) - WallLength; i += WallLength)
	{
		GetWorld()->SpawnActor<AActor>(WallClass, FVector(i, 0.0f, 0.0f), FRotator(0.0f));
	}
	for (int32 i = 0; i < (Height * GridSize) - WallLength; i += WallLength)
	{
		GetWorld()->SpawnActor<AActor>(WallClass, FVector(0.0f, i, 0.0f), FRotator(0.0f, 90.0f, 0.0f));
	}
	float GridParameter = Width;

	if (Width > Height)
	{
		GridParameter = Height;

	}
	else if (Width < Height)
	{
		GridParameter = Width;
	}
	for (int32 i = (GridParameter * GridSize) - WallLength; i > 0; i -= WallLength)
	{
		GetWorld()->SpawnActor<AActor>(WallClass, FVector((Width * GridSize) - Width * 2, i, 0.0f), FRotator(0.0f, 270.0f, 0.0f));
	}

	for (int32 i = (GridParameter * GridSize) - WallLength; i > 0; i -= WallLength)
	{
		GetWorld()->SpawnActor<AActor>(WallClass, FVector(i, (Height * GridSize) - Height * 2, 0.0f), FRotator(0.0f, 180.0f, 0.0f));
	}

	//Spawns the final walls with an altered scale based on the modulus of the total grid size and wall length
	float WallRemainder = FMath::Fmod((Width * GridSize), WallLength);
	if (WallRemainder == 0)
	{
		WallRemainder = 1.0f;
	}
	FVector WallScale = FVector(WallRemainder, WallWidth, WallHeight);
	WallClass->GetDefaultObject<AActor>()->SetActorScale3D(WallScale);


	GetWorld()->SpawnActor<AActor>(WallClass, FVector((Width * GridSize) - WallLength, 0.0f, 0.0f), FRotator(0.0f));
	GetWorld()->SpawnActor<AActor>(WallClass, FVector(0.0f, (Height * GridSize) - WallLength, 0.0f), FRotator(0.0f, 90.0f, 0.0f));
	GetWorld()->SpawnActor<AActor>(WallClass, FVector((Width * GridSize) - Width * 2, (Width * GridSize), 0.0f), FRotator(0.0f, 270.0f, 0.0f));
	GetWorld()->SpawnActor<AActor>(WallClass, FVector((Width * GridSize), (Height * GridSize) - Height * 2, 0.0f), FRotator(0.0f, 180.0f, 0.0f));
}
