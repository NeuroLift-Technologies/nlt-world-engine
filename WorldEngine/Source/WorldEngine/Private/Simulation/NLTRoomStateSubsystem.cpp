#include "Simulation/NLTRoomStateSubsystem.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogNLTRoomState);

void UNLTRoomStateSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogNLTRoomState, Log, TEXT("Room state subsystem initialized"));
}

void UNLTRoomStateSubsystem::Deinitialize()
{
	UE_LOG(LogNLTRoomState, Log, TEXT("Room state subsystem shutdown (%d rooms)"), RoomStates.Num());
	RoomStates.Empty();
	Super::Deinitialize();
}

void UNLTRoomStateSubsystem::RegisterRoom(const FNLRoomState& InitialState)
{
	if (InitialState.RoomId == NAME_None) return;
	RoomStates.Add(InitialState.RoomId, InitialState);
	UE_LOG(LogNLTRoomState, Log, TEXT("Room registered: %s"), *InitialState.RoomId.ToString());
}

bool UNLTRoomStateSubsystem::UnregisterRoom(FName RoomId)
{
	const int32 Removed = RoomStates.Remove(RoomId);
	if (Removed > 0)
	{
		UE_LOG(LogNLTRoomState, Log, TEXT("Room unregistered: %s"), *RoomId.ToString());
		return true;
	}
	return false;
}

void UNLTRoomStateSubsystem::UpdateRoomState(FName RoomId, const FNLRoomState& NewState)
{
	if (NewState.RoomId == NAME_None) return;
	RoomStates.Add(RoomId, NewState);
	OnRoomStateChanged.Broadcast(RoomId, NewState);
}

bool UNLTRoomStateSubsystem::GetRoomState(FName RoomId, FNLRoomState& OutState) const
{
	const FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		OutState = *Found;
		return true;
	}
	return false;
}

TArray<FName> UNLTRoomStateSubsystem::GetAllRoomIds() const
{
	TArray<FName> Ids;
	RoomStates.GetKeys(Ids);
	return Ids;
}

TArray<FNLRoomState> UNLTRoomStateSubsystem::GetAllRoomStates() const
{
	TArray<FNLRoomState> States;
	RoomStates.GenerateValueArray(States);
	return States;
}

void UNLTRoomStateSubsystem::RestoreAllRoomStates(const TArray<FNLRoomState>& InStates)
{
	RoomStates.Empty();
	for (const FNLRoomState& State : InStates)
	{
		if (State.RoomId != NAME_None)
		{
			RoomStates.Add(State.RoomId, State);
		}
	}
	UE_LOG(LogNLTRoomState, Log, TEXT("Restored %d room states"), RoomStates.Num());
}

void UNLTRoomStateSubsystem::SetRoomLighting(FName RoomId, float LightingLevel, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->LightingLevel = LightingLevel;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

void UNLTRoomStateSubsystem::SetRoomNoise(FName RoomId, float NoiseLevel, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->NoiseLevel = NoiseLevel;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

void UNLTRoomStateSubsystem::SetRoomTemperature(FName RoomId, float TemperatureC, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->TemperatureCelsius = TemperatureC;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

void UNLTRoomStateSubsystem::SetRoomActivity(FName RoomId, FName Activity, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->ActiveActivity = Activity;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

void UNLTRoomStateSubsystem::SetRoomWeather(FName RoomId, FName WeatherState, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->WeatherState = WeatherState;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

void UNLTRoomStateSubsystem::SetRoomAmbientColor(FName RoomId, FLinearColor Color, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->AmbientColor = Color;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

void UNLTRoomStateSubsystem::SetRoomFogDensity(FName RoomId, float FogDensity, int32 CurrentTick)
{
	FNLRoomState* Found = RoomStates.Find(RoomId);
	if (Found)
	{
		Found->FogDensity = FogDensity;
		Found->LastUpdateTick = CurrentTick;
		OnRoomStateChanged.Broadcast(RoomId, *Found);
	}
}

// Helper: write int32 to buffer at offset
static void WriteInt32(TArray<uint8>& Buffer, int32& Offset, int32 Value)
{
	if (Offset + sizeof(int32) > Buffer.Num())
	{
		Buffer.AddUninitialized(sizeof(int32));
	}
	FMemory::Memcpy(&Buffer[Offset], &Value, sizeof(int32));
	Offset += sizeof(int32);
}

// Helper: write float to buffer at offset
static void WriteFloat(TArray<uint8>& Buffer, int32& Offset, float Value)
{
	if (Offset + sizeof(float) > Buffer.Num())
	{
		Buffer.AddUninitialized(sizeof(float));
	}
	FMemory::Memcpy(&Buffer[Offset], &Value, sizeof(float));
	Offset += sizeof(float);
}

// Helper: write FName as string length + chars
static void WriteFName(TArray<uint8>& Buffer, int32& Offset, FName Name)
{
	const FString NameStr = Name.ToString();
	const int32 Len = NameStr.Len();
	WriteInt32(Buffer, Offset, Len);

	if (Offset + Len * sizeof(TCHAR) > Buffer.Num())
	{
		Buffer.AddUninitialized(Len * sizeof(TCHAR));
	}
	FMemory::Memcpy(&Buffer[Offset], *NameStr, Len * sizeof(TCHAR));
	Offset += Len * sizeof(TCHAR);
}

// Helper: write FString as string length + chars
static void WriteFString(TArray<uint8>& Buffer, int32& Offset, const FString& Str)
{
	const int32 Len = Str.Len();
	WriteInt32(Buffer, Offset, Len);

	if (Offset + Len * sizeof(TCHAR) > Buffer.Num())
	{
		Buffer.AddUninitialized(Len * sizeof(TCHAR));
	}
	FMemory::Memcpy(&Buffer[Offset], *Str, Len * sizeof(TCHAR));
	Offset += Len * sizeof(TCHAR);
}

// Helper: read int32 from buffer at offset
static int32 ReadInt32(const TArray<uint8>& Buffer, int32& Offset)
{
	int32 Value = 0;
	if (Offset + sizeof(int32) <= Buffer.Num())
	{
		FMemory::Memcpy(&Value, &Buffer[Offset], sizeof(int32));
		Offset += sizeof(int32);
	}
	return Value;
}

// Helper: read float from buffer at offset
static float ReadFloat(const TArray<uint8>& Buffer, int32& Offset)
{
	float Value = 0.0f;
	if (Offset + sizeof(float) <= Buffer.Num())
	{
		FMemory::Memcpy(&Value, &Buffer[Offset], sizeof(float));
		Offset += sizeof(float);
	}
	return Value;
}

// Helper: read FName from buffer at offset
static FName ReadFName(const TArray<uint8>& Buffer, int32& Offset)
{
	const int32 Len = ReadInt32(Buffer, Offset);
	if (Len > 0 && Offset + Len * sizeof(TCHAR) <= Buffer.Num())
	{
		TArray<TCHAR> Chars;
		Chars.SetNumUninitialized(Len);
		FMemory::Memcpy(Chars.GetData(), &Buffer[Offset], Len * sizeof(TCHAR));
		Offset += Len * sizeof(TCHAR);
		return FName(*FString(Chars.GetData(), Len));
	}
	return NAME_None;
}

// Helper: read FString from buffer at offset
static FString ReadFString(const TArray<uint8>& Buffer, int32& Offset)
{
	const int32 Len = ReadInt32(Buffer, Offset);
	if (Len > 0 && Offset + Len * sizeof(TCHAR) <= Buffer.Num())
	{
		TArray<TCHAR> Chars;
		Chars.SetNumUninitialized(Len);
		FMemory::Memcpy(Chars.GetData(), &Buffer[Offset], Len * sizeof(TCHAR));
		Offset += Len * sizeof(TCHAR);
		return FString(Chars.GetData());
	}
	return FString();
}

void UNLTRoomStateSubsystem::SerializeRoomStates(TArray<uint8>& OutData) const
{
	OutData.Empty();
	int32 Offset = 0;

	// Write count
	WriteInt32(OutData, Offset, RoomStates.Num());

	// Write each room state
	for (const auto& Pair : RoomStates)
	{
		const FNLRoomState& State = Pair.Value;
		WriteFName(OutData, Offset, State.RoomId);
		WriteFString(OutData, Offset, State.DisplayName);
		WriteFloat(OutData, Offset, State.TemperatureCelsius);
		WriteFloat(OutData, Offset, State.LightingLevel);
		WriteFloat(OutData, Offset, State.NoiseLevel);
		WriteFloat(OutData, Offset, State.Occupancy);
		WriteFName(OutData, Offset, State.ActiveActivity);
		WriteFName(OutData, Offset, State.WeatherState);
		WriteFName(OutData, Offset, State.TimeOfDayState);
		WriteFloat(OutData, Offset, State.AmbientColor.R);
		WriteFloat(OutData, Offset, State.AmbientColor.G);
		WriteFloat(OutData, Offset, State.AmbientColor.B);
		WriteFloat(OutData, Offset, State.AmbientColor.A);
		WriteFloat(OutData, Offset, State.FogDensity);
		WriteInt32(OutData, Offset, State.LastUpdateTick);
	}
}

bool UNLTRoomStateSubsystem::DeserializeRoomStates(const TArray<uint8>& InData)
{
	int32 Offset = 0;
	const int32 Count = ReadInt32(InData, Offset);

	if (Count < 0 || Count > 10000)
	{
		UE_LOG(LogNLTRoomState, Warning, TEXT("DeserializeRoomStates: invalid count %d"), Count);
		return false;
	}

	RoomStates.Empty();

	for (int32 i = 0; i < Count; ++i)
	{
		FNLRoomState State;
		State.RoomId = ReadFName(InData, Offset);
		State.DisplayName = ReadFString(InData, Offset);
		State.TemperatureCelsius = ReadFloat(InData, Offset);
		State.LightingLevel = ReadFloat(InData, Offset);
		State.NoiseLevel = ReadFloat(InData, Offset);
		State.Occupancy = ReadFloat(InData, Offset);
		State.ActiveActivity = ReadFName(InData, Offset);
		State.WeatherState = ReadFName(InData, Offset);
		State.TimeOfDayState = ReadFName(InData, Offset);
		State.AmbientColor.R = ReadFloat(InData, Offset);
		State.AmbientColor.G = ReadFloat(InData, Offset);
		State.AmbientColor.B = ReadFloat(InData, Offset);
		State.AmbientColor.A = ReadFloat(InData, Offset);
		State.FogDensity = ReadFloat(InData, Offset);
		State.LastUpdateTick = ReadInt32(InData, Offset);

		if (State.RoomId != NAME_None)
		{
			RoomStates.Add(State.RoomId, State);
		}
	}

	UE_LOG(LogNLTRoomState, Log, TEXT("Deserialized %d room states"), RoomStates.Num());
	return true;
}
