// NLTTrainingGameMode.cpp
#include "Scenarios/NLTTrainingGameMode.h"
#include "Agents/NLTTrainingManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ANLTTrainingGameMode::ANLTTrainingGameMode()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ANLTTrainingGameMode::BeginPlay()
{
    // Bypass ANLTDemoGameMode::BeginPlay which starts the 20-agent demo scenario.
    // Training mode should not spawn demo agents — ANLTTrainingManager handles
    // its own actor spawning via deferred SpawnActor.
    AGameModeBase::BeginPlay();

    // Spawn doors only if the training map requires them (Workplace_Level does).
    SpawnLevelDoors();

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

    // Use deferred spawning so we can configure the manager before BeginPlay runs.
    // This ensures bUseLLMControl is set to false (PPO mode) before the manager's
    // BeginPlay() executes.
    ANLTTrainingManager* TrainingManager = World->SpawnActorDeferred<ANLTTrainingManager>(
        ANLTTrainingManager::StaticClass(),
        FTransform::Identity,
        this,
        nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn
    );

    if (TrainingManager)
    {
        // PPO training mode: disable LLM control before BeginPlay.
        TrainingManager->bUseLLMControl = false;
        TrainingManager->bRunInference = true;
        TrainingManager->bRunTraining = true;
        TrainingManager->MaxEpisodeSteps = 512;

        // Complete spawning (fires BeginPlay with properties already set).
        UGameplayStatics::FinishSpawningActor(TrainingManager, FTransform::Identity);

        UE_LOG(LogTemp, Log, TEXT("NLTTrainingGameMode: Training manager spawned: %s"), *TrainingManager->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NLTTrainingGameMode: Failed to spawn training manager"));
    }
}
