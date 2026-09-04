// NLTAideInteractor.cpp
#include "Agents/NLTAideInteractor.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "LearningAgentsManager.h"
#include "Core/NLTFusionCore.h"

UNLTAideInteractor::UNLTAideInteractor()
{
}

void UNLTAideInteractor::SetPairMapping(const TMap<int32, int32>& InPairMap)
{
    PairMap = InPairMap;
}

void UNLTAideInteractor::SpecifyAgentObservation(
    FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
    ULearningAgentsObservationSchema* InObservationSchema)
{
    TMap<FName, FLearningAgentsObservationSchemaElement> ObsElements;
    ObsElements.Add(TEXT("Position"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 3));
    ObsElements.Add(TEXT("Velocity"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 3));
    ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 7));
    
    OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObsElements);
}

void UNLTAideInteractor::GatherAgentObservation(
    FLearningAgentsObservationObjectElement& OutObservationObjectElement,
    ULearningAgentsObservationObject* InObservationObject,
    const int32 AgentId)
{
    // Aide observes the PAIRED Avatar's state
    const int32* AvatarAgentIdPtr = PairMap.Find(AgentId);
    if (!AvatarAgentIdPtr) return;
    
    int32 AvatarAgentId = *AvatarAgentIdPtr;
    UObject* Agent = GetAgent(AvatarAgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar) return;

    FVector Position = Avatar->GetActorLocation();
    FVector Velocity = Avatar->GetVelocity();

    TMap<FName, FLearningAgentsObservationObjectElement> ObsElements;
    
    ObsElements.Add(TEXT("Position"), ULearningAgentsObservations::MakeLocationObservation(
        InObservationObject, Position, FTransform::Identity, true, TEXT("AideObsPosition")));
    
    TArray<float> VelValues = {Velocity.X, Velocity.Y, Velocity.Z};
    ObsElements.Add(TEXT("Velocity"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
        InObservationObject, VelValues, true, TEXT("AideObsVelocity")));
    
    ULTCognitiveStateComponent* Cognitive = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
    if (Cognitive)
    {
        TArray<float> CognitiveValues = Cognitive->GetObservationValues();
        ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
            InObservationObject, CognitiveValues, true, TEXT("AideObsCognitive")));
    }
    else
    {
        TArray<float> CognitiveValues = {0.5f, 0.2f, 0.15f, 0.05f, 0.2f, 0.0f, 0.5f};
        ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
            InObservationObject, CognitiveValues, true, TEXT("AideObsCognitive")));
    }

    OutObservationObjectElement = ULearningAgentsObservations::MakeStructObservation(
        InObservationObject, ObsElements);
}

void UNLTAideInteractor::SpecifyAgentAction(
    FLearningAgentsActionSchemaElement& OutActionSchemaElement,
    ULearningAgentsActionSchema* InActionSchema)
{
    OutActionSchemaElement = ULearningAgentsActions::SpecifyExclusiveDiscreteAction(
        InActionSchema, 11, {});
}

void UNLTAideInteractor::PerformAgentAction(
    const ULearningAgentsActionObject* InActionObject,
    const FLearningAgentsActionObjectElement& InActionObjectElement,
    const int32 AgentId)
{
    int32 ActionChoice = 0;
    ULearningAgentsActions::GetExclusiveDiscreteAction(
        ActionChoice, InActionObject, InActionObjectElement, true, TEXT("DiscreteExclusiveAction"));

    // Apply coaching effect to the PAIRED Avatar
    const int32* AvatarAgentIdPtr = PairMap.Find(AgentId);
    if (!AvatarAgentIdPtr) return;
    
    int32 AvatarAgentId = *AvatarAgentIdPtr;
    UObject* Agent = GetAgent(AvatarAgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar) return;

    ULTCognitiveStateComponent* Cognitive = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
    if (Cognitive)
    {
        Cognitive->ApplyCoachingEffect(ActionChoice);
    }

    UE_LOG(LogNLTFusion, Log, TEXT("Aide Agent %d coached Avatar %d with strategy %d"), AgentId, AvatarAgentId, ActionChoice);
}
