#include "Simulation/NLTSimulationSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogNLTSimulation, Log, All);

void UNLTSimulationSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogNLTSimulation, Log, TEXT("Simulation subsystem initialized"));
}

void UNLTSimulationSubsystem::Deinitialize()
{
    StopSimulation();
    Super::Deinitialize();
}

void UNLTSimulationSubsystem::StartSimulation()
{
    if (bRunning && !bPaused) return;
    if (bPaused) { ResumeSimulation(); return; }
    bRunning = true;
    bPaused = false;
}

void UNLTSimulationSubsystem::StopSimulation()
{
    bRunning = false;
    bPaused = false;
}

void UNLTSimulationSubsystem::PauseSimulation()
{
    if (!bRunning) return;
    bPaused = true;
}

void UNLTSimulationSubsystem::ResumeSimulation()
{
    if (!bRunning || !bPaused) return;
    bPaused = false;
}

void UNLTSimulationSubsystem::StepTick()
{
    if (!bRunning || bPaused) return;
    SimulationTick++;
    // Advance simulation clock by one tick in minutes (e.g. 60 ticks/min => +1/60 min).
    SimulationTimeMinutes += (1.0f / FMath::Max(1, TicksPerMinute));
    OnSimulationTick.Broadcast(SimulationTick);
}

void UNLTSimulationSubsystem::StepTicks(int32 Count)
{
    for (int32 i = 0; i < Count; i++) StepTick();
}

void UNLTSimulationSubsystem::SetMode(ESimulationMode NewMode)
{
    if (Mode == NewMode) return;
    Mode = NewMode;
    switch (NewMode)
    {
    case ESimulationMode::Paused: PauseSimulation(); break;
    case ESimulationMode::Realtime: SetSimulationRate(1.0f); if (bPaused) ResumeSimulation(); break;
    case ESimulationMode::FastForward: SetSimulationRate(4.0f); if (bPaused) ResumeSimulation(); break;
    case ESimulationMode::SlowMotion: SetSimulationRate(0.25f); if (bPaused) ResumeSimulation(); break;
    case ESimulationMode::Headless: SetSimulationRate(0.0f); break;
    case ESimulationMode::Replay: SetSimulationRate(1.0f); break;
    case ESimulationMode::DeterministicTest: SetSimulationRate(0.0f); break;
    }
    OnSimulationModeChanged.Broadcast(NewMode);
}

void UNLTSimulationSubsystem::ComputeDeltaTime()
{
    TickDeltaTimeSeconds = (60.0f / FMath::Max(1, TicksPerMinute)) * SimulationRate;
}
