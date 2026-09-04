// NLTAideInteractor.h
#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "NLTAideInteractor.generated.h"

UCLASS()
class WORLDENGINE_API UNLTAideInteractor : public ULearningAgentsInteractor
{
    GENERATED_BODY()

public:
    UNLTAideInteractor();

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

    // Pair mapping: Aide AgentId -> Avatar AgentId
    void SetPairMapping(const TMap<int32, int32>& InPairMap);

private:
    TMap<int32, int32> PairMap; // AideId -> AvatarId
};
