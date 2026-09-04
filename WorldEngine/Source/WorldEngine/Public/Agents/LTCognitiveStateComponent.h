// LTCognitiveStateComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/NLTFusionCore.h"
#include "LTCognitiveStateComponent.generated.h"

/**
 * Cognitive state component for Avatar characters.
 * Tracks 7 cognitive dimensions: Focus, CognitiveLoad, Stress, Burnout, Independence, FusionReady, SuccessRate.
 * Supports coaching effects and temporal decay for training dynamics.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API ULTCognitiveStateComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULTCognitiveStateComponent();

    /** Get all cognitive values as array for LA observations (7 dims: Focus, CognitiveLoad, Stress, Burnout, Independence, FusionReady, SuccessRate) */
    TArray<float> GetObservationValues() const;

    /** Apply coaching effect based on strategy ID (0-9) */
    void ApplyCoachingEffect(int32 StrategyId);

    /** Tick cognitive decay/growth over time. Call each step. */
    void TickCognitiveDecay(float DeltaTime);

    /** Reset all cognitive values to defaults */
    void ResetCognitiveState();

    // Core cognitive dimensions
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float Focus = 0.65f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float CognitiveLoad = 0.20f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float Stress = 0.15f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float Burnout = 0.05f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float Independence = 0.20f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float FusionReady = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    float SuccessRate = 0.50f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive")
    FName EmotionalState;

    // Decay rates per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive|Decay")
    float StressDecayRate = 0.01f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive|Decay")
    float BurnoutDecayRate = 0.005f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive|Decay")
    float FocusDecayRate = 0.02f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognitive|Decay")
    float IndependenceDecayRate = 0.001f;
};
