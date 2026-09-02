#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "MassEntityTypes.h"
#include "NLTDemoScenarioFragments.generated.h"

/**
 * Numeric need drives for scenario agents (all values clamped to 0..1).
 * Grown deterministically by UNLTScenarioNeedsProcessor, consumed by
 * UNLTScenarioDecisionProcessor and the StateTree conditions.
 * Complements the enum-level FNLTAgentNeedsFragment (PrimaryNeed/Urgency).
 */
USTRUCT()
struct FNLTScenarioNeedsFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    float Quiet = 0.20f;

    UPROPERTY()
    float Rest = 0.10f;

    UPROPERTY()
    float Social = 0.30f;

    UPROPERTY()
    float Stimulation = 0.25f;
};

/**
 * Per-agent tuning for the demo scenario systems. Values are fixed at spawn
 * (deterministic seeding) and never mutated during the simulation.
 */
USTRUCT()
struct FNLTScenarioConfigFragment : public FMassFragment
{
    GENERATED_BODY()

    /** Movement speed in cm/s (custom movement, no Chaos). */
    UPROPERTY()
    float MovementSpeed = 150.0f;

    /** Distance at which an agent is considered to have arrived (cm). */
    UPROPERTY()
    float ArrivalRadius = 100.0f;

    /** Decision re-evaluation period in simulation ticks (60 ticks = 1s at fixed 60Hz). */
    UPROPERTY()
    int32 DecisionIntervalTicks = 60;

    /** Max radius (cm) for deterministic wander targets when no location matches. */
    UPROPERTY()
    float WanderRadius = 1500.0f;

    /** Multiplier applied to all need growth rates. Set from the scenario data
     *  asset (aversiveness + cognitive demand); 1.0 = baseline. */
    UPROPERTY()
    float NeedGrowthMultiplier = 1.0f;
};

/** Movement phase of a scenario agent. */
UENUM()
enum class ENLTScenarioMovementPhase : uint8
{
    Idle,
    Moving,
    Arrived
};

/**
 * Per-tick behavior state written by the decision processor and read by the
 * movement processor and StateTree tasks.
 */
USTRUCT()
struct FNLTScenarioBehaviorFragment : public FMassFragment
{
    GENERATED_BODY()

    UPROPERTY()
    ENLTScenarioMovementPhase Phase = ENLTScenarioMovementPhase::Idle;

    UPROPERTY()
    ENLTAgentNeed DrivenNeed = ENLTAgentNeed::None;

    UPROPERTY()
    FVector TargetPosition = FVector::ZeroVector;

    UPROPERTY()
    bool bHasTarget = false;

    UPROPERTY()
    int32 TicksSinceDecision = 0;
};

/** Deterministic constants shared by the demo scenario simulation systems. */
namespace NLTDemoScenario
{
    /** Fixed simulation timestep. 600 ticks = 10s (matches QA determinism gate). */
    constexpr float TickDeltaSeconds = 1.0f / 60.0f;

    /** Per-second growth rates for each need drive (deterministic, no runtime variation). */
    constexpr float QuietGrowthPerSecond = 0.060f;
    constexpr float RestGrowthPerSecond = 0.030f;
    constexpr float SocialGrowthPerSecond = 0.045f;
    constexpr float StimulationGrowthPerSecond = 0.050f;

    /** Clamps a need value into the valid 0..1 range. */
    inline float ClampNeed(const float Value)
    {
        return FMath::Clamp(Value, 0.0f, 1.0f);
    }

    /** Deterministic 32-bit hash of two integers (FNV-1a style, stable across platforms). */
    inline uint32 DeterministicHash(const uint32 A, const uint32 B)
    {
        uint32 Hash = 2166136261u;
        Hash = (Hash ^ A) * 16777619u;
        Hash = (Hash ^ B) * 16777619u;
        return Hash;
    }
}
