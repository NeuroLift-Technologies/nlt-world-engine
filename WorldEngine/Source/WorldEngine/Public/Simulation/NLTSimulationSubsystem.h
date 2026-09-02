#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTSimulationSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimulationTick, int32, SimulationTick);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimulationModeChanged, ESimulationMode, NewMode);

UCLASS()
class UNLTSimulationSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void StartSimulation();

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void StopSimulation();

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void PauseSimulation();

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void ResumeSimulation();

    UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
    bool IsRunning() const { return bRunning && !bPaused; }

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void StepTick();

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void StepTicks(int32 Count);

    UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
    int32 GetCurrentTick() const { return SimulationTick; }

    UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
    float GetSimulationTimeMinutes() const { return SimulationTimeMinutes; }

    UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
    ESimulationMode GetMode() const { return Mode; }

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void SetMode(ESimulationMode NewMode);

    UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
    void SetSimulationRate(float NewRate) { SimulationRate = FMath::Max(0.0f, NewRate); }

    UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
    float GetSimulationRate() const { return SimulationRate; }

    FOnSimulationTick OnSimulationTick;
    FOnSimulationModeChanged OnSimulationModeChanged;

private:
    int32 SimulationTick = 0;
    float SimulationTimeMinutes = 0.0f;
    float TickDeltaTimeSeconds = 1.0f;
    float SimulationRate = 1.0f;
    int32 TicksPerMinute = 60;
    bool bRunning = false;
    bool bPaused = false;
    ESimulationMode Mode = ESimulationMode::Realtime;

    void ComputeDeltaTime();
};
