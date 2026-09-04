#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "MassEntityTypes.h"
#include "NLTAgentFragments.generated.h"

USTRUCT()
struct FNLTAgentIdentityFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    FName AgentId;

    UPROPERTY()
    ENLTAgentRole Role = ENLTAgentRole::Avatar;

    UPROPERTY()
    FName ProfileId;

    UPROPERTY()
    FName DisplayName;

    UPROPERTY()
    int32 TeamId = 0;

    UPROPERTY()
    bool bIsSelected = false;

    UPROPERTY()
    int32 VisualCustomizationId = 0;
};

USTRUCT()
struct FNLTAgentLocationFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    FVector Position = FVector::ZeroVector;

    UPROPERTY()
    float Heading = 0.0f;

    UPROPERTY()
    FVector Velocity = FVector::ZeroVector;

    UPROPERTY()
    FVector TargetPosition = FVector::ZeroVector;

    UPROPERTY()
    FIntVector WorldCell = FIntVector::ZeroValue;

    UPROPERTY()
    bool bIsMoving = false;
};

USTRUCT()
struct FNLTAgentIntentFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    ENLTAgentIntent Intent = ENLTAgentIntent::Idle;

    UPROPERTY()
    float Priority = 0.0f;

    UPROPERTY()
    int32 SourceTick = 0;

    UPROPERTY()
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY()
    FName TargetTag;
};

USTRUCT()
struct FNLTAgentCognitiveFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    float Focus = 0.65f;

    UPROPERTY()
    float CognitiveLoad = 0.20f;

    UPROPERTY()
    float Stress = 0.15f;

    UPROPERTY()
    float Burnout = 0.05f;

    UPROPERTY()
    float Independence = 0.20f;

    UPROPERTY()
    float FusionReady = 0.0f;

    UPROPERTY()
    float SuccessRate = 0.50f;

    UPROPERTY()
    FName EmotionalState;
};

USTRUCT()
struct FNLTAgentNeedsFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    ENLTAgentNeed PrimaryNeed = ENLTAgentNeed::None;

    UPROPERTY()
    ENLTAgentNeed SecondaryNeed = ENLTAgentNeed::None;

    UPROPERTY()
    float Urgency = 0.0f;
};

USTRUCT()
struct FNLTAgentBehaviorFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    bool bIsExecutingBehavior = false;

    UPROPERTY()
    int32 CurrentState = 0;

    UPROPERTY()
    int32 BehaviorStartTick = 0;

    UPROPERTY()
    int32 CoachingCount = 0;
};
