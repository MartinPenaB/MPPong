// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/GameplayStatics.h"

ABall* ABall::Instance = nullptr;

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and attach the mesh component
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    // Set default location and scale
    SetActorLocation(FVector(0.f, 0.f, 38.f));
    SetActorScale3D(FVector(0.25f, 0.25f, 0.25f));

    // Load sphere mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Engine/BasicShapes/Sphere"));
    if (SphereMeshAsset.Succeeded())
    {
        BallMesh->SetStaticMesh(SphereMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset02"));
    if (MaterialAsset.Succeeded())
    {
        BallMesh->SetMaterial(0, MaterialAsset.Object);
    }
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
    Instance = this;
    ShootTowardsRandomPoint();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    float Speed = 500.0f;
    FVector CurrentVelocity = BallMesh->GetComponentVelocity().GetSafeNormal();
    FVector NewVelocity = CurrentVelocity * Speed;
    NewVelocity.Z = 0.0f; // Ensure no movement along the Z-axis
    BallMesh->SetPhysicsLinearVelocity(NewVelocity, false);
}

void ABall::ShootTowardsRandomPoint()
{
    // Get a random point on the screen
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = FVector(FMath::RandRange(-1000.0f, 1000.0f), FMath::RandRange(-1000.0f, 1000.0f), StartLocation.Z);

    // Calculate velocity direction
    FVector LaunchDirection = (EndLocation - StartLocation).GetSafeNormal();

    // Shoot the ball
    float LaunchSpeed = 2000.0f;
    BallMesh->SetPhysicsLinearVelocity(LaunchDirection * LaunchSpeed, false);
}

ABall* ABall::GetInstance()
{
    return Instance;
}

