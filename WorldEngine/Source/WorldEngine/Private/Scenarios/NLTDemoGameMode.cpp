// NLTDemoGameMode.cpp
#include "Scenarios/NLTDemoGameMode.h"
#include "Scenarios/Demo/NLTScenarioManagerSubsystem.h"
#include "Scenarios/UScenarioLibrary.h"

ANLTDemoGameMode::ANLTDemoGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANLTDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	// The NLT web server is hosted at engine boot by UEngineSubsystem so the
	// shared HTTP listeners (including the ModelContextProtocol MCP endpoint on
	// port 8000) are not coupled to any single PIE world lifecycle.

	if (UNLTScenarioManagerSubsystem* ScenarioManager = GetWorld()->GetSubsystem<UNLTScenarioManagerSubsystem>())
	{
		// Resolve the default scenario asset from the asset registry.
		UScenarioDataAsset* ScenarioAsset = UScenarioLibrary::GetScenarioById(DefaultScenarioId);
		if (!ScenarioAsset)
		{
			UE_LOG(LogTemp, Warning, TEXT("Demo: scenario asset not found for id '%s'; spawning raw"), *DefaultScenarioId.ToString());
		}

		// Parameters are fully deterministic: fixed seed + fixed agent count => reproducible runs.
		FNLTScenarioParams Params;
		Params.NumAgents = 20;
		Params.Seed = 1000;
		Params.SpawnOrigin = FVector(0.0f, 0.0f, 100.0f);
		Params.SpawnRadius = 5000.0f;
		Params.bAutoStartSimulation = true;

		const bool bStarted = ScenarioAsset
			? ScenarioManager->StartScenarioWithAsset(Params, ScenarioAsset)
			: ScenarioManager->StartScenario(Params);

		if (bStarted)
		{
			UE_LOG(LogTemp, Log, TEXT("Demo: scenario '%s' started (asset=%s, agents=%d)"),
				*DefaultScenarioId.ToString(),
				ScenarioAsset ? TEXT("yes") : TEXT("no"),
				Params.NumAgents);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Demo: failed to start scenario '%s'"), *DefaultScenarioId.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Demo: UNLTScenarioManagerSubsystem not available on this world"));
	}
}

void ANLTDemoGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (UNLTScenarioManagerSubsystem* ScenarioManager = GetWorld()->GetSubsystem<UNLTScenarioManagerSubsystem>())
	{
		ScenarioManager->TickScenarioManager(DeltaSeconds);
	}
}

void ANLTDemoGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UNLTScenarioManagerSubsystem* ScenarioManager = GetWorld()->GetSubsystem<UNLTScenarioManagerSubsystem>())
	{
		ScenarioManager->StopScenario();
	}

	Super::EndPlay(EndPlayReason);
}
