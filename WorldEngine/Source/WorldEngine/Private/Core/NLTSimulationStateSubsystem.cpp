#include "Core/NLTSimulationStateSubsystem.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogNLTSimulationState, Log, All);

void UNLTSimulationStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogNLTSimulationState, Log, TEXT("Simulation state subsystem initialized"));
	RNG = FNLTRandomStream(CurrentState.RandomSeed);
}

void UNLTSimulationStateSubsystem::Deinitialize()
{
	UE_LOG(LogNLTSimulationState, Log, TEXT("Simulation state subsystem shutdown"));
	Super::Deinitialize();
}

void UNLTSimulationStateSubsystem::ResetState()
{
	CurrentState.Agents.Empty();
	CurrentState.ActiveEvents.Empty();
	CurrentState.SimulationTick = 0;
	CurrentState.WorldTime = 0.0;
	RNG.Reset();
	UE_LOG(LogNLTSimulationState, Log, TEXT("Simulation state reset"));
}

void UNLTSimulationStateSubsystem::RestoreFromSnapshot(const FNLTSimulationState& Snapshot)
{
	CurrentState = Snapshot;
	RNG = FNLTRandomStream(CurrentState.RandomSeed);
	UE_LOG(LogNLTSimulationState, Log, TEXT("Simulation state restored from snapshot (tick %d)"), CurrentState.SimulationTick);
}

void UNLTSimulationStateSubsystem::SetSeed(int32 NewSeed)
{
	CurrentState.RandomSeed = NewSeed;
	RNG = FNLTRandomStream(NewSeed);
	UE_LOG(LogNLTSimulationState, Log, TEXT("Random seed set to %d"), NewSeed);
}

void UNLTSimulationStateSubsystem::SetAgentState(const FNLTAgentState& AgentState)
{
	for (FNLTAgentState& Existing : CurrentState.Agents)
	{
		if (Existing.AgentId == AgentState.AgentId)
		{
			Existing = AgentState;
			return;
		}
	}
	CurrentState.Agents.Add(AgentState);
}

bool UNLTSimulationStateSubsystem::GetAgentState(FName AgentId, FNLTAgentState& OutAgentState) const
{
	for (const FNLTAgentState& Existing : CurrentState.Agents)
	{
		if (Existing.AgentId == AgentId)
		{
			OutAgentState = Existing;
			return true;
		}
	}
	return false;
}

bool UNLTSimulationStateSubsystem::RemoveAgentState(FName AgentId)
{
	const int32 OriginalNum = CurrentState.Agents.Num();
	CurrentState.Agents.RemoveAll([AgentId](const FNLTAgentState& Agent) {
		return Agent.AgentId == AgentId;
	});
	return CurrentState.Agents.Num() < OriginalNum;
}