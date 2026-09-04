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

void UNLTAvatarInteractor::SpecifyAgentObservation(
    FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
    ULearningAgentsObservationSchema* InObservationSchema)
{
    // Struct observation: position (3 floats), velocity (3 floats), cognitive (7 floats)
    TMap<FName, FLearningAgentsObservationSchemaElement> ObsElements;
    ObsElements.Add(TEXT("Position"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 3));
    ObsElements.Add(TEXT("Velocity"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 3));
    ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::SpecifyContinuousObservation(InObservationSchema, 7));
    
    OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ObsElements);
}

void UNLTAvatarInteractor::GatherAgentObservation(
    FLearningAgentsObservationObjectElement& OutObservationObjectElement,
    ULearningAgentsObservationObject* InObservationObject,
    const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar) return;

    FVector Position = Avatar->GetActorLocation();
    FVector Velocity = Avatar->GetVelocity();

    // Build struct observation
    TMap<FName, FLearningAgentsObservationObjectElement> ObsElements;
    
    // Position
    ObsElements.Add(TEXT("Position"), ULearningAgentsObservations::MakeLocationObservation(
        InObservationObject, Position, FTransform::Identity, true, TEXT("AvatarPosition")));
    
    // Velocity (as a vector of 3 floats)
    TArray<float> VelValues = {Velocity.X, Velocity.Y, Velocity.Z};
    ObsElements.Add(TEXT("Velocity"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
        InObservationObject, VelValues, true, TEXT("AvatarVelocity")));
    
    // Cognitive state from LTCognitiveStateComponent
    ULTCognitiveStateComponent* Cognitive = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
    if (Cognitive)
    {
        TArray<float> CognitiveValues = Cognitive->GetObservationValues();
        ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
            InObservationObject, CognitiveValues, true, TEXT("AvatarCognitive")));
    }
    else
    {
        // Fallback if no cognitive component
        TArray<float> CognitiveValues = {0.5f, 0.2f, 0.15f, 0.05f, 0.2f, 0.0f, 0.5f};
        ObsElements.Add(TEXT("Cognitive"), ULearningAgentsObservations::MakeContinuousObservationFromArrayView(
            InObservationObject, CognitiveValues, true, TEXT("AvatarCognitive")));
    }

    OutObservationObjectElement = ULearningAgentsObservations::MakeStructObservation(
        InObservationObject, ObsElements);
}

void UNLTAvatarInteractor::SpecifyAgentAction(
    FLearningAgentsActionSchemaElement& OutActionSchemaElement,
    ULearningAgentsActionSchema* InActionSchema)
{
    // Struct action: move direction (3 continuous) + interaction type (discrete)
    TMap<FName, FLearningAgentsActionSchemaElement> ActionElements;
    
    // Move direction: 3 continuous floats (X, Y, Z direction to move)
    ActionElements.Add(TEXT("MoveDirection"), 
        ULearningAgentsActions::SpecifyContinuousAction(InActionSchema, 3));
    
    // Interaction: discrete exclusive (0=None, 1=Work, 2=Rest, 3=Interact)
    ActionElements.Add(TEXT("Interaction"),
        ULearningAgentsActions::SpecifyExclusiveDiscreteAction(InActionSchema, 4, {}));

    OutActionSchemaElement = ULearningAgentsActions::SpecifyStructAction(InActionSchema, ActionElements);
}

void UNLTAvatarInteractor::PerformAgentAction(
    const ULearningAgentsActionObject* InActionObject,
    const FLearningAgentsActionObjectElement& InActionObjectElement,
    const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar) return;

    AAvatarAIController* AIController = Cast<AAvatarAIController>(Avatar->GetController());
    if (!AIController) return;

    // Disable wandering when LA performs an action
    AIController->SetLearningAgentsActive(true);

    // Get move direction from the struct action
    TArray<float> MoveDirectionValues;
    ULearningAgentsActions::GetContinuousActionToArrayView(
        MoveDirectionValues, InActionObject, InActionObjectElement, true, TEXT("ContinuousAction"));

    if (MoveDirectionValues.Num() >= 3)
    {
        FVector MoveDirection(MoveDirectionValues[0], MoveDirectionValues[1], MoveDirectionValues[2]);
        if (!MoveDirection.IsNearlyZero())
        {
            FVector TargetLocation = Avatar->GetActorLocation() + MoveDirection * 500.0f;
            AIController->MoveToLocation(TargetLocation);
        }
    }
}
