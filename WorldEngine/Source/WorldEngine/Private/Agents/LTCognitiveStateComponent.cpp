// LTCognitiveStateComponent.cpp
#include "Agents/LTCognitiveStateComponent.h"

ULTCognitiveStateComponent::ULTCognitiveStateComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

TArray<float> ULTCognitiveStateComponent::GetObservationValues() const
{
    return {Focus, CognitiveLoad, Stress, Burnout, Independence, FusionReady, SuccessRate};
}

void ULTCognitiveStateComponent::ApplyCoachingEffect(int32 StrategyId)
{
    // Apply coaching effect based on strategy (0-9)
    switch (StrategyId)
    {
    case 0: // Pomodoro
        Stress = FMath::Max(0.0f, Stress - 0.1f);
        Focus = FMath::Min(1.0f, Focus + 0.1f);
        break;
    case 1: // LadderStep
        CognitiveLoad = FMath::Max(0.0f, CognitiveLoad - 0.1f);
        Focus = FMath::Min(1.0f, Focus + 0.05f);
        break;
    case 2: // BodyDouble
        Stress = FMath::Max(0.0f, Stress - 0.15f);
        Independence = FMath::Min(1.0f, Independence + 0.05f);
        break;
    case 3: // ImplementationIntent
        CognitiveLoad = FMath::Max(0.0f, CognitiveLoad - 0.05f);
        Focus = FMath::Min(1.0f, Focus + 0.1f);
        break;
    case 4: // TwoMinuteStart
        Focus = FMath::Min(1.0f, Focus + 0.15f);
        break;
    case 5: // TaskChunking
        CognitiveLoad = FMath::Max(0.0f, CognitiveLoad - 0.15f);
        Focus = FMath::Min(1.0f, Focus + 0.05f);
        break;
    case 6: // MindfulRefocus
        Stress = FMath::Max(0.0f, Stress - 0.2f);
        Focus = FMath::Min(1.0f, Focus + 0.1f);
        break;
    case 7: // DistractionImmunize
        Focus = FMath::Min(1.0f, Focus + 0.15f);
        break;
    case 8: // AttentionAnchor
        Focus = FMath::Min(1.0f, Focus + 0.2f);
        Stress = FMath::Max(0.0f, Stress - 0.1f);
        break;
    case 9: // ShrinkTheTask
        CognitiveLoad = FMath::Max(0.0f, CognitiveLoad - 0.2f);
        Stress = FMath::Max(0.0f, Stress - 0.05f);
        break;
    default:
        break;
    }
}

void ULTCognitiveStateComponent::TickCognitiveDecay(float DeltaTime)
{
    // Increase stress/burnout over time (pressure builds)
    Stress = FMath::Min(1.0f, Stress + StressDecayRate * DeltaTime);
    Burnout = FMath::Min(1.0f, Burnout + BurnoutDecayRate * DeltaTime);
    
    // Decay focus and independence if not coached
    Focus = FMath::Max(0.0f, Focus - FocusDecayRate * DeltaTime);
    Independence = FMath::Max(0.0f, Independence - IndependenceDecayRate * DeltaTime);
}

void ULTCognitiveStateComponent::ResetCognitiveState()
{
    Focus = 0.65f;
    CognitiveLoad = 0.20f;
    Stress = 0.15f;
    Burnout = 0.05f;
    Independence = 0.20f;
    FusionReady = 0.0f;
    SuccessRate = 0.50f;
}
