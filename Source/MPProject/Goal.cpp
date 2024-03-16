// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal.h"
#include "PlayerPaddle.h"
#include "PongWidget.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create and attach the mesh component
    GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GoalMesh"));
    RootComponent = GoalMesh;

    // Set default location and scale
    SetActorLocation(FVector(0.f, -280.f, 20.f));
    SetActorScale3D(FVector(4.f, 0.5f, 3.f));

    // Load mesh and material
    static ConstructorHelpers::FObjectFinder<UStaticMesh> GoalMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (GoalMeshAsset.Succeeded())
    {
        GoalMesh->SetStaticMesh(GoalMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/BufferVisualization/BaseColor"));
    if (MaterialAsset.Succeeded())
    {
        GoalMesh->SetMaterial(0, MaterialAsset.Object);
    }

    // Enable collision
    GoalMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    GoalMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GoalMesh->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnGoalOverlap);
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoal::OnGoalOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapped actor is the ball
    ABall* Ball = Cast<ABall>(OtherActor);
    if (Ball)
    {
        if (PlayerTarget) {
            Paddle->WidgetInstance->IncreasePlayerScore();
        }
        else {
            Paddle->WidgetInstance->IncreaseAIScore();
        }
       
        Ball->SetActorHiddenInGame(true);

        const float RespawnDelay = 2.0f; 
        FTimerHandle RespawnTimerHandle;

        GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, [Ball]() {
            
            Ball->SetActorLocation(FVector(0.f, 0.f, 38.f));
            Ball->ShootTowardsRandomPoint();
            Ball->SetActorHiddenInGame(false);

        }, RespawnDelay, false);
    }
}

