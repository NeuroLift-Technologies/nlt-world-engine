#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTEventBus.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTEventBus, Log, All);

UENUM(BlueprintType)
enum class ENLTSimulationEventType : uint8
{
	None                UMETA(DisplayName = "None"),
	Tick                UMETA(DisplayName = "Tick"),
	AgentCreated        UMETA(DisplayName = "AgentCreated"),
	AgentDestroyed      UMETA(DisplayName = "AgentDestroyed"),
	AgentSpawned        UMETA(DisplayName = "AgentSpawned"),
	AgentDespawned      UMETA(DisplayName = "AgentDespawned"),
	AgentMoved          UMETA(DisplayName = "AgentMoved"),
	NeedChanged         UMETA(DisplayName = "NeedChanged"),
	IntentChanged       UMETA(DisplayName = "IntentChanged"),
	EmotionalShift      UMETA(DisplayName = "EmotionalShift"),
	FusionStart         UMETA(DisplayName = "FusionStart"),
	FusionComplete      UMETA(DisplayName = "FusionComplete"),
	FusionFail          UMETA(DisplayName = "FusionFail"),
	StressSpike         UMETA(DisplayName = "StressSpike"),
	BurnoutDetected     UMETA(DisplayName = "BurnoutDetected"),
	Breakthrough        UMETA(DisplayName = "Breakthrough"),
	Distraction         UMETA(DisplayName = "Distraction"),
	SocialInteraction   UMETA(DisplayName = "SocialInteraction"),
	TaskComplete        UMETA(DisplayName = "TaskComplete"),
	SimulationReset     UMETA(DisplayName = "SimulationReset"),
	ModeChanged         UMETA(DisplayName = "ModeChanged"),
	// Environment events (environment-only mode)
	EnvWeatherChanged   UMETA(DisplayName = "EnvWeatherChanged"),
	EnvLightingChanged  UMETA(DisplayName = "EnvLightingChanged"),
	EnvTimeOfDayChanged UMETA(DisplayName = "EnvTimeOfDayChanged"),
	EnvRoomStateChanged UMETA(DisplayName = "EnvRoomStateChanged"),
	EnvAmbientSound     UMETA(DisplayName = "EnvAmbientSound"),
	EnvParticleEffect   UMETA(DisplayName = "EnvParticleEffect"),
	EnvFogChanged       UMETA(DisplayName = "EnvFogChanged"),
	EnvWindChanged      UMETA(DisplayName = "EnvWindChanged")
};

USTRUCT(BlueprintType)
struct FNLTSimulationEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "NLT|Simulation")
	ENLTSimulationEventType EventType = ENLTSimulationEventType::None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|Simulation")
	int32 Tick = 0;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|Simulation")
	FName AgentId = NAME_None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|Simulation")
	FString Description;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|Simulation")
	FName TargetId = NAME_None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|Simulation")
	float Value = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSimulationEvent, const FNLTSimulationEvent&, Event);

UCLASS()
class UNLTEventBus : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	void RaiseEvent(const FNLTSimulationEvent& Event);

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	void RaiseSimpleEvent(ENLTSimulationEventType EventType, int32 Tick, FName AgentId, FString Description, FName TargetId = NAME_None, float Value = 0.0f);

	/** Raise an environment event (no agent, environment-only mode). */
	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation|Environment")
	void RaiseEnvironmentEvent(ENLTSimulationEventType EventType, int32 Tick, FName RoomId, FString Description, float Value = 0.0f);

	/** Get the most recent N events from the ring buffer (newest first). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	void GetRecentEvents(int32 Count, TArray<FNLTSimulationEvent>& OutEvents) const;

	/** Get all events of a specific type from the ring buffer. */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	void GetEventsByType(ENLTSimulationEventType EventType, TArray<FNLTSimulationEvent>& OutEvents) const;

	/** Get the total number of events ever raised (including overwritten ones). */
	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	int32 GetTotalEventCount() const { return TotalEventCount; }

	FOnSimulationEvent OnSimulationEvent;
	FOnSimulationEvent OnEnvironmentEvent;

private:
	static constexpr int32 RingBufferCapacity = 256;
	TArray<FNLTSimulationEvent> EventRingBuffer;
	int32 RingBufferWriteHead = 0;
	int32 TotalEventCount = 0;
};