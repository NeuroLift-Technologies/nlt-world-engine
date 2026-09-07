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
	const FName CurrentLevel = FName(*UGameplayStatics::GetCurrentLevelName(World));
	UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Current level is '%s'"), *CurrentLevel.ToString());

	// Define all available levels (used for door display names)
	struct FLevelInfo
	{
		FName LevelId;
		FText DisplayName;
	};

	const TArray<FLevelInfo> AllLevels = {
		{ TEXT("Workplace_Level"),  FText::FromString(TEXT("Workplace")) },
		{ TEXT("Personal_Level"),   FText::FromString(TEXT("Personal")) },
		{ TEXT("Social_Level"),     FText::FromString(TEXT("Social")) },
		{ TEXT("Academic_Level"),   FText::FromString(TEXT("Academic")) }
	};

	// Where doors go depends on each level's architecture. Each entry spawns a
	// door that leads to TargetLevelId; doors that lead to the current level
	// are skipped below.
	struct FDoorSpawn
	{
		FName TargetLevelId;
		FVector Location;
		FRotator Rotation;
	};

	TArray<FDoorSpawn> DoorSpawns;
	if (CurrentLevel == TEXT("Workplace_Level"))
	{
		// Workplace is a big open room (floor x = -1600..1600, y = -1200..1200).
		// Doors sit flush against the east wall (inner face x = 1585), spaced
		// evenly along Y, running N-S along the wall.
		DoorSpawns = {
			{ TEXT("Personal_Level"), FVector(1580.0f, -400.0f, 100.0f), FRotator(0.0f, 90.0f, 0.0f) },
			{ TEXT("Social_Level"),   FVector(1580.0f,    0.0f, 100.0f), FRotator(0.0f, 90.0f, 0.0f) },
			{ TEXT("Academic_Level"), FVector(1580.0f,  400.0f, 100.0f), FRotator(0.0f, 90.0f, 0.0f) },
		};
	}
	else if (CurrentLevel == TEXT("Personal_Level") ||
			 CurrentLevel == TEXT("Social_Level") ||
			 CurrentLevel == TEXT("Academic_Level"))
	{
		// The home realm levels each have their own north wall. Social and
		// Academic have a full-width interior wall further north, so their
		// doors must sit on the room-facing (south) side of it at y = 950.
		// Personal_Level has no such partition; its north wall actor Wall_N
		// (StaticMeshActor_1) spans y = 885..915, so doors sit just inside
		// it at y = 870.
		// Each destination gets its own slot in the row; the level we are
		// already in is skipped below.
		const auto HomeDoorX = [](const FName& TargetId) -> float
		{
			if (TargetId == TEXT("Workplace_Level")) return -800.0f;
			if (TargetId == TEXT("Personal_Level"))  return -300.0f;
			if (TargetId == TEXT("Social_Level"))    return  200.0f;
			return  700.0f; // Academic_Level
		};
		const float DoorY = (CurrentLevel == TEXT("Social_Level") ||
							 CurrentLevel == TEXT("Academic_Level")) ? 950.0f : 870.0f;
		for (const FLevelInfo& Info : AllLevels)
		{
			if (Info.LevelId == CurrentLevel) continue;
			DoorSpawns.Add(FDoorSpawn{
				Info.LevelId,
				FVector(HomeDoorX(Info.LevelId), DoorY, 100.0f),
				FRotator(0.0f, 0.0f, 0.0f)
			});
		}
	}
	else
	{
		// Fallback for any other level: a generic row near the world origin.
		UE_LOG(LogTemp, Warning, TEXT("SpawnLevelDoors: no door config for level '%s'; using fallback row"), *CurrentLevel.ToString());
		DoorSpawns = {
			{ TEXT("Workplace_Level"), FVector(-600.0f, 0.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f) },
			{ TEXT("Personal_Level"),  FVector(   0.0f, 0.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f) },
			{ TEXT("Social_Level"),    FVector( 600.0f, 0.0f, 100.0f), FRotator(0.0f, 0.0f, 0.0f) },
		};
	}

	int32 DoorCount = 0;
	for (const FDoorSpawn& Spawn : DoorSpawns)
	{
		// Never spawn a door that leads back to the level we are already in.
		if (Spawn.TargetLevelId == CurrentLevel)
			continue;

		FText DisplayName = FText::FromString(Spawn.TargetLevelId.ToString());
		for (const FLevelInfo& Info : AllLevels)
		{
			if (Info.LevelId == Spawn.TargetLevelId)
			{
				DisplayName = Info.DisplayName;
				break;
			}
		}

		SpawnDoor(Spawn.TargetLevelId, DisplayName, Spawn.Location, Spawn.Rotation);
		DoorCount++;
	}

	UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Spawned %d doors on level '%s'"), DoorCount, *CurrentLevel.ToString());
}

ANLTDoorActor* ANLTDemoGameMode::SpawnDoor(const FName& TargetLevel, const FText& DisplayName, const FVector& Location, const FRotator& Rotation)
{
	UWorld* World = GetWorld();
	if (! World) return nullptr;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*FString::Printf(TEXT("Door_%s"), *TargetLevel.ToString()));
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANLTDoorActor* Door = World->SpawnActor<ANLTDoorActor>(
		ANLTDoorActor::StaticClass(),
		Location,
		Rotation,
		SpawnParams
	);

	if (Door)
	{
		Door->TargetLevelId = TargetLevel;
		Door->DisplayName = DisplayName;
		Door->UpdateLabelText();

		// Face the label toward the side the player approaches from. Each door
		// config mounts its row on a specific wall; the face direction points
		// back into the room (away from the wall).
		int32 YawInt = FMath::RoundToInt(Rotation.Yaw) % 360;
		if (YawInt < 0) YawInt += 360;
		FVector FaceDir(0.0f, -1.0f, 0.0f);
		switch (YawInt)
		{
			case 90:  FaceDir = FVector(-1.0f, 0.0f, 0.0f); break;
			case 180: FaceDir = FVector(0.0f, 1.0f, 0.0f);  break;
			case 270: FaceDir = FVector(1.0f, 0.0f, 0.0f);  break;
			default:  break; // 0 -> south
		}
		Door->SetLabelFacing(FaceDir);

		UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Spawned door to '%s' at %s"), *TargetLevel.ToString(), *Location.ToString());
	}

	return Door;
}
