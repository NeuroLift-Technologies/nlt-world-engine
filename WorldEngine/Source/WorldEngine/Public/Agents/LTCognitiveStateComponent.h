// LTCognitiveStateComponent.h
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/NLTFusionCore.h"
#include "LTCognitiveStateComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WORLDENGINE_API ULTCognitiveStateComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULTCognitiveStateComponent();

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

    // Helper to get all values as array for LA observations
    TArray<float> GetObservationValues() const;

    // Helper to set coaching effect
    void ApplyCoachingEffect(int32 StrategyId);
};
