// NLTTrainingGameMode.cpp
#include "Scenarios/NLTTrainingGameMode.h"
#include "Agents/NLTTrainingManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

ANLTTrainingGameMode::ANLTTrainingGameMode()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANLTTrainingGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Spawn doors (from NLTDemoGameMode::BeginPlay)
    // Note: We skip scenario agent spawning to avoid conflict with training

    UE_LOG(LogTemp, Log, TEXT("NLTTrainingGameMode: Spawning training manager..."));

    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("NLTTrainingGameMode: No world available"));
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Name = TEXT("NLTTrainingManager_0");
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ANLTTrainingManager* TrainingManager = World->SpawnActor<ANLTTrainingManager>(
        ANLTTrainingManager::StaticClass(),
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        SpawnParams
    );

    if (TrainingManager)
    {
        UE_LOG(LogTemp, Log, TEXT("NLTTrainingGameMode: Training manager spawned: %s"), *TrainingManager->GetName());
        TrainingManager->bRunInference = true;
        TrainingManager->bRunTraining = true;
        TrainingManager->MaxEpisodeSteps = 512;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NLTTrainingGameMode: Failed to spawn training manager"));
    }
}
