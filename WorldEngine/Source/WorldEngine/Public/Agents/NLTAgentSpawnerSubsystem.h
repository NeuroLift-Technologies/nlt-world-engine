#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "MassEntityTypes.h"
#include "MassEntitySubsystem.h"
#include "NLTAgentSpawnerSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTAgentSpawner, Log, All);

USTRUCT(BlueprintType)
struct FNLTSpawnRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FName ProfileId;

    UPROPERTY(BlueprintReadWrite)
    ENLTAgentRole Role = ENLTAgentRole::Avatar;

    UPROPERTY(BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(BlueprintReadWrite)
    FVector Position = FVector::ZeroVector;
};

UCLASS()
class UNLTAgentSpawnerSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "NLT|Agents")
    void SpawnAgent(const FNLTSpawnRequest& Request);

    UFUNCTION(BlueprintCallable, Category = "NLT|Agents")
    void SpawnAgents(int32 Count, const FVector& Origin, float Radius);

    /** Spawns agents by profile/type name at a default origin with a default radius. */
    UFUNCTION(BlueprintCallable, Category = "NLT|Agents")
    void SpawnAgentsByType(FName AgentType, int32 Count);

    /** Deterministic spawn: positions and per-agent scenario fragment values are
     *  derived from Seed (FRandomStream + stable per-agent hash). Same seed and
     *  count produce byte-identical agent setups. */
    void SpawnAgentsDeterministic(int32 Count, const FVector& Origin, float Radius, int32 Seed);

    UFUNCTION(BlueprintCallable, Category = "NLT|Agents")
    void DespawnAllAgents();

    UFUNCTION(BlueprintPure, Category = "NLT|Agents")
    int32 GetAgentCount() const { return AgentCount; }

    UFUNCTION(BlueprintCallable, Category = "NLT|Agents")
    void SetSpawnSeed(int32 InSeed) { SpawnSeed = InSeed; }

    /** Applied to FNLTScenarioConfigFragment.NeedGrowthMultiplier at spawn (1.0 = baseline). */
    UFUNCTION(BlueprintCallable, Category = "NLT|Agents")
    void SetNeedGrowthMultiplier(float InMultiplier) { NeedGrowthMultiplier = FMath::Max(0.0f, InMultiplier); }

private:
    int32 AgentCount = 0;
    int32 SpawnSeed = 12345;
    float NeedGrowthMultiplier = 1.0f;
    TArray<FMassEntityHandle> SpawnedEntities;

    /** Adds the demo-scenario fragments (needs/config/behavior) with deterministic values. */
    void AppendScenarioFragments(TArray<FInstancedStruct>& Fragments, int32 AgentIndex);
};
