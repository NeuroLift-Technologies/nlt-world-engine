#include "Scenarios/Demo/NLTDemoScenarioProcessors.h"
#include "Scenarios/Demo/NLTDemoScenarioFragments.h"
#include "Agents/NLTAgentFragments.h"
#include "Simulation/NLTSimulationSubsystem.h"
#include "World/NLTSmartObjectWorldSubsystem.h"
#include "MassEntityManager.h"
#include "MassExecutionContext.h"

DEFINE_LOG_CATEGORY_STATIC(LogNLTScenario, Log, All);

namespace
{
    /** Sorts candidate locations deterministically: score desc, distance asc, name asc. */
    struct FNLTScenarioCandidate
    {
        FVector WorldLocation = FVector::ZeroVector;
        FString DisplayName;
        float Score = 0.0f;
        float Distance = 0.0f;
    };

    /** Returns the most pressing need and its value (deterministic tie-break by enum order). */
    ENLTAgentNeed HighestNeed(const FNLTScenarioNeedsFragment& Needs, float& OutValue)
    {
        ENLTAgentNeed Best = ENLTAgentNeed::Quiet;
        float BestValue = Needs.Quiet;
        if (Needs.Rest > BestValue) { Best = ENLTAgentNeed::Rest; BestValue = Needs.Rest; }
        if (Needs.Social > BestValue) { Best = ENLTAgentNeed::Social; BestValue = Needs.Social; }
        if (Needs.Stimulation > BestValue) { Best = ENLTAgentNeed::Stimulation; BestValue = Needs.Stimulation; }
        OutValue = BestValue;
        return Best;
    }

    ENLTAgentIntent IntentForNeed(const ENLTAgentNeed Need)
    {
        switch (Need)
        {
        case ENLTAgentNeed::Quiet: return ENLTAgentIntent::FindQuietPlace;
        case ENLTAgentNeed::Rest: return ENLTAgentIntent::Rest;
        case ENLTAgentNeed::Social: return ENLTAgentIntent::Socialize;
        case ENLTAgentNeed::Stimulation: return ENLTAgentIntent::Drifting;
        default: return ENLTAgentIntent::Idle;
        }
    }

    float NeedValue(const FNLTScenarioNeedsFragment& Needs, const ENLTAgentNeed Need)
    {
        switch (Need)
        {
        case ENLTAgentNeed::Quiet: return Needs.Quiet;
        case ENLTAgentNeed::Rest: return Needs.Rest;
        case ENLTAgentNeed::Social: return Needs.Social;
        case ENLTAgentNeed::Stimulation: return Needs.Stimulation;
        default: return 0.0f;
        }
    }

    float ScoreLocationForNeed(const FNLTWorldLocation& Location, const ENLTAgentNeed Need)
    {
        switch (Need)
        {
        case ENLTAgentNeed::Quiet:
            return 1.0f - Location.NoiseLevel;
        case ENLTAgentNeed::Social:
            return Location.SocialDensity;
        case ENLTAgentNeed::Rest:
        case ENLTAgentNeed::Privacy:
            return Location.Privacy;
        case ENLTAgentNeed::Stimulation:
            return Location.SocialDensity + Location.NoiseLevel * 0.5f;
        default:
            return 0.0f;
        }
    }

    /**
     * Deterministic target selection for one agent decision pass.
     * 1. Gathers unoccupied candidate locations matching the need (TArray copy)
     * 2. Sorts deterministically: score desc, distance asc, display name asc
     * 3. Falls back to a seeded deterministic wander target when no candidate exists
     */
    void DecideTarget(const int32 SimulationTick,
        const UNLTSmartObjectWorldSubsystem* SmartWorld,
        const FNLTScenarioNeedsFragment& Needs,
        const FNLTScenarioConfigFragment& Config,
        const FNLTAgentIdentityFragment& Identity,
        const FNLTAgentLocationFragment& Location,
        FNLTScenarioBehaviorFragment& Behavior)
    {
        // Pick the most pressing need (deterministic tie-break by enum order)
        float Urgency = 0.0f;
        Behavior.DrivenNeed = HighestNeed(Needs, Urgency);

        TArray<FNLTScenarioCandidate> Candidates;
        const TArray<FNLTWorldLocation> MatchingLocations = SmartWorld->FindLocationsByNeed(Behavior.DrivenNeed);
        Candidates.Reserve(MatchingLocations.Num());

        for (const FNLTWorldLocation& Loc : MatchingLocations)
        {
            if (Loc.bIsOccupied)
            {
                continue;
            }
            FNLTScenarioCandidate Candidate;
            Candidate.WorldLocation = Loc.WorldLocation;
            Candidate.DisplayName = Loc.DisplayName;
            Candidate.Score = ScoreLocationForNeed(Loc, Behavior.DrivenNeed);
            Candidate.Distance = FVector::Dist(Location.Position, Loc.WorldLocation);
            Candidates.Add(Candidate);
        }

        Candidates.Sort([](const FNLTScenarioCandidate& A, const FNLTScenarioCandidate& B)
        {
            if (A.Score != B.Score) return A.Score > B.Score;
            if (A.Distance != B.Distance) return A.Distance < B.Distance;
            return A.DisplayName < B.DisplayName;
        });

        if (Candidates.Num() > 0)
        {
            Behavior.TargetPosition = Candidates[0].WorldLocation;
        }
        else
        {
            // Deterministic wander fallback: seeded by stable agent identity + tick
            const uint32 Seed = NLTDemoScenario::DeterministicHash(
                GetTypeHash(Identity.AgentId),
                static_cast<uint32>(SimulationTick));
            FRandomStream Stream(static_cast<int32>(Seed));
            const float Angle = Stream.FRandRange(0.0f, 2.0f * PI);
            const float Radius = Stream.FRandRange(0.25f, 1.0f) * Config.WanderRadius;
            Behavior.TargetPosition = Location.Position + FVector(
                FMath::Cos(Angle) * Radius,
                FMath::Sin(Angle) * Radius,
                0.0f);
        }

        Behavior.bHasTarget = true;
        Behavior.Phase = ENLTScenarioMovementPhase::Moving;
    }
}

//----------------------------------------------------------------------
// UNLTScenarioNeedsProcessor
//----------------------------------------------------------------------

UNLTScenarioNeedsProcessor::UNLTScenarioNeedsProcessor()
    : EntityQuery(*this)
{
    ExecutionOrder.ExecuteInGroup = TEXT("Tasks");
    bRequiresGameThreadExecution = false;
}

void UNLTScenarioNeedsProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
    EntityQuery.AddRequirement<FNLTScenarioNeedsFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FNLTScenarioConfigFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.RegisterWithProcessor(*this);
}

void UNLTScenarioNeedsProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    const float GrowthStep = NLTDemoScenario::TickDeltaSeconds;
    EntityQuery.ForEachEntityChunk(Context, [GrowthStep](FMassExecutionContext& Context)
    {
        const int32 NumEntities = Context.GetNumEntities();
        TArrayView<FNLTScenarioNeedsFragment> Needs = Context.GetMutableFragmentView<FNLTScenarioNeedsFragment>();
        TConstArrayView<FNLTScenarioConfigFragment> Configs = Context.GetFragmentView<FNLTScenarioConfigFragment>();

        for (int32 i = 0; i < NumEntities; i++)
        {
            FNLTScenarioNeedsFragment& N = Needs[i];
            const float ScaledStep = GrowthStep * Configs[i].NeedGrowthMultiplier;
            N.Quiet = NLTDemoScenario::ClampNeed(N.Quiet + NLTDemoScenario::QuietGrowthPerSecond * ScaledStep);
            N.Rest = NLTDemoScenario::ClampNeed(N.Rest + NLTDemoScenario::RestGrowthPerSecond * ScaledStep);
            N.Social = NLTDemoScenario::ClampNeed(N.Social + NLTDemoScenario::SocialGrowthPerSecond * ScaledStep);
            N.Stimulation = NLTDemoScenario::ClampNeed(N.Stimulation + NLTDemoScenario::StimulationGrowthPerSecond * ScaledStep);
        }
    });
}

//----------------------------------------------------------------------
// UNLTScenarioDecisionProcessor
//----------------------------------------------------------------------

UNLTScenarioDecisionProcessor::UNLTScenarioDecisionProcessor()
    : EntityQuery(*this)
{
    ExecutionOrder.ExecuteInGroup = TEXT("Tasks");
    ExecutionOrder.ExecuteAfter.Add(TEXT("NLTScenarioNeedsProcessor"));
    bRequiresGameThreadExecution = true; // reads world subsystem state
}

void UNLTScenarioDecisionProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
    EntityQuery.AddRequirement<FNLTScenarioNeedsFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.AddRequirement<FNLTScenarioConfigFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.AddRequirement<FNLTScenarioBehaviorFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FNLTAgentIdentityFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.AddRequirement<FNLTAgentLocationFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.AddRequirement<FNLTAgentIntentFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FNLTAgentNeedsFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.RegisterWithProcessor(*this);
}

void UNLTScenarioDecisionProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    UWorld* World = EntityManager.GetWorld();
    if (!World)
    {
        return;
    }

    const UNLTSimulationSubsystem* Sim = World->GetSubsystem<UNLTSimulationSubsystem>();
    const UNLTSmartObjectWorldSubsystem* SmartWorld = World->GetSubsystem<UNLTSmartObjectWorldSubsystem>();
    if (!Sim || !SmartWorld)
    {
        return;
    }

    const int32 SimulationTick = Sim->GetCurrentTick();

    EntityQuery.ForEachEntityChunk(Context, [SimulationTick, SmartWorld](FMassExecutionContext& Context)
    {
        const int32 NumEntities = Context.GetNumEntities();
        TConstArrayView<FNLTScenarioNeedsFragment> Needs = Context.GetFragmentView<FNLTScenarioNeedsFragment>();
        TConstArrayView<FNLTScenarioConfigFragment> Configs = Context.GetFragmentView<FNLTScenarioConfigFragment>();
        TArrayView<FNLTScenarioBehaviorFragment> Behaviors = Context.GetMutableFragmentView<FNLTScenarioBehaviorFragment>();
        TConstArrayView<FNLTAgentIdentityFragment> Identities = Context.GetFragmentView<FNLTAgentIdentityFragment>();
        TConstArrayView<FNLTAgentLocationFragment> Locations = Context.GetFragmentView<FNLTAgentLocationFragment>();
        TArrayView<FNLTAgentIntentFragment> Intents = Context.GetMutableFragmentView<FNLTAgentIntentFragment>();
        TArrayView<FNLTAgentNeedsFragment> AgentNeeds = Context.GetMutableFragmentView<FNLTAgentNeedsFragment>();

        for (int32 i = 0; i < NumEntities; i++)
        {
            FNLTScenarioBehaviorFragment& Behavior = Behaviors[i];
            Behavior.TicksSinceDecision++;

            const bool bDueForDecision = Behavior.TicksSinceDecision >= Configs[i].DecisionIntervalTicks;
            const bool bArrivedIdle = (Behavior.Phase == ENLTScenarioMovementPhase::Arrived);
            if (!bDueForDecision && !bArrivedIdle)
            {
                continue;
            }

            Behavior.TicksSinceDecision = 0;
            DecideTarget(SimulationTick, SmartWorld, Needs[i], Configs[i],
                Identities[i], Locations[i], Behavior);

            // Mirror state into the shared agent fragments (visualizer + domain)
            Intents[i].Intent = IntentForNeed(Behavior.DrivenNeed);
            Intents[i].TargetLocation = Behavior.TargetPosition;
            Intents[i].SourceTick = SimulationTick;
            AgentNeeds[i].PrimaryNeed = Behavior.DrivenNeed;
            AgentNeeds[i].Urgency = NeedValue(Needs[i], Behavior.DrivenNeed);
        }
    });
}

//----------------------------------------------------------------------
// UNLTScenarioMovementProcessor
//----------------------------------------------------------------------

UNLTScenarioMovementProcessor::UNLTScenarioMovementProcessor()
    : EntityQuery(*this)
{
    ExecutionOrder.ExecuteInGroup = TEXT("Tasks");
    ExecutionOrder.ExecuteAfter.Add(TEXT("NLTScenarioDecisionProcessor"));
    bRequiresGameThreadExecution = false;
}

void UNLTScenarioMovementProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
    EntityQuery.AddRequirement<FNLTScenarioBehaviorFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.AddRequirement<FNLTScenarioConfigFragment>(EMassFragmentAccess::ReadOnly);
    EntityQuery.AddRequirement<FNLTAgentLocationFragment>(EMassFragmentAccess::ReadWrite);
    EntityQuery.RegisterWithProcessor(*this);
}

void UNLTScenarioMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
    const float Dt = NLTDemoScenario::TickDeltaSeconds;
    EntityQuery.ForEachEntityChunk(Context, [Dt](FMassExecutionContext& Context)
    {
        const int32 NumEntities = Context.GetNumEntities();
        TArrayView<FNLTScenarioBehaviorFragment> Behaviors = Context.GetMutableFragmentView<FNLTScenarioBehaviorFragment>();
        TConstArrayView<FNLTScenarioConfigFragment> Configs = Context.GetFragmentView<FNLTScenarioConfigFragment>();
        TArrayView<FNLTAgentLocationFragment> Locations = Context.GetMutableFragmentView<FNLTAgentLocationFragment>();

        for (int32 i = 0; i < NumEntities; i++)
        {
            FNLTAgentLocationFragment& Location = Locations[i];

            FNLTScenarioBehaviorFragment& Behavior = Behaviors[i];

            if (!Behavior.bHasTarget || Behavior.Phase == ENLTScenarioMovementPhase::Arrived)
            {
                Location.bIsMoving = false;
                Location.Velocity = FVector::ZeroVector;
                continue;
            }

            const FVector ToTarget = Behavior.TargetPosition - Location.Position;
            const float Distance = ToTarget.Size();
            const float Step = Configs[i].MovementSpeed * Dt;

            if (Distance <= FMath::Max(Step, Configs[i].ArrivalRadius))
            {
                Location.Position = Behavior.TargetPosition;
                Location.Velocity = FVector::ZeroVector;
                Location.bIsMoving = false;
                Behavior.Phase = ENLTScenarioMovementPhase::Arrived;
                Behavior.bHasTarget = false;
            }
            else
            {
                const FVector Dir = ToTarget / Distance;
                Location.Position += Dir * Step;
                Location.Velocity = Dir * Configs[i].MovementSpeed;
                Location.Heading = FMath::RadiansToDegrees(FMath::Atan2(Dir.Y, Dir.X));
                Location.bIsMoving = true;
            }

            Location.WorldCell = FIntVector(
                FMath::FloorToInt32(Location.Position.X / 100.0f),
                FMath::FloorToInt32(Location.Position.Y / 100.0f),
                0);
        }
    });
}
