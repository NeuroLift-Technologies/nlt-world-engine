#pragma once

#include "CoreMinimal.h"
#include "MassEntityQuery.h"
#include "MassProcessor.h"
#include "NLTDemoScenarioProcessors.generated.h"

/**
 * Grows each agent's need drives at fixed per-second rates using the fixed
 * simulation timestep (NLTDemoScenario::TickDeltaSeconds). Deterministic:
 * no wall-clock delta time, no random variation. Parallel-safe (fragment-local
 * writes only). Must run before the decision processor.
 */
UCLASS()
class UNLTScenarioNeedsProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UNLTScenarioNeedsProcessor();

protected:
    virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
    virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

    FMassEntityQuery EntityQuery;
};

/**
 * Deterministic decision-making pass. Every DecisionIntervalTicks an agent
 * re-evaluates its highest need and selects a target location:
 *  1. Gathers candidate world locations matching the need (TArray copy)
 *  2. Sorts candidates deterministically (score desc, distance asc, name asc)
 *  3. Falls back to a deterministic seeded wander target when no candidate exists
 * Writes Intent/TargetPosition into the shared agent fragments so the
 * visualizer and StateTree stay consistent.
 */
UCLASS()
class UNLTScenarioDecisionProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UNLTScenarioDecisionProcessor();

protected:
    virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
    virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

    FMassEntityQuery EntityQuery;
};

/**
 * Custom movement integration (no Chaos physics): closed-form step toward the
 * behavior target at the agent's configured speed over the fixed timestep.
 * Updates the shared location fragment (Position/Velocity/Heading/bIsMoving)
 * and updates behavior phase on arrival so decisions can re-evaluate immediately.
 * Parallel-safe.
 */
UCLASS()
class UNLTScenarioMovementProcessor : public UMassProcessor
{
    GENERATED_BODY()

public:
    UNLTScenarioMovementProcessor();

protected:
    virtual void ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager) override;
    virtual void Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context) override;

    FMassEntityQuery EntityQuery;
};
