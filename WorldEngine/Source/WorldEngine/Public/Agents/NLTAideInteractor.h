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

    void SetPairMapping(const TMap<int32, int32>& InPairMap);

private:
    TMap<int32, int32> PairMap;
};
