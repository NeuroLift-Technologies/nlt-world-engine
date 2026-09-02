#pragma once

#include "CoreMinimal.h"
#include "Core/NLTFusionCore.h"
#include "Subsystems/WorldSubsystem.h"
#include "NLTRoomStateSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogNLTRoomState, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRoomStateChanged, FName, RoomId, const FNLRoomState&, NewState);

/**
 * Represents a room's dynamic state at a point in time.
 * Persisted so environment-only mode can restore exact room conditions.
 */
USTRUCT(BlueprintType)
struct FNLRoomState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	FName RoomId = NAME_None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	FString DisplayName;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	float TemperatureCelsius = 22.0f;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	float LightingLevel = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	float NoiseLevel = 0.1f;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	float Occupancy = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	FName ActiveActivity = NAME_None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	FName WeatherState = NAME_None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	FName TimeOfDayState = NAME_None;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	FLinearColor AmbientColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	float FogDensity = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "NLT|RoomState")
	int32 LastUpdateTick = 0;
};

/**
 * Room-state persistence for environment-only mode.
 * Tracks and persists the dynamic state of each room/environment zone,
 * enabling deterministic restoration of lighting, weather, activity state.
 */
UCLASS()
class UNLTRoomStateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Register a room with initial state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void RegisterRoom(const FNLRoomState& InitialState);

	/** Unregister a room. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	bool UnregisterRoom(FName RoomId);

	/** Update a room's state (broadcasts OnRoomStateChanged). */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void UpdateRoomState(FName RoomId, const FNLRoomState& NewState);

	/** Get a room's current state (returns false if not found). */
	UFUNCTION(BlueprintPure, Category = "NLT|RoomState")
	bool GetRoomState(FName RoomId, FNLRoomState& OutState) const;

	/** Get all registered room IDs. */
	UFUNCTION(BlueprintPure, Category = "NLT|RoomState")
	TArray<FName> GetAllRoomIds() const;

	/** Get all room states (for bulk serialization). */
	UFUNCTION(BlueprintPure, Category = "NLT|RoomState")
	TArray<FNLRoomState> GetAllRoomStates() const;

	/** Restore all room states from a bulk set. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void RestoreAllRoomStates(const TArray<FNLRoomState>& InStates);

	/** Set a room's lighting level. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomLighting(FName RoomId, float LightingLevel, int32 CurrentTick);

	/** Set a room's noise level. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomNoise(FName RoomId, float NoiseLevel, int32 CurrentTick);

	/** Set a room's temperature. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomTemperature(FName RoomId, float TemperatureC, int32 CurrentTick);

	/** Set a room's active activity. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomActivity(FName RoomId, FName Activity, int32 CurrentTick);

	/** Set a room's weather state. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomWeather(FName RoomId, FName WeatherState, int32 CurrentTick);

	/** Set a room's ambient color. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomAmbientColor(FName RoomId, FLinearColor Color, int32 CurrentTick);

	/** Set a room's fog density. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SetRoomFogDensity(FName RoomId, float FogDensity, int32 CurrentTick);

	/** Serialize all room states for persistence. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	void SerializeRoomStates(TArray<uint8>& OutData) const;

	/** Deserialize and restore all room states. */
	UFUNCTION(BlueprintCallable, Category = "NLT|RoomState")
	bool DeserializeRoomStates(const TArray<uint8>& InData);

	/** Get the number of registered rooms. */
	UFUNCTION(BlueprintPure, Category = "NLT|RoomState")
	int32 GetRoomCount() const { return RoomStates.Num(); }

	FOnRoomStateChanged OnRoomStateChanged;

private:
	TMap<FName, FNLRoomState> RoomStates;
};
