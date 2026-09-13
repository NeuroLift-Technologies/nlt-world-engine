// NLTAvatarInteractor.cpp
#include "Agents/NLTAvatarInteractor.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "LearningAgentsObservations.h"
#include "LearningAgentsActions.h"
#include "LearningAgentsManager.h"

UNLTAvatarInteractor::UNLTAvatarInteractor()
{
}

void UNLTAvatarInteractor::SpecifyAgentObservation_Implementation(
    FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
    ULearningAgentsObservationSchema* InObservationSchema)
{
    TMap<FName, FLearningAgentsObservationSchemaElement> ObsElements;
    ObsElements.Add(TEXT("Position"), ULearningAgentsObservations::SpecifyLocationObservation(InObservationSchema));
    ObsElements.Add(TEXT("Velocity"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 3));
    ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 7));
    OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObsElements);
}

void UNLTAvatarInteractor::GatherAgentObservation_Implementation(
    FLearningAgentsObservationObjectElement& OutObservationObjectElement,
    ULearningAgentsObservationObject* InObservationObject,
    const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar) return;

    FVector Position = Avatar->GetActorLocation();
    FVector Velocity = Avatar->GetVelocity();

    TArray<float> VelValues = {Velocity.X, Velocity.Y, Velocity.Z};
    TArray<float> CognitiveValues = {0.5f, 0.2f, 0.15f, 0.05f, 0.2f, 0.0f, 0.5f};

    ULTCognitiveStateComponent* CognitiveState = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
    if (CognitiveState)
    {
        CognitiveValues = CognitiveState->GetObservationValues();
    }

    TMap<FName, FLearningAgentsObservationObjectElement> ObsElements;
    ObsElements.Add(TEXT("Position"), ULearningAgentsObservations::MakeLocationObservation(InObservationObject, Position, FTransform::Identity, true));
    ObsElements.Add(TEXT("Velocity"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(InObservationObject, VelValues, true));
    ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(InObservationObject, CognitiveValues, true));
    OutObservationObjectElement = ULearningAgentsObservations::MakeStructObservation(InObservationObject, ObsElements);
}

void UNLTAvatarInteractor::SpecifyAgentAction_Implementation(
    FLearningAgentsActionSchemaElement& OutActionSchemaElement,
    ULearningAgentsActionSchema* InActionSchema)
{
    TMap<FName, FLearningAgentsActionSchemaElement> ActionElements;
    ActionElements.Add(TEXT("MoveDirection"), ULearningAgentsActions::SpecifyContinuousAction(InActionSchema, 3));
    ActionElements.Add(TEXT("Interaction"), ULearningAgentsActions::SpecifyExclusiveDiscreteAction(InActionSchema, 4, {}));
    OutActionSchemaElement = ULearningAgentsActions::SpecifyStructAction(InActionSchema, ActionElements);
}

void UNLTAvatarInteractor::PerformAgentAction_Implementation(
    const ULearningAgentsActionObject* InActionObject,
    const FLearningAgentsActionObjectElement& InActionObjectElement,
    const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar) return;

    AAvatarAIController* AIController = Cast<AAvatarAIController>(Avatar->GetController());
    if (!AIController) return;

    FLearningAgentsActionObjectElement MoveDirectionElement;
    ULearningAgentsActions::GetStructActionElement(MoveDirectionElement, InActionObject, InActionObjectElement, TEXT("MoveDirection"), true);

    TArray<float> MoveDirectionValues;
    ULearningAgentsActions::GetContinuousAction(MoveDirectionValues, InActionObject, MoveDirectionElement, true);

    if (MoveDirectionValues.Num() >= 3)
    {
        FVector MoveDirection(MoveDirectionValues[0], MoveDirectionValues[1], MoveDirectionValues[2]);
        if (!MoveDirection.IsNearlyZero())
        {
            FVector TargetLocation = Avatar->GetActorLocation() + MoveDirection * 500.0f;
            AIController->MoveToLocation(TargetLocation);
        }
    }

    FLearningAgentsActionObjectElement InteractionElement;
    ULearningAgentsActions::GetStructActionElement(InteractionElement, InActionObject, InActionObjectElement, TEXT("Interaction"), true);

    int32 InteractionChoice = 0;
    ULearningAgentsActions::GetExclusiveDiscreteAction(InteractionChoice, InActionObject, InteractionElement, true);
}
