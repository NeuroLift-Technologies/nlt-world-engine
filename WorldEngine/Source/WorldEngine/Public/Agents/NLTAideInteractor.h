// NLTAideInteractor.h
#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "NLTAideInteractor.generated.h"

/**
 * Aide interactor for Learning Agents.
 * Observes the paired Avatar's state, outputs coaching strategy (0-9 = 10 strategies).
 */
UCLASS()
class WORLDENGINE_API UNLTAideInteractor : public ULearningAgentsInteractor
{
    GENERATED_BODY()

public:
    UNLTAideInteractor();

    /** Specify observation schema. Called once during setup. */
    virtual void SpecifyAgentObservation(
        FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
        ULearningAgentsObservationSchema* InObservationSchema);

    /** Gather observation data for a single agent. Called each tick. */
    virtual void GatherAgentObservation(
        FLearningAgentsObservationObjectElement& OutObservationObjectElement,
        ULearningAgentsObservationObject* InObservationObject,
        const int32 AgentId);

    /** Specify action schema. Called once during setup. */
    virtual void SpecifyAgentAction(
        FLearningAgentsActionSchemaElement& OutActionSchemaElement,
        ULearningAgentsActionSchema* InActionSchema);

    /** Perform action for a single agent. Called each tick after policy evaluation. */
    virtual void PerformAgentAction(
        const ULearningAgentsActionObject* InActionObject,
        const FLearningAgentsActionObjectElement& InActionObjectElement,
        const int32 AgentId);

    /** Set pair mapping: Aide AgentId -> Avatar AgentId */
    void SetPairMapping(const TMap<int32, int32>& InPairMap);

private:
    TMap<int32, int32> PairMap;
};
