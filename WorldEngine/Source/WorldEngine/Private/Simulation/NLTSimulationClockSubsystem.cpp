#include "Simulation/NLTSimulationClockSubsystem.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTSimulationClock);

void UNLTSimulationClockSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogNLTSimulationClock, Log, TEXT("Authoritative simulation clock initialized (timestep %.4fs, initial time-of-day %.1fh)"),
		FixedTimestepSeconds, InitialTimeOfDayHours);
}

void UNLTSimulationClockSubsystem::Deinitialize()
{
	UE_LOG(LogNLTSimulationClock, Log, TEXT("Authoritative simulation clock shutdown at tick %d, %.1fs world time"),
		CurrentTick, WorldTimeSeconds);
	Super::Deinitialize();
}

void UNLTSimulationClockSubsystem::AdvanceTick()
{
	if (!bRunning) return;

	++CurrentTick;
	WorldTimeSeconds += static_cast<double>(FixedTimestepSeconds * TimeScale);

	// Track day rollover for time-of-day
	const double DaySeconds = 24.0 * 3600.0;
	if (WorldTimeSeconds >= static_cast<double>(DaysElapsed + 1) * DaySeconds)
	{
		++DaysElapsed;
	}

	OnAuthoritativeTick.Broadcast(CurrentTick, WorldTimeSeconds);
}

void UNLTSimulationClockSubsystem::AdvanceTicks(int32 Count)
{
	for (int32 i = 0; i < Count; ++i)
	{
		AdvanceTick();
	}
}

float UNLTSimulationClockSubsystem::GetTimeOfDayHours() const
{
	const double SecondsInDay = FMath::Fmod(WorldTimeSeconds, 24.0 * 3600.0);
	return static_cast<float>(SecondsInDay / 3600.0) + InitialTimeOfDayHours;
}

void UNLTSimulationClockSubsystem::SetFixedTimestepSeconds(float InSeconds)
{
	FixedTimestepSeconds = FMath::Max(KINDA_SMALL_NUMBER, InSeconds);
	UE_LOG(LogNLTSimulationClock, Log, TEXT("Fixed timestep set to %.6fs"), FixedTimestepSeconds);
}

void UNLTSimulationClockSubsystem::SetTimeScale(float NewScale)
{
	TimeScale = FMath::Max(0.0f, NewScale);
	OnClockRateChanged.Broadcast(TimeScale);
}

void UNLTSimulationClockSubsystem::Start()
{
	if (bRunning) return;
	bRunning = true;
	UE_LOG(LogNLTSimulationClock, Log, TEXT("Clock started at tick %d"), CurrentTick);
}

void UNLTSimulationClockSubsystem::Stop()
{
	if (!bRunning) return;
	bRunning = false;
	UE_LOG(LogNLTSimulationClock, Log, TEXT("Clock stopped at tick %d"), CurrentTick);
}

void UNLTSimulationClockSubsystem::ResetClock()
{
	CurrentTick = 0;
	WorldTimeSeconds = 0.0;
	DaysElapsed = 0;
	UE_LOG(LogNLTSimulationClock, Log, TEXT("Clock reset to tick 0"));
}

void UNLTSimulationClockSubsystem::SetInitialTimeOfDay(float Hours)
{
	InitialTimeOfDayHours = FMath::Fmod(FMath::Fmod(Hours, 24.0f) + 24.0f, 24.0f);
}

void UNLTSimulationClockSubsystem::SerializeClockState(TArray<uint8>& OutData) const
{
	// Simple binary serialization: pack all state into a byte buffer
	OutData.Empty();
	OutData.AddUninitialized(sizeof(int32) * 3 + sizeof(double) + sizeof(float) * 3 + sizeof(bool));

	int32 Offset = 0;
	FMemory::Memcpy(&OutData[Offset], &CurrentTick, sizeof(int32)); Offset += sizeof(int32);
	FMemory::Memcpy(&OutData[Offset], &WorldTimeSeconds, sizeof(double)); Offset += sizeof(double);
	FMemory::Memcpy(&OutData[Offset], &FixedTimestepSeconds, sizeof(float)); Offset += sizeof(float);
	FMemory::Memcpy(&OutData[Offset], &TimeScale, sizeof(float)); Offset += sizeof(float);
	FMemory::Memcpy(&OutData[Offset], &InitialTimeOfDayHours, sizeof(float)); Offset += sizeof(float);
	FMemory::Memcpy(&OutData[Offset], &DaysElapsed, sizeof(int32)); Offset += sizeof(int32);
	FMemory::Memcpy(&OutData[Offset], &bRunning, sizeof(bool)); Offset += sizeof(bool);
}

bool UNLTSimulationClockSubsystem::DeserializeClockState(const TArray<uint8>& InData)
{
	const int32 ExpectedSize = sizeof(int32) * 3 + sizeof(double) + sizeof(float) * 3 + sizeof(bool);
	if (InData.Num() < ExpectedSize)
	{
		UE_LOG(LogNLTSimulationClock, Warning, TEXT("DeserializeClockState: buffer too small (%d < %d)"), InData.Num(), ExpectedSize);
		return false;
	}

	int32 Offset = 0;
	FMemory::Memcpy(&CurrentTick, &InData[Offset], sizeof(int32)); Offset += sizeof(int32);
	FMemory::Memcpy(&WorldTimeSeconds, &InData[Offset], sizeof(double)); Offset += sizeof(double);
	FMemory::Memcpy(&FixedTimestepSeconds, &InData[Offset], sizeof(float)); Offset += sizeof(float);
	FMemory::Memcpy(&TimeScale, &InData[Offset], sizeof(float)); Offset += sizeof(float);
	FMemory::Memcpy(&InitialTimeOfDayHours, &InData[Offset], sizeof(float)); Offset += sizeof(float);
	FMemory::Memcpy(&DaysElapsed, &InData[Offset], sizeof(int32)); Offset += sizeof(int32);
	FMemory::Memcpy(&bRunning, &InData[Offset], sizeof(bool)); Offset += sizeof(bool);

	UE_LOG(LogNLTSimulationClock, Log, TEXT("Clock deserialized: tick %d, time %.1fs, scale %.2f"), CurrentTick, WorldTimeSeconds, TimeScale);
	return true;
}
