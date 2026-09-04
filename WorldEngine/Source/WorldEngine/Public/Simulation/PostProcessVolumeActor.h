#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "PostProcessVolumeActor.generated.h"

/**
 * Cinematic post-process volume for WorldEngine.
 * Provides film-quality rendering with bloom, ambient occlusion,
 * film grain, chromatic aberration, lens flare, vignette,
 * and color grading.
 */
UCLASS()
class WORLDENGINE_API APostProcessVolumeActor : public AVolume
{
	GENERATED_BODY()

public:
	APostProcessVolumeActor();

	/** Post-process settings */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process")
	FPostProcessSettings PostProcessSettings;

	// ─── Bloom ──────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Bloom", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float BloomIntensity = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Bloom", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float BloomThreshold = 1.0f;

	// ─── Exposure ───────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Exposure", meta = (ClampMin = "0.1", ClampMax = "2.0"))
	float Exposure = 1.0f;

	// ─── Ambient Occlusion ──────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|AO", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AmbientOcclusion = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|AO", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AORadius = 200.0f;

	// ─── Film Grain ─────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Film", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float FilmGrain = 0.03f;

	// ─── Chromatic Aberration ───────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Lens", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float ChromaticAberration = 0.5f;

	// ─── Lens Flare ─────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Lens", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float LensFlareIntensity = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Lens")
	FLinearColor LensFlareTint = FLinearColor(1.0f, 0.9f, 0.7f, 1.0f);

	// ─── Vignette ───────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Vignette", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VignetteIntensity = 0.3f;

	// ─── Color Grading ──────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Color")
	FLinearColor ColorGradeTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Color", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float Saturation = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Color", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float Contrast = 1.0f;

	// ─── Motion Blur ────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|Motion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MotionBlurAmount = 0.1f;

	// ─── Depth of Field ─────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|DOF", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float DOFFocalDistance = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post-Process|DOF", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float DOFAperture = 5.5f;

	/** Apply all current property values to the post-process settings. */
	UFUNCTION(BlueprintCallable, Category = "Post-Process")
	void ApplySettings();
};
