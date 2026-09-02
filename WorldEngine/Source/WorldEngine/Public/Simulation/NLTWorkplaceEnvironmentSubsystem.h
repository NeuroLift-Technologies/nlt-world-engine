#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Core/NLTSimulationState.h"
#include "Core/NLTEventBus.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTWorkplaceEnvironmentSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTWorkplaceEnvironment, Log, All);

class UNLTSimulationClockSubsystem;
class UNLTDeterministicSeedSubsystem;
class UNLTRoomStateSubsystem;

/**
 * Environment-only simulation driver for Workplace_Level.
 *
 * Ties the authoritative clock (UNLTSimulationClockSubsystem), the event bus
 * (UNLTEventBus, environment event channels), the deterministic seed system
 * (UNLTDeterministicSeedSubsystem) and room-state persistence
 * (UNLTRoomStateSubsystem) together into one coherent, reproducible
 * environment pass.
 *
 * Deliberately agent-free: this subsystem never spawns or drives Avatar/Aide/
 * Mass entities. It only advances the environment (time-of-day, lighting,
 * room state) from a single master "room seed" so the same seed always
 * produces the same environment events and room states.
 *
 * Usage (from the Workplace_Level GameMode or level Blueprint):
 *   - ConfigureEnvironment(ScenarioId, RoomSeed, bStartSimulation) to seed
 *     everything and register the workplace rooms.
 *   - Each frame while running, call StepEnvironmentSimulation(1) (batch the
 *     count for headless / -game -nullrhi runs) to advance the clock one fixed
 *     tick and emit environment events.
 */
UCLASS()
class UNLTWorkplaceEnvironmentSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/**
	 * (Re)configure the workplace environment from a master room seed.
	 * Derives all category streams, registers the standard workplace rooms
	 * with deterministic initial state, applies seeded micro-variation, and
	 * optionally starts the clock.
	 */
	UFUNCTION(BlueprintCallable, Category = "NLT|Environment|Workplace")
	void ConfigureEnvironment(FName ScenarioId, int32 RoomSeed, bool bStartSimulation);

	/** Start advancing the authoritative clock. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Environment|Workplace")
	void StartEnvironmentSimulation();

	/** Stop advancing the clock (preserves state for persistence). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Environment|Workplace")
	void StopEnvironmentSimulation();

	/** Whether the clock is currently running. */
	UFUNCTION(BlueprintPure, Category = "NLT|Environment|Workplace")
	bool IsRunning() const { return bRunning; }

	/**
	 * Advance the environment by NumTicks fixed clicks. Each tick advances the
	 * clock; the OnAuthoritativeTick handler publishes time-of-day and
	 * periodically refreshes room detail, raising env events. Call once per
	 * frame with 1 (game), or batch N for headless determinism runs.
	 */
	UFUNCTION(BlueprintCallable, Category = "NLT|Environment|Workplace")
	void StepEnvironmentSimulation(int32 NumTicks);

	/** Number of fixed ticks between per-room detail refreshes (default 60). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NLT|Environment|Workplace")
	int32 DetailRefreshIntervalTicks = 60;

	/** Full environment persistence: clock + seed streams + all room states. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Environment|Workplace")
	void SerializeEnvironmentState(TArray<uint8>& OutData) const;

	/** Restore a previously serialized environment state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|Environment|Workplace")
	bool DeserializeEnvironmentState(const TArray<uint8>& InData);

	/** Get the active master room seed. */
	UFUNCTION(BlueprintPure, Category = "NLT|Environment|Workplace")
	int32 GetMasterSeed() const { return MasterSeed; }

	/** Get the active scenario id (may be NAME_None for a bare environment). */
	UFUNCTION(BlueprintPure, Category = "NLT|Environment|Workplace")
	FName GetScenarioId() const { return ActiveScenarioId; }

private:
	/** React to each authoritative clock tick: publish time-of-day + refresh rooms. */
	UFUNCTION()
	void HandleAuthoritativeTick(int32 Tick, double WorldTimeSeconds);

	/** Register the standard Workplace_Level rooms with deterministic initial state. */
	void RegisterWorkplaceRooms(int32 Tick);

	/** Refresh every room's lighting/noise a little, raising env events. */
	void RefreshRooms(int32 Tick);

	/** Publish EnvTimeOfDayChanged / EnvLightingChanged when the hour rolls over. */
	void PublishTimeOfDay(int32 Tick);

	/** Write an int32 to a byte buffer (little-endian, length-prefixed framing). */
	static void WriteInt32(TArray<uint8>& OutData, int32& Offset, int32 Value);
	/** Read an int32 from a byte buffer. */
	static int32 ReadInt32(const TArray<uint8>& InData, int32& Offset);
	/** Append a length-prefixed byte blob (int32 size + payload). */
	static void AppendBlob(TArray<uint8>& OutData, int32& Offset, const TArray<uint8>& Blob);
	/** Read a length-prefixed byte blob, returning false if truncated. */
	static bool ReadBlob(const TArray<uint8>& InData, int32& Offset, TArray<uint8>& OutBlob);

	TObjectPtr<UNLTSimulationClockSubsystem> Clock = nullptr;
	TObjectPtr<UNLTEventBus> EventBus = nullptr;
	TObjectPtr<UNLTDeterministicSeedSubsystem> Seed = nullptr;
	TObjectPtr<UNLTRoomStateSubsystem> RoomState = nullptr;

	FName ActiveScenarioId = NAME_None;
	int32 MasterSeed = 0;
	bool bRunning = false;
	bool bConfigured = false;

	int32 LastPublishedTimeOfDayHour = -1;
	int32 TicksSinceLastRefresh = 0;
};
