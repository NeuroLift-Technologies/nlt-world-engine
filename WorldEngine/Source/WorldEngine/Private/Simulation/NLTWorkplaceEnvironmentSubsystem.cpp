// NLTWorkplaceEnvironmentSubsystem.cpp - environment-only sim infrastructure for Workplace_Level
#include "Simulation/NLTWorkplaceEnvironmentSubsystem.h"
#include "Simulation/NLTSimulationClockSubsystem.h"
#include "Simulation/NLTDeterministicSeedSubsystem.h"
#include "Simulation/NLTRoomStateSubsystem.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTWorkplaceEnvironment);

namespace
{
    // Standard Workplace_Level rooms (stable id + friendly display name).
    // IDs must stay stable because they are persisted in room-state data.
    struct FWorkplaceRoomDef
    {
        const TCHAR* Id;
        const TCHAR* DisplayName;
    };

    const FWorkplaceRoomDef kWorkplaceRooms[] = {
        { TEXT("Lobby"),          TEXT("Lobby") },
        { TEXT("OpenOffice"),     TEXT("Open Office") },
        { TEXT("BreakRoom"),      TEXT("Break Room") },
        { TEXT("ConferenceRoom"), TEXT("Conference Room") },
        { TEXT("MeetingRoomA"),   TEXT("Meeting Room A") },
        { TEXT("FocusRoom"),      TEXT("Focus Room") },
        { TEXT("Pantry"),         TEXT("Pantry") },
        { TEXT("Hallway"),        TEXT("Hallway") },
    };
    constexpr int32 NumWorkplaceRooms = UE_ARRAY_COUNT(kWorkplaceRooms);

    constexpr int32 kEnvironmentMagic = 0x4E4C5457; // "NLTW"
    constexpr int32 kEnvironmentVersion = 1;
}

bool UNLTWorkplaceEnvironmentSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }
    const UWorld* World = Cast<UWorld>(Outer);
    return World && (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE);
}

void UNLTWorkplaceEnvironmentSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    Clock = GetWorld()->GetSubsystem<UNLTSimulationClockSubsystem>();
    EventBus = GetWorld()->GetSubsystem<UNLTEventBus>();
    Seed = GetWorld()->GetSubsystem<UNLTDeterministicSeedSubsystem>();
    RoomState = GetWorld()->GetSubsystem<UNLTRoomStateSubsystem>();

    if (Clock)
    {
        Clock->OnAuthoritativeTick.AddDynamic(this, &UNLTWorkplaceEnvironmentSubsystem::HandleAuthoritativeTick);
    }

    UE_LOG(LogNLTWorkplaceEnvironment, Log,
        TEXT("Workplace environment driver initialized (clock=%s eventBus=%s seed=%s roomState=%s)"),
        Clock ? TEXT("yes") : TEXT("no"),
        EventBus ? TEXT("yes") : TEXT("no"),
        Seed ? TEXT("yes") : TEXT("no"),
        RoomState ? TEXT("yes") : TEXT("no"));
}

void UNLTWorkplaceEnvironmentSubsystem::Deinitialize()
{
    bRunning = false;
    if (Clock)
    {
        Clock->OnAuthoritativeTick.RemoveDynamic(this, &UNLTWorkplaceEnvironmentSubsystem::HandleAuthoritativeTick);
    }
    Super::Deinitialize();
}

void UNLTWorkplaceEnvironmentSubsystem::ConfigureEnvironment(FName ScenarioId, int32 RoomSeed, bool bStartSimulation)
{
    ActiveScenarioId = ScenarioId;
    MasterSeed = RoomSeed;
    TicksSinceLastRefresh = 0;
    LastPublishedTimeOfDayHour = -1;

    if (Seed)
    {
        Seed->SetMasterSeed(RoomSeed);
    }

    RegisterWorkplaceRooms(0);
    bConfigured = true;

    UE_LOG(LogNLTWorkplaceEnvironment, Log,
        TEXT("Workplace environment configured: scenario=%s roomSeed=%d rooms=%d"),
        *ActiveScenarioId.ToString(), MasterSeed, NumWorkplaceRooms);

    if (bStartSimulation)
    {
        StartEnvironmentSimulation();
    }
}

void UNLTWorkplaceEnvironmentSubsystem::StartEnvironmentSimulation()
{
    if (!Clock)
    {
        UE_LOG(LogNLTWorkplaceEnvironment, Warning, TEXT("StartEnvironmentSimulation: clock subsystem unavailable"));
        return;
    }
    if (bRunning)
    {
        return;
    }
    if (!bConfigured)
    {
        // A seed was never set; fall back to a fixed default so rooms still register.
        ConfigureEnvironment(NAME_None, 12345, false);
    }
    Clock->Start();
    bRunning = true;
    UE_LOG(LogNLTWorkplaceEnvironment, Log, TEXT("Workplace environment simulation started (tick=%d)"), Clock->GetCurrentTick());
}

void UNLTWorkplaceEnvironmentSubsystem::StopEnvironmentSimulation()
{
    if (Clock)
    {
        Clock->Stop();
    }
    if (!bRunning)
    {
        return;
    }
    bRunning = false;
    UE_LOG(LogNLTWorkplaceEnvironment, Log, TEXT("Workplace environment simulation stopped"));
}

void UNLTWorkplaceEnvironmentSubsystem::StepEnvironmentSimulation(int32 NumTicks)
{
    if (!Clock || !bRunning)
    {
        return;
    }
    const int32 Count = FMath::Max(0, NumTicks);
    for (int32 i = 0; i < Count; ++i)
    {
        Clock->AdvanceTick();
    }
}

void UNLTWorkplaceEnvironmentSubsystem::HandleAuthoritativeTick(int32 Tick, double /*WorldTimeSeconds*/)
{
    if (!bRunning)
    {
        return;
    }

    PublishTimeOfDay(Tick);

    ++TicksSinceLastRefresh;
    if (TicksSinceLastRefresh >= DetailRefreshIntervalTicks)
    {
        TicksSinceLastRefresh = 0;
        RefreshRooms(Tick);
    }
}

void UNLTWorkplaceEnvironmentSubsystem::RegisterWorkplaceRooms(int32 Tick)
{
    if (!RoomState)
    {
        return;
    }

    for (int32 i = 0; i < NumWorkplaceRooms; ++i)
    {
        FNLRoomState Initial;
        Initial.RoomId = FName(kWorkplaceRooms[i].Id);
        Initial.DisplayName = kWorkplaceRooms[i].DisplayName;
        Initial.LastUpdateTick = Tick;

        if (Seed)
        {
            // Deterministic initial conditions, derived from the master seed.
            Initial.LightingLevel = FMath::Clamp(Seed->GetDeterministicRange(ENLTSeedCategory::Lighting, 0.5f, 1.0f), 0.15f, 1.5f);
            Initial.NoiseLevel = FMath::Clamp(Seed->GetDeterministicRange(ENLTSeedCategory::Ambient, 0.0f, 0.3f), 0.0f, 1.0f);
            Initial.TemperatureCelsius = FMath::Clamp(Seed->GetDeterministicRange(ENLTSeedCategory::Ambient, 20.0f, 24.0f), 10.0f, 40.0f);
        }
        Initial.AmbientColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

        RoomState->RegisterRoom(Initial);
    }
}

void UNLTWorkplaceEnvironmentSubsystem::RefreshRooms(int32 Tick)
{
    if (!RoomState || !Seed)
    {
        return;
    }

    const TArray<FName> RoomIds = RoomState->GetAllRoomIds();
    for (const FName RoomId : RoomIds)
    {
        FNLRoomState Current;
        if (!RoomState->GetRoomState(RoomId, Current))
        {
            continue;
        }

        const float NewLighting = FMath::Clamp(
            Current.LightingLevel + Seed->GetDeterministicRange(ENLTSeedCategory::Lighting, -0.08f, 0.08f), 0.15f, 1.5f);
        const float NewNoise = FMath::Clamp(
            Current.NoiseLevel + Seed->GetDeterministicRange(ENLTSeedCategory::Ambient, -0.05f, 0.05f), 0.0f, 1.0f);

        RoomState->SetRoomLighting(RoomId, NewLighting, Tick);
        RoomState->SetRoomNoise(RoomId, NewNoise, Tick);

        if (EventBus)
        {
            EventBus->RaiseEnvironmentEvent(
                ENLTSimulationEventType::EnvLightingChanged, Tick, RoomId,
                FString::Printf(TEXT("LightingRefresh %.2f"), NewLighting), NewLighting);
            EventBus->RaiseEnvironmentEvent(
                ENLTSimulationEventType::EnvRoomStateChanged, Tick, RoomId,
                TEXT("RoomDetailRefresh"), NewNoise);
        }
    }
}

void UNLTWorkplaceEnvironmentSubsystem::PublishTimeOfDay(int32 Tick)
{
    if (!Clock || !EventBus)
    {
        return;
    }

    const float Hours = Clock->GetTimeOfDayHours();
    const int32 Hour = FMath::FloorToInt(FMath::Fmod(FMath::Fmod(Hours, 24.0f) + 24.0f, 24.0f));
    if (Hour == LastPublishedTimeOfDayHour)
    {
        return;
    }
    LastPublishedTimeOfDayHour = Hour;

    EventBus->RaiseEnvironmentEvent(
        ENLTSimulationEventType::EnvTimeOfDayChanged, Tick, NAME_None,
        FString::Printf(TEXT("TimeOfDay %.1f"), Hours), Hours);

    // Global daylight curve: brightest around midday, dark before 6am / after 6pm.
    const float Daylight = FMath::Clamp(FMath::Sin((Hours - 6.0f) * (UE_PI / 12.0f)), 0.0f, 1.0f);
    const float GlobalLighting = FMath::Lerp(0.15f, 1.0f, Daylight);
    EventBus->RaiseEnvironmentEvent(
        ENLTSimulationEventType::EnvLightingChanged, Tick, NAME_None,
        TEXT("GlobalLighting"), GlobalLighting);
}

void UNLTWorkplaceEnvironmentSubsystem::WriteInt32(TArray<uint8>& OutData, int32& Offset, int32 Value)
{
    OutData.AddUninitialized(sizeof(int32));
    FMemory::Memcpy(&OutData[Offset], &Value, sizeof(int32));
    Offset += sizeof(int32);
}

int32 UNLTWorkplaceEnvironmentSubsystem::ReadInt32(const TArray<uint8>& InData, int32& Offset)
{
    if (Offset + (int32)sizeof(int32) > InData.Num())
    {
        return 0;
    }
    int32 Value = 0;
    FMemory::Memcpy(&Value, &InData[Offset], sizeof(int32));
    Offset += sizeof(int32);
    return Value;
}

void UNLTWorkplaceEnvironmentSubsystem::AppendBlob(TArray<uint8>& OutData, int32& Offset, const TArray<uint8>& Blob)
{
    WriteInt32(OutData, Offset, Blob.Num());
    if (Blob.Num() > 0)
    {
        OutData.AddUninitialized(Blob.Num());
        FMemory::Memcpy(&OutData[Offset], Blob.GetData(), Blob.Num());
        Offset += Blob.Num();
    }
}

bool UNLTWorkplaceEnvironmentSubsystem::ReadBlob(const TArray<uint8>& InData, int32& Offset, TArray<uint8>& OutBlob)
{
    const int32 Size = ReadInt32(InData, Offset);
    if (Size < 0 || Offset + Size > InData.Num())
    {
        return false;
    }
    OutBlob.SetNum(Size);
    if (Size > 0)
    {
        FMemory::Memcpy(OutBlob.GetData(), &InData[Offset], Size);
        Offset += Size;
    }
    return true;
}

void UNLTWorkplaceEnvironmentSubsystem::SerializeEnvironmentState(TArray<uint8>& OutData) const
{
    OutData.Empty();
    int32 Offset = 0;

    // Header
    WriteInt32(OutData, Offset, kEnvironmentMagic);
    WriteInt32(OutData, Offset, kEnvironmentVersion);
    // Scalar state
    WriteInt32(OutData, Offset, MasterSeed);
    WriteInt32(OutData, Offset, bRunning ? 1 : 0);
    WriteInt32(OutData, Offset, LastPublishedTimeOfDayHour);
    WriteInt32(OutData, Offset, TicksSinceLastRefresh);
    // Scenario id (length + TCHAR payload)
    const FString ScenarioName = ActiveScenarioId.ToString();
    const int32 NameLen = ScenarioName.Len();
    WriteInt32(OutData, Offset, NameLen);
    if (NameLen > 0)
    {
        OutData.AddUninitialized(NameLen * (int32)sizeof(TCHAR));
        FMemory::Memcpy(&OutData[Offset], *ScenarioName, NameLen * sizeof(TCHAR));
        Offset += NameLen * (int32)sizeof(TCHAR);
    }

    // Subsystem payloads
    {
        TArray<uint8> ClockData;
        if (Clock) { Clock->SerializeClockState(ClockData); }
        AppendBlob(OutData, Offset, ClockData);
    }
    {
        TArray<uint8> SeedData;
        if (Seed) { Seed->SerializeSeedState(SeedData); }
        AppendBlob(OutData, Offset, SeedData);
    }
    {
        TArray<uint8> RoomData;
        if (RoomState) { RoomState->SerializeRoomStates(RoomData); }
        AppendBlob(OutData, Offset, RoomData);
    }
}

bool UNLTWorkplaceEnvironmentSubsystem::DeserializeEnvironmentState(const TArray<uint8>& InData)
{
    int32 Offset = 0;
    if (ReadInt32(InData, Offset) != kEnvironmentMagic)
    {
        UE_LOG(LogNLTWorkplaceEnvironment, Warning, TEXT("DeserializeEnvironmentState: bad magic"));
        return false;
    }
    if (ReadInt32(InData, Offset) < kEnvironmentVersion)
    {
        UE_LOG(LogNLTWorkplaceEnvironment, Warning, TEXT("DeserializeEnvironmentState: unsupported version"));
        return false;
    }

    MasterSeed = ReadInt32(InData, Offset);
    bRunning = ReadInt32(InData, Offset) != 0;
    LastPublishedTimeOfDayHour = ReadInt32(InData, Offset);
    TicksSinceLastRefresh = ReadInt32(InData, Offset);

    const int32 NameLen = ReadInt32(InData, Offset);
    if (NameLen < 0 || Offset + NameLen * (int32)sizeof(TCHAR) > InData.Num())
    {
        return false;
    }
    if (NameLen > 0)
    {
        TArray<TCHAR> Chars;
        Chars.SetNumUninitialized(NameLen);
        FMemory::Memcpy(Chars.GetData(), &InData[Offset], NameLen * sizeof(TCHAR));
        ActiveScenarioId = FName(FString(Chars.GetData(), NameLen));
        Offset += NameLen * (int32)sizeof(TCHAR);
    }
    else
    {
        ActiveScenarioId = NAME_None;
    }

    TArray<uint8> ClockData;
    TArray<uint8> SeedData;
    TArray<uint8> RoomData;
    if (!ReadBlob(InData, Offset, ClockData) ||
        !ReadBlob(InData, Offset, SeedData) ||
        !ReadBlob(InData, Offset, RoomData))
    {
        UE_LOG(LogNLTWorkplaceEnvironment, Warning, TEXT("DeserializeEnvironmentState: truncated payload"));
        return false;
    }

    bool bOk = true;
    if (Clock && ClockData.Num() > 0) { bOk = Clock->DeserializeClockState(ClockData) && bOk; }
    if (Seed && SeedData.Num() > 0)  { bOk = Seed->DeserializeSeedState(SeedData) && bOk; }
    if (RoomState && RoomData.Num() > 0) { bOk = RoomState->DeserializeRoomStates(RoomData) && bOk; }

    bConfigured = true;
    UE_LOG(LogNLTWorkplaceEnvironment, Log,
        TEXT("Workplace environment deserialized: seed=%d running=%d rooms=%d"),
        MasterSeed, bRunning ? 1 : 0, RoomState ? RoomState->GetRoomCount() : 0);
    return bOk;
}