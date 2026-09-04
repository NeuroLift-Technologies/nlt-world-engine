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
    bEndEpisodeGuard = false;
}

void UNLTEpisodeManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bEpisodeActive) return;
    if (StepInterval <= 0.0f) return;

    StepTimer += DeltaTime;
    
    // Consume every elapsed interval
    while (StepTimer >= StepInterval && bEpisodeActive)
    {
        StepTimer -= StepInterval;
        CurrentStep++;

        if (IsEpisodeComplete())
        {
            EndEpisode();
            break;
        }
    }
}

void UNLTEpisodeManager::StartEpisode()
{
    // Guard against double-start
    if (bEpisodeActive) return;
    
    CurrentStep = 0;
    StepTimer = 0.0f;
    bEpisodeActive = true;
    bEndEpisodeGuard = false;
}

void UNLTEpisodeManager::EndEpisode()
{
    // Guard against re-entrancy
    if (bEndEpisodeGuard) return;
    bEndEpisodeGuard = true;
    
    bEpisodeActive = false;
    OnEpisodeComplete.Broadcast();
}

void UNLTEpisodeManager::ResetEpisode()
{
    CurrentStep = 0;
    StepTimer = 0.0f;
    bEndEpisodeGuard = false;
}

bool UNLTEpisodeManager::IsEpisodeComplete() const
{
    return CurrentStep >= MaxEpisodeSteps;
}

void UNLTEpisodeManager::CheckCognitiveCompletion(float Independence, float Burnout)
{
    // Episode ends early if Avatar achieves high independence or burns out
    if (Independence >= 0.8f || Burnout >= 0.9f)
    {
        EndEpisode();
    }
}
