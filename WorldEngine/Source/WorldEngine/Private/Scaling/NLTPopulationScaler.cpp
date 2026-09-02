#include "Scaling/NLTPopulationScaler.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTPopulationScaler);

void UNLTPopulationScaler::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogNLTPopulationScaler, Log, TEXT("Population scaler initialized"));
}

void UNLTPopulationScaler::Deinitialize()
{
    Super::Deinitialize();
}

void UNLTPopulationScaler::StartBenchmark()
{
    bIsBenchmarking = true;
    BenchmarkStartTime = FPlatformTime::Seconds();
    UE_LOG(LogNLTPopulationScaler, Log, TEXT("Benchmark started"));
}

void UNLTPopulationScaler::StopBenchmark()
{
    bIsBenchmarking = false;
    UE_LOG(LogNLTPopulationScaler, Log, TEXT("Benchmark stopped"));
}

void UNLTPopulationScaler::ScalePopulation(int32 NewAgentCount)
{
    UE_LOG(LogNLTPopulationScaler, Log, TEXT("Scaling population to %d agents"), NewAgentCount);
    CurrentMetrics.AgentCount = NewAgentCount;
}

void UNLTPopulationScaler::RecordMetrics()
{
    CurrentMetrics.FrameTime = FApp::GetDeltaTime();
    CurrentMetrics.SimulationTickTime = FApp::GetDeltaTime();
}
