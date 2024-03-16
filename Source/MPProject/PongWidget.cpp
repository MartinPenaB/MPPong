#include "PongWidget.h"
#include "Components/TextBlock.h"

void UPongWidget::IncreasePlayerScore()
{
    // Increase player score
    PlayerScoreValue++;

    // Update player score text
    if (PlayerScore)
    {
        PlayerScore->SetText(FText::FromString(FString::Printf(TEXT("Your Score: %d"), PlayerScoreValue)));
    }
}

void UPongWidget::IncreaseAIScore()
{
    // Increase AI score
    AIScoreValue++;

    // Update AI score text
    if (AIScore)
    {
        AIScore->SetText(FText::FromString(FString::Printf(TEXT("Opponent Score: %d"), AIScoreValue)));
    }
}
