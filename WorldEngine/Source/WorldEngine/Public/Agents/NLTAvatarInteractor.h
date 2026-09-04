// NLTAvatarInteractor.h
#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "NLTAvatarInteractor.generated.h"

/**
 * Avatar interactor for Learning Agents.
 * Observations: Position(3) + Velocity(3) + Cognitive(7) = 13 dims
 * Actions: MoveDirection(3 continuous) + Interaction(4 discrete)
 */
UCLASS()
class WORLDENGINE_API UNLTAvatarInteractor : public ULearningAgentsInteractor
{
    GENERATED_BODY()

public:
    UNLTAvatarInteractor();

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
};
