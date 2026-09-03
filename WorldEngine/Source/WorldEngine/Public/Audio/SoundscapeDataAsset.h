#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundAttenuation.h"
#include "SoundscapeDataAsset.generated.h"

/**
 * Configuration for one soundscape bed layer.
 * Each layer is a looping ambient sound whose volume and pitch
 * are modulated by the scenario stress level (0..1).
 */
USTRUCT(BlueprintType)
struct FSoundscapeBedLayer
{
	GENERATED_BODY()

	/** The sound wave asset to play (looping). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	TObjectPtr<USoundWave> SoundWave;

	/** Base volume multiplier when stress = 0 (0..1). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BaseVolume = 0.3f;

	/** Volume at maximum stress (0..1). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MaxVolume = 0.8f;

	/** Pitch multiplier at stress = 0. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.5", ClampMax = "2.0"))
	float BasePitch = 1.0f;

	/** Pitch multiplier at max stress. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.5", ClampMax = "2.0"))
	float MaxPitch = 1.1f;

	/** Local offset from the soundscape origin where this bed sits (cm). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FVector LocalOffset = FVector::ZeroVector;

	/** Attenuation settings for spatialized beds (nullptr = 2D/global). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	TObjectPtr<USoundAttenuation> Attenuation;
};

/**
 * Data asset defining the full soundscape for a scenario level.
 * Layers: HVAC hum, fridge murmur, clock tick, distant murmur.
 * Mute = dead world (no scenario active). Unmute = occupied world.
 */
UCLASS(BlueprintType)
class WORLDENGINE_API USoundscapeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Unique identifier for this soundscape (e.g. "Workplace_Default"). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FName SoundscapeId;

	/** Display name. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FText DisplayName;

	/** HVAC hum layer — low-frequency mechanical drone. Volume rises with stress. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FSoundscapeBedLayer HVACLayer;

	/** Fridge murmur layer — gentle intermittent hum. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FSoundscapeBedLayer FridgeLayer;

	/** Clock tick layer — rhythmic ticking. Pitch rises with stress. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FSoundscapeBedLayer ClockLayer;

	/** Distant murmur layer — background voices/machinery. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape")
	FSoundscapeBedLayer MurmurLayer;

	/** Stress at which all beds reach max intensity (0..1). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FullStressThreshold = 1.0f;

	/** Fade-in duration in seconds when soundscape activates. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.0"))
	float FadeInDuration = 2.0f;

	/** Fade-out duration in seconds when soundscape deactivates. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Soundscape", meta = (ClampMin = "0.0"))
	float FadeOutDuration = 1.5f;
};
