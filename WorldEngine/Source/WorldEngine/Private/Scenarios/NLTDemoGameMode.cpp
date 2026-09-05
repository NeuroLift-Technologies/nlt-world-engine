// NLTDemoGameMode.cpp
#include "Scenarios/NLTDemoGameMode.h"
#include "Scenarios/Demo/NLTScenarioManagerSubsystem.h"
#include "Scenarios/UScenarioLibrary.h"
#include "World/NLTDoorActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ANLTDemoGameMode::ANLTDemoGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANLTDemoGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Spawn doors that lead to other levels
	SpawnLevelDoors();

	// Start the scenario simulation
	if (UNLTScenarioManagerSubsystem* ScenarioManager = GetWorld()->GetSubsystem<UNLTScenarioManagerSubsystem>())
	{
		UScenarioDataAsset* ScenarioAsset = UScenarioLibrary::GetScenarioById(DefaultScenarioId);
		if (!ScenarioAsset)
		{
			UE_LOG(LogTemp, Warning, TEXT("Demo: scenario asset not found for id '%s'; spawning raw"), *DefaultScenarioId.ToString());
		}

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

void ANLTDemoGameMode::SpawnLevelDoors()
{
	UWorld* World = GetWorld();
	if (!World) return;

	// Get the current level name
	FName CurrentLevel = FName(*UGameplayStatics::GetCurrentLevelName(World));
	UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Current level is '%s'"), *CurrentLevel.ToString());

	// Define all available levels
	struct FLevelInfo
	{
		FName LevelId;
		FText DisplayName;
	};

	TArray<FLevelInfo> AllLevels = {
		{ TEXT("Workplace_Level"),  FText::FromString(TEXT("Workplace")) },
		{ TEXT("Personal_Level"),   FText::FromString(TEXT("Personal")) },
		{ TEXT("Social_Level"),     FText::FromString(TEXT("Social")) },
		{ TEXT("Academic_Level"),   FText::FromString(TEXT("Academic")) }
	};

	// Spawn a door for each level that isn't the current one
	int32 DoorCount = 0;
	for (const FLevelInfo& Info : AllLevels)
	{
		if (Info.LevelId == CurrentLevel)
			continue;

		// Position doors in a row along the X axis, spaced 400 units apart
		float XOffset = (DoorCount + 1) * 400.0f;
		FVector DoorLocation(XOffset, 0.0f, 100.0f);

		SpawnDoor(Info.LevelId, Info.DisplayName, DoorLocation);
		DoorCount++;
	}

	UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Spawned %d doors on level '%s'"), DoorCount, *CurrentLevel.ToString());
}

ANLTDoorActor* ANLTDemoGameMode::SpawnDoor(const FName& TargetLevel, const FText& DisplayName, const FVector& Location)
{
	UWorld* World = GetWorld();
	if (! World) return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*FString::Printf(TEXT("Door_%s"), *TargetLevel.ToString()));
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANLTDoorActor* Door = World->SpawnActor<ANLTDoorActor>(
		ANLTDoorActor::StaticClass(),
		Location,
		FRotator::ZeroRotator,
		SpawnParams
	);

	if (Door)
	{
		Door->TargetLevelId = TargetLevel;
		Door->DisplayName = DisplayName;
		UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Spawned door to '%s' at %s"), *TargetLevel.ToString(), *Location.ToString());
	}

	return Door;
}
