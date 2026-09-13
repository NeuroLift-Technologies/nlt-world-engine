// NLTAideInteractor.cpp
#include "Agents/NLTAideInteractor.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "LearningAgentsManager.h"

UNLTAideInteractor::UNLTAideInteractor()
{
}

void UNLTAideInteractor::SpecifyAgentObservation_Implementation(
    FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
    ULearningAgentsObservationSchema* InObservationSchema)
{
    TMap<FName, FLearningAgentsObservationSchemaElement> ObsElements;
    ObsElements.Add(TEXT("AvatarState"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 13));
    ObsElements.Add(TEXT("AideState"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 7));
    
    OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObsElements);
}

void UNLTAideInteractor::GatherAgentObservation_Implementation(
    FLearningAgentsObservationObjectElement& OutObservationObjectElement,
    ULearningAgentsObservationObject* InObservationObject,
    const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    
    TMap<FName, FLearningAgentsObservationObjectElement> ObsElements;
    ObsElements.Add(TEXT("AvatarState"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
        InObservationObject, {0.5f, 0.2f, 0.15f, 0.05f, 0.2f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f}, true, TEXT("AvatarState")));
    ObsElements.Add(TEXT("AideState"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
        InObservationObject, {0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f}, true, TEXT("AideState")));

    OutObservationObjectElement = ULearningAgentsObservations::MakeStructObservation(
        InObservationObject, ObsElements);
}

void UNLTAideInteractor::SpecifyAgentAction_Implementation(
    FLearningAgentsActionSchemaElement& OutActionSchemaElement,
    ULearningAgentsActionSchema* InActionSchema)
{
    OutActionSchemaElement = ULearningAgentsActions::SpecifyExclusiveDiscreteAction(InActionSchema, 10, {});
}

void UNLTAideInteractor::PerformAgentAction_Implementation(
    const ULearningAgentsActionObject* InActionObject,
    const FLearningAgentsActionObjectElement& InActionObjectElement,
    const int32 AgentId)
{
    int32 StrategyChoice = 0;
    ULearningAgentsActions::GetExclusiveDiscreteAction(
        StrategyChoice, InActionObject, InActionObjectElement, true, TEXT("Strategy"));
}

void UNLTAideInteractor::SetPairMapping(const TMap<int32, int32>& InPairMap)
{
    PairMap = InPairMap;
}
