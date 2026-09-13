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

    // Begin ULearningAgentsInteractor Interface
    virtual void SpecifyAgentObservation_Implementation(
        FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
        ULearningAgentsObservationSchema* InObservationSchema) override;

    virtual void GatherAgentObservation_Implementation(
        FLearningAgentsObservationObjectElement& OutObservationObjectElement,
        ULearningAgentsObservationObject* InObservationObject,
        const int32 AgentId) override;

    virtual void SpecifyAgentAction_Implementation(
        FLearningAgentsActionSchemaElement& OutActionSchemaElement,
        ULearningAgentsActionSchema* InActionSchema) override;

    virtual void PerformAgentAction_Implementation(
        const ULearningAgentsActionObject* InActionObject,
        const FLearningAgentsActionObjectElement& InActionObjectElement,
        const int32 AgentId) override;
    // End ULearningAgentsInteractor Interface
};
