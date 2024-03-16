#include "PlayerPaddle.h"
#include "PongWidget.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

   // Create and attach the mesh component
    PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
    RootComponent = PaddleMesh;

    // Set default location and scale
    SetActorLocation(FVector(0.f, -270.f, 38.f));
    SetActorScale3D(FVector(1.f, 0.5f, 0.25f));

    // Load mesh and material
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PaddleMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (PaddleMeshAsset.Succeeded())
    {
        PaddleMesh->SetStaticMesh(PaddleMeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Engine/MapTemplates/Materials/BasicAsset03"));
    if (MaterialAsset.Succeeded())
    {
        PaddleMesh->SetMaterial(0, MaterialAsset.Object);
    }
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
    WidgetInstance->AddToViewport();
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveX", this, &APlayerPaddle::MoveX);
}

void APlayerPaddle::MoveX(float Value)
{
    float Speed = 500.0f;
    float DeltaX = Speed * Value * GetWorld()->GetDeltaSeconds();
    float NewX = FMath::Clamp(GetActorLocation().X + DeltaX, -100.0f, 100.0f);
    SetActorLocation(FVector(NewX, GetActorLocation().Y, GetActorLocation().Z));
}
