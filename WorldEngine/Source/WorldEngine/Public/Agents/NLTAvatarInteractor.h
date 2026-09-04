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

    //~ Begin ULearningAgentsInteractor Interface
    virtual void SpecifyAgentObservation(
        FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
        ULearningAgentsObservationSchema* InObservationSchema);

    virtual void GatherAgentObservation(
        FLearningAgentsObservationObjectElement& OutObservationObjectElement,
        ULearningAgentsObservationObject* InObservationObject,
        const int32 AgentId);

    virtual void SpecifyAgentAction(
        FLearningAgentsActionSchemaElement& OutActionSchemaElement,
        ULearningAgentsActionSchema* InActionSchema);

    virtual void PerformAgentAction(
        const ULearningAgentsActionObject* InActionObject,
        const FLearningAgentsActionObjectElement& InActionObjectElement,
        const int32 AgentId);
    //~ End ULearningAgentsInteractor Interface
};
