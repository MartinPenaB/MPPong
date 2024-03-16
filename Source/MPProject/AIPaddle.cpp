// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPaddle.h"

// Sets default values
AAIPaddle::AAIPaddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and attach the mesh component
    PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
    RootComponent = PaddleMesh;

    // Set default location and scale
    SetActorLocation(FVector(0.f, 270.f, 38.f));
    SetActorScale3D(FVector(1.f, 0.5f, 0.25f));

    // Load mesh and material
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PaddleMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (PaddleMeshAsset.Succeeded())
    {
        PaddleMesh->SetStaticMesh(PaddleMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset01"));
    if (MaterialAsset.Succeeded())
    {
        PaddleMesh->SetMaterial(0, MaterialAsset.Object);
    }
}

// Called when the game starts or when spawned
void AAIPaddle::BeginPlay()
{
	Super::BeginPlay();
    Ball = ABall::GetInstance();
}

// Called every frame
void AAIPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (Ball)
    {
        FVector BallLocation = Ball->GetActorLocation();
        float ClampedX = FMath::Clamp(BallLocation.X/3, -100.0f, 100.0f);
        FVector NewLocation = FVector(ClampedX, GetActorLocation().Y, GetActorLocation().Z);
        SetActorLocation(NewLocation);


    }

}

