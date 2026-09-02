#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Core/NLTSimulationState.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTSimulationStateSubsystem.generated.h"

UCLASS()
class UNLTSimulationStateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	const FNLTSimulationState& GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	FNLTSimulationState& GetMutableState() { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	void ResetState();

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	FNLTSimulationState CreateSnapshot() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	void RestoreFromSnapshot(const FNLTSimulationState& Snapshot);

	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	const FNLTRandomStream& GetRNGConst() const { return RNG; }

	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	FNLTRandomStream& GetRNG() { return RNG; }

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	void SetSeed(int32 NewSeed);

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	void SetAgentState(const FNLTAgentState& AgentState);

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	bool GetAgentState(FName AgentId, FNLTAgentState& OutAgentState) const;

	UFUNCTION(BlueprintCallable, Category = "NLT|Simulation")
	bool RemoveAgentState(FName AgentId);

	UFUNCTION(BlueprintPure, Category = "NLT|Simulation")
	const TArray<FNLTAgentState>& GetAllAgentStates() const { return CurrentState.Agents; }

private:
	FNLTSimulationState CurrentState;
	FNLTRandomStream RNG;
};