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

	const FName CurrentLevel = FName(*UGameplayStatics::GetCurrentLevelName(World));
	UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Current level is '%s'"), *CurrentLevel.ToString());

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

	struct FDoorSpawn
	{
		FName TargetLevelId;
		FVector Location;
		FRotator Rotation;
	};

	TArray<FDoorSpawn> DoorSpawns;
	if (CurrentLevel == TEXT("Workplace_Level"))
	{
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
		const auto HomeDoorX = [](const FName& TargetId) -> float
		{
			if (TargetId == TEXT("Workplace_Level")) return -800.0f;
			if (TargetId == TEXT("Personal_Level"))  return -300.0f;
			if (TargetId == TEXT("Social_Level"))    return  200.0f;
			return  700.0f;
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

		int32 YawInt = FMath::RoundToInt(Rotation.Yaw) % 360;
		if (YawInt < 0) YawInt += 360;
		FVector FaceDir(0.0f, -1.0f, 0.0f);
		switch (YawInt)
		{
			case 90:  FaceDir = FVector(-1.0f, 0.0f, 0.0f); break;
			case 180: FaceDir = FVector(0.0f, 1.0f, 0.0f);  break;
			case 270: FaceDir = FVector(1.0f, 0.0f, 0.0f);  break;
			default:  break;
		}
		Door->SetLabelFacing(FaceDir);

		UE_LOG(LogTemp, Log, TEXT("SpawnLevelDoors: Spawned door to '%s' at %s"), *TargetLevel.ToString(), *Location.ToString());
	}

	return Door;
}
