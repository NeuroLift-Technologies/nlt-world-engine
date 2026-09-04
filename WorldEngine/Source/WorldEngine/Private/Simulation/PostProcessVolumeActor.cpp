#include "Simulation/PostProcessVolumeActor.h"

APostProcessVolumeActor::APostProcessVolumeActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Enable unlimited blending by default
	BrushColor = FColor(0, 0, 0, 0);

	ApplySettings();
}

void APostProcessVolumeActor::ApplySettings()
{
	// === Bloom ===
	PostProcessSettings.bOverride_BloomIntensity = true;
	PostProcessSettings.BloomIntensity = BloomIntensity;
	PostProcessSettings.bOverride_BloomThreshold = true;
	PostProcessSettings.BloomThreshold = BloomThreshold;

	// === Exposure ===
	PostProcessSettings.bOverride_AutoExposureMinBrightness = true;
	PostProcessSettings.bOverride_AutoExposureMaxBrightness = true;
	PostProcessSettings.AutoExposureMinBrightness = Exposure;
	PostProcessSettings.AutoExposureMaxBrightness = Exposure;

	// === Ambient Occlusion ===
	PostProcessSettings.bOverride_AmbientOcclusionRadius = true;
	PostProcessSettings.AmbientOcclusionRadius = AORadius;
	PostProcessSettings.bOverride_AmbientOcclusionIntensity = true;
	PostProcessSettings.AmbientOcclusionIntensity = AmbientOcclusion;

	// === Film Grain ===
	PostProcessSettings.bOverride_FilmGrainIntensity = true;
	PostProcessSettings.FilmGrainIntensity = FilmGrain;

	// === Chromatic Aberration ===
	PostProcessSettings.bOverride_SceneFringeIntensity = true;
	PostProcessSettings.SceneFringeIntensity = ChromaticAberration;

	// === Lens Flare ===
	PostProcessSettings.bOverride_LensFlareIntensity = true;
	PostProcessSettings.LensFlareIntensity = LensFlareIntensity;
	PostProcessSettings.bOverride_LensFlareTint = true;
	PostProcessSettings.LensFlareTint = LensFlareTint;

	// === Vignette ===
	PostProcessSettings.bOverride_VignetteIntensity = true;
	PostProcessSettings.VignetteIntensity = VignetteIntensity;

	// === Color Grading ===
	PostProcessSettings.bOverride_SceneColorTint = true;
	PostProcessSettings.SceneColorTint = ColorGradeTint;
	PostProcessSettings.bOverride_Saturation = true;
	PostProcessSettings.Saturation = FVector4(Saturation, Saturation, Saturation, 1.0f);
	PostProcessSettings.bOverride_Contrast = true;
	PostProcessSettings.Contrast = FVector4(Contrast, Contrast, Contrast, 1.0f);

	// === Motion Blur ===
	PostProcessSettings.bOverride_MotionBlurAmount = true;
	PostProcessSettings.MotionBlurAmount = MotionBlurAmount;

	// === Depth of Field ===
	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	PostProcessSettings.DepthOfFieldFocalDistance = DOFFocalDistance;
	PostProcessSettings.bOverride_DepthOfFieldFstop = true;
	PostProcessSettings.DepthOfFieldFstop = DOFAperture;
}
