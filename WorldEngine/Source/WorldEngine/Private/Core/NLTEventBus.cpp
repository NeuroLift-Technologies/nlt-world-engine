#include "Core/NLTEventBus.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTEventBus);

void UNLTEventBus::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogNLTEventBus, Log, TEXT("Event bus initialized"));

	EventRingBuffer.SetNumZeroed(RingBufferCapacity);
	RingBufferWriteHead = 0;
}

void UNLTEventBus::Deinitialize()
{
	UE_LOG(LogNLTEventBus, Log, TEXT("Event bus shutdown"));
	EventRingBuffer.Empty();
	Super::Deinitialize();
}

void UNLTEventBus::RaiseEvent(const FNLTSimulationEvent& Event)
{
	if (EventRingBuffer.Num() != RingBufferCapacity)
	{
		EventRingBuffer.SetNumZeroed(RingBufferCapacity);
	}

	EventRingBuffer[RingBufferWriteHead] = Event;
	RingBufferWriteHead = (RingBufferWriteHead + 1) % RingBufferCapacity;

	UE_LOG(LogNLTEventBus, Verbose, TEXT("Event raised: %s for agent %s at tick %d"),
		*UEnum::GetValueAsString(Event.EventType),
		*Event.AgentId.ToString(),
		Event.Tick);

	OnSimulationEvent.Broadcast(Event);
}

void UNLTEventBus::RaiseSimpleEvent(ENLTSimulationEventType EventType, int32 Tick, FName AgentId, FString Description, FName TargetId, float Value)
{
	FNLTSimulationEvent NewEvent;
	NewEvent.EventType = EventType;
	NewEvent.Tick = Tick;
	NewEvent.AgentId = AgentId;
	NewEvent.Description = MoveTemp(Description);
	NewEvent.TargetId = TargetId;
	NewEvent.Value = Value;

	RaiseEvent(NewEvent);
}