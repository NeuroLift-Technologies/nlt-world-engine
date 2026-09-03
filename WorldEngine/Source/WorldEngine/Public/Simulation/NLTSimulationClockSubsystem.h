#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTSimulationClockSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTSimulationClock, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAuthoritativeTick, int32, Tick, double, WorldTimeSeconds);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClockRateChanged, float, NewRate);

/**
 * Authoritative simulation clock for environment-only mode.
 * Provides deterministic, fixed-timestep time advancement independent of render framerate.
 * Drives all environment subsystems (lighting, weather, room state) from a single time source.
 */
UCLASS()
class UNLTSimulationClockSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Advance the clock by one fixed tick. Call from sim loop, not Tick(). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void AdvanceTick();

	/** Advance the clock by N fixed ticks (batch stepping for headless/deterministic modes). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void AdvanceTicks(int32 Count);

	/** Current authoritative tick index (monotonically increasing). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	int32 GetCurrentTick() const { return CurrentTick; }

	/** Total simulated time in seconds since clock start. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	double GetWorldTimeSeconds() const { return WorldTimeSeconds; }

	/** Simulated time-of-day in hours [0, 24). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	float GetTimeOfDayHours() const;

	/** Duration of one fixed tick in seconds. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	float GetFixedTimestepSeconds() const { return FixedTimestepSeconds; }

	/** Set the fixed timestep (seconds per tick). Affects all downstream subsystems. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void SetFixedTimestepSeconds(float InSeconds);

	/** Time scale multiplier (1.0 = realtime, 0.0 = paused, >1.0 = fast-forward). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	float GetTimeScale() const { return TimeScale; }

	/** Set time scale. 0.0 pauses the clock. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void SetTimeScale(float NewScale);

	/** Whether the clock is currently advancing. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	bool IsRunning() const { return bRunning; }

	/** Start the clock. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void Start();

	/** Stop the clock (resets running state but preserves tick count). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void Stop();

	/** Reset clock to tick 0, time 0. Does not change timestep or scale. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void ResetClock();

	/** Set initial time-of-day in hours [0, 24). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void SetInitialTimeOfDay(float Hours);

	/** Get the initial time-of-day used for day-rollover math. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	float GetInitialTimeOfDay() const { return InitialTimeOfDayHours; }

	/** Number of simulated days elapsed since clock start. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation|Clock")
	int32 GetDaysElapsed() const { return DaysElapsed; }

	/** Serialize clock state for persistence. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	void SerializeClockState(TArray<uint8>& OutData) const;

	/** Deserialize and restore clock state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Clock")
	bool DeserializeClockState(const TArray<uint8>& InData);

	FOnAuthoritativeTick OnAuthoritativeTick;
	FOnClockRateChanged OnClockRateChanged;

private:
	int32 CurrentTick = 0;
	double WorldTimeSeconds = 0.0;
	float FixedTimestepSeconds = 1.0f / 60.0f;
	float TimeScale = 1.0f;
	float InitialTimeOfDayHours = 12.0f;
	int32 DaysElapsed = 0;
	bool bRunning = false;
};
