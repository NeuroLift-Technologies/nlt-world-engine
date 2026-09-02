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
	ModeChanged         UMETA(DisplayName = "ModeChanged")
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

	FOnSimulationEvent OnSimulationEvent;

private:
	static constexpr int32 RingBufferCapacity = 256;
	TArray<FNLTSimulationEvent> EventRingBuffer;
	int32 RingBufferWriteHead = 0;
};