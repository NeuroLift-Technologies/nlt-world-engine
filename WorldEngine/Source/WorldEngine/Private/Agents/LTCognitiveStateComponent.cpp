// LTCognitiveStateComponent.cpp
#include "Agents/LTCognitiveStateComponent.h"
#include "Agents/NLTEmotionStateComponent.h"

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
    EmotionalState = NAME_None;
}

void ULTCognitiveStateComponent::UpdateEmotionalState()
{
    // Derive EmotionalState FName from the emotion state component's
    // CurrentEmotion enum, ensuring a single source of truth with
    // UNLTEmotionStateComponent. This respects intent, temporary overrides
    // (Working, Coached, Celebrating), and customized thresholds — so typed
    // consumers and FName consumers always receive the same state.
    if (AActor* Owner = GetOwner())
    {
        if (const UNLTEmotionStateComponent* EmotionComp =
            Owner->FindComponentByClass<UNLTEmotionStateComponent>())
        {
            // Convert the enum to the matching FName string. This is a
            // pure type conversion — not threshold logic — so it stays
            // in sync with the sim-driven emotion state machine.
            switch (EmotionComp->CurrentEmotion)
            {
            case ENLTEmotionState::Neutral:     EmotionalState = FName(TEXT("Neutral")); break;
            case ENLTEmotionState::Focused:     EmotionalState = FName(TEXT("Focused")); break;
            case ENLTEmotionState::Working:     EmotionalState = FName(TEXT("Working")); break;
            case ENLTEmotionState::Struggling:  EmotionalState = FName(TEXT("Struggling")); break;
            case ENLTEmotionState::Overwhelmed: EmotionalState = FName(TEXT("Overwhelmed")); break;
            case ENLTEmotionState::Drifting:    EmotionalState = FName(TEXT("Drifting")); break;
            case ENLTEmotionState::Hyperfocus:  EmotionalState = FName(TEXT("Hyperfocus")); break;
            case ENLTEmotionState::Coached:     EmotionalState = FName(TEXT("Coached")); break;
            case ENLTEmotionState::Fatigued:    EmotionalState = FName(TEXT("Fatigued")); break;
            case ENLTEmotionState::Celebrating: EmotionalState = FName(TEXT("Celebrating")); break;
            default:                            EmotionalState = NAME_None; break;
            }
            return;
        }
    }

    // Fallback: clear the state if the emotion component is unavailable.
    EmotionalState = NAME_None;
}
