// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.h"
#include "AIPaddle.generated.h"

UCLASS()
class MPPROJECT_API AAIPaddle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPaddle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PaddleMesh;

	UPROPERTY(EditAnywhere)
	ABall* Ball;


};
