// NLTAvatarInteractor.h
#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "NLTAvatarInteractor.generated.h"

UCLASS()
class WORLDENGINE_API UNLTAvatarInteractor : public ULearningAgentsInteractor
{
    GENERATED_BODY()

public:
    UNLTAvatarInteractor();

    /** Specify observation schema. Called once during setup. */
    virtual void SpecifyAgentObservation_Implementation(
        FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
        ULearningAgentsObservationSchema* InObservationSchema) override;

    /** Gather observation data for a single agent. Called each tick. */
    virtual void GatherAgentObservation_Implementation(
        FLearningAgentsObservationObjectElement& OutObservationObjectElement,
        ULearningAgentsObservationObject* InObservationObject,
        const int32 AgentId) override;

    /** Specify action schema. Called once during setup. */
    virtual void SpecifyAgentAction_Implementation(
        FLearningAgentsActionSchemaElement& OutActionSchemaElement,
        ULearningAgentsActionSchema* InActionSchema) override;

    /** Perform action for a single agent. Called each tick after policy evaluation. */
    virtual void PerformAgentAction_Implementation(
        const ULearningAgentsActionObject* InActionObject,
        const FLearningAgentsActionObjectElement& InActionObjectElement,
        const int32 AgentId) override;
};
