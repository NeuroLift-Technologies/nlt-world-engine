// NLTEpisodeManager.cpp
#include "Agents/NLTEpisodeManager.h"

UNLTEpisodeManager::UNLTEpisodeManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    MaxEpisodeSteps = 512;
    StepInterval = 0.1f;
    CurrentStep = 0;
    bEpisodeActive = false;
    StepTimer = 0.0f;
}

void UNLTEpisodeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bEpisodeActive) return;

    StepTimer += DeltaTime;
    if (StepTimer >= StepInterval)
    {
        StepTimer -= StepInterval;
        CurrentStep++;

        if (IsEpisodeComplete())
        {
            EndEpisode();
        }
    }
}

void UNLTEpisodeManager::StartEpisode()
{
    CurrentStep = 0;
    StepTimer = 0.0f;
    bEpisodeActive = true;
}

void UNLTEpisodeManager::EndEpisode()
{
    bEpisodeActive = false;
    OnEpisodeComplete.Broadcast();
}

void UNLTEpisodeManager::ResetEpisode()
{
    CurrentStep = 0;
    StepTimer = 0.0f;
}

bool UNLTEpisodeManager::IsEpisodeComplete() const
{
    return CurrentStep >= MaxEpisodeSteps;
}

void UNLTEpisodeManager::CheckCognitiveCompletion(float Independence, float Burnout)
{
    // Episode ends early if Avatar achieves high independence or burns out
    if (Independence >= 0.8f)
    {
        EndEpisode();  // Success!
    }
    else if (Burnout >= 0.9f)
    {
        EndEpisode();  // Failure
    }
}
