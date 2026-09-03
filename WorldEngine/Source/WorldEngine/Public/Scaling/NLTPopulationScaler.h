#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTPopulationScaler.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTPopulationScaler, Log, All);

USTRUCT(BlueprintType)
struct FNLTScaleMetrics
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 AgentCount = 0;

    UPROPERTY(BlueprintReadWrite)
    float FrameTime = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    float SimulationTickTime = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    float MemoryUsageMB = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    float MassProcessorTime = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    float StateTreeTime = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    float NavigationTime = 0.0f;

    UPROPERTY(BlueprintReadWrite)
    int32 ActiveEntities = 0;

    UPROPERTY(BlueprintReadWrite)
    float CognitionLatency = 0.0f;
};

UCLASS()
class UNLTPopulationScaler : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "NLT|Scaling")
    void StartBenchmark();

    UFUNCTION(BlueprintCallable, Category = "NLT|Scaling")
    void StopBenchmark();

    UFUNCTION(BlueprintCallable, Category = "NLT|Scaling")
    void ScalePopulation(int32 NewAgentCount);

    UFUNCTION(BlueprintPure, Category = "NLT|Scaling")
    FNLTScaleMetrics GetCurrentMetrics() const { return CurrentMetrics; }

    UFUNCTION(BlueprintPure, Category = "NLT|Scaling")
    bool IsBenchmarking() const { return bIsBenchmarking; }

private:
    bool bIsBenchmarking = false;
    FNLTScaleMetrics CurrentMetrics;
    double BenchmarkStartTime = 0.0;

    void RecordMetrics();
};
