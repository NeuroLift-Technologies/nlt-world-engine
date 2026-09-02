#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NLTDemoGameMode.generated.h"

/**
 * Demo game mode for NLT Fusion scenario simulation.
 * On BeginPlay, loads a default scenario and starts the simulation.
 */
UCLASS()
class WORLDENGINE_API ANLTDemoGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ANLTDemoGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    /** Default scenario to load on startup. */
    UPROPERTY(EditAnywhere, Category = "NLT|Scenario")
        FName DefaultScenarioId = TEXT("wp_1");
};
