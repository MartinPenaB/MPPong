// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPaddle.generated.h"

UCLASS()
class MPPROJECT_API APlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveX(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PaddleMesh;
public:
	UPROPERTY(EditAnywhere)
	class UPongWidget* WidgetInstance;
};
