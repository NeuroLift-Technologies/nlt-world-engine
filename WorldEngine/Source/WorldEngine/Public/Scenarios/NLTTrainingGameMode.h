// NLTTrainingGameMode.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NLTTrainingGameMode.generated.h"

/**
 * Training game mode — spawns NLTTrainingManager for PPO training.
 */
UCLASS()
class WORLDENGINE_API ANLTTrainingGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANLTTrainingGameMode();

    virtual void BeginPlay() override;
};
