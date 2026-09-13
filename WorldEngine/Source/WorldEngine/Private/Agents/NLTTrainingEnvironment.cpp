// NLTTrainingEnvironment.cpp
#include "Agents/NLTTrainingEnvironment.h"
#include "LearningAgentsManager.h"
#include "Agents/AvatarCharacter.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"

UNLTTrainingEnvironment::UNLTTrainingEnvironment()
{
}

void UNLTTrainingEnvironment::OnAgentsAdded_Implementation(const TArray<int32>& AgentIds)
{
    Super::OnAgentsAdded_Implementation(AgentIds);

    // Capture the initial transform of each agent when it is first registered.
    // This is used by ResetAgentEpisode_Implementation to restore the complete
    // episode state so truncated episodes don't inherit stale position/velocity.
    for (int32 AgentId : AgentIds)
    {
        if (AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(GetAgent(AgentId)))
        {
            InitialAgentTransforms.Add(AgentId, Avatar->GetActorTransform());
        }
    }
}

void UNLTTrainingEnvironment::ResetAgentEpisode_Implementation(const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar)
    {
        return;
    }

    // Reset cognitive state to defaults
    if (Avatar->CognitiveState)
    {
        Avatar->CognitiveState->ResetCognitiveState();
    }

    // Restore the complete stored initial episode state: transform, velocity,
    // and controller movement request.
    if (InitialAgentTransforms.Contains(AgentId))
    {
        const FTransform InitialTransform = InitialAgentTransforms[AgentId];
        Avatar->SetActorTransform(InitialTransform, /*bSweep=*/false, nullptr, ETeleportType::TeleportPhysics);

        if (UCharacterMovementComponent* MoveComp = Avatar->GetCharacterMovement())
        {
            MoveComp->Velocity = FVector::ZeroVector;
            MoveComp->StopMovementImmediately();
        }

        if (AAIController* AIController = Cast<AAIController>(Avatar->GetController()))
        {
            AIController->StopMovement();
        }
    }
}

void UNLTTrainingEnvironment::GatherAgentReward_Implementation(float& OutReward, const int32 AgentId)
{
    UObject* Agent = GetAgent(AgentId);
    AAvatarCharacter* Avatar = Cast<AAvatarCharacter>(Agent);
    if (!Avatar)
    {
        OutReward = 0.0f;
        return;
    }

    ULTCognitiveStateComponent* Cognitive = Avatar->FindComponentByClass<ULTCognitiveStateComponent>();
    if (!Cognitive)
    {
        OutReward = 0.0f;
        return;
    }

    OutReward = 0.0f;
    OutReward += Cognitive->Independence * 1.0f;
    OutReward -= Cognitive->Burnout * 1.0f;
    OutReward -= Cognitive->Stress * 0.5f;
    OutReward += Cognitive->Focus * 0.3f;
    OutReward += Cognitive->SuccessRate * 0.5f;
}

void UNLTTrainingEnvironment::GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId)
{
    OutCompletion = ELearningAgentsCompletion::Running;
}
