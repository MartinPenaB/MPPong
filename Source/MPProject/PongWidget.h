// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PongWidget.generated.h"

/**
 * 
 */
UCLASS()
class MPPROJECT_API UPongWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerScore;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* AIScore;

	// Function to increase player score and update text
	UFUNCTION(BlueprintCallable)
	void IncreasePlayerScore();

	// Function to increase AI score and update text
	UFUNCTION(BlueprintCallable)
	void IncreaseAIScore();

private:
	int32 PlayerScoreValue = 0;
	int32 AIScoreValue = 0;
	
};
