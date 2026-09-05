#include "Simulation/PostProcessVolumeActor.h"

APostProcessVolumeActor::APostProcessVolumeActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Unbound volume affecting the full level with no physical extent
	bUnbound = true;
	Priority = 1.0f;
	BlendWeight = 1.0f;
	BlendRadius = 0.0f;
	bEnabled = true;

	ApplySettings();
}

void APostProcessVolumeActor::ApplySettings()
{
	bUnbound = bApplyUnbounded;

	// === Bloom ===
	Settings.bOverride_BloomIntensity = true;
	Settings.BloomIntensity = BloomIntensity;
	Settings.bOverride_BloomThreshold = true;
	Settings.BloomThreshold = BloomThreshold;

	// === Exposure ===
	Settings.bOverride_AutoExposureMinBrightness = true;
	Settings.bOverride_AutoExposureMaxBrightness = true;
	Settings.AutoExposureMinBrightness = Exposure;
	Settings.AutoExposureMaxBrightness = Exposure;

	// === Ambient Occlusion ===
	Settings.bOverride_AmbientOcclusionRadius = true;
	Settings.AmbientOcclusionRadius = AORadius;
	Settings.bOverride_AmbientOcclusionIntensity = true;
	Settings.AmbientOcclusionIntensity = AmbientOcclusion;

	// === Film Grain ===
	Settings.bOverride_FilmGrainIntensity = true;
	Settings.FilmGrainIntensity = FilmGrain;

	// === Chromatic Aberration ===
	Settings.bOverride_SceneFringeIntensity = true;
	Settings.SceneFringeIntensity = ChromaticAberration;

	// === Lens Flare ===
	Settings.bOverride_LensFlareIntensity = true;
	Settings.LensFlareIntensity = LensFlareIntensity;
	Settings.bOverride_LensFlareTint = true;
	Settings.LensFlareTint = LensFlareTint;

	// === Vignette ===
	Settings.bOverride_VignetteIntensity = true;
	Settings.VignetteIntensity = VignetteIntensity;

	// === Color Grading ===
	Settings.bOverride_SceneColorTint = true;
	Settings.SceneColorTint = ColorGradeTint;
	Settings.bOverride_ColorSaturation = true;
	Settings.ColorSaturation = FVector4(Saturation, Saturation, Saturation, 1.0f);
	Settings.bOverride_ColorContrast = true;
	Settings.ColorContrast = FVector4(Contrast, Contrast, Contrast, 1.0f);

	// === Motion Blur ===
	Settings.bOverride_MotionBlurAmount = true;
	Settings.MotionBlurAmount = MotionBlurAmount;

	// === Depth of Field ===
	Settings.bOverride_DepthOfFieldFocalDistance = true;
	Settings.DepthOfFieldFocalDistance = DOFFocalDistance;
	Settings.bOverride_DepthOfFieldFstop = true;
	Settings.DepthOfFieldFstop = DOFAperture;

	// Re-assert volume state in case a default-constructed base reset it
	bEnabled = true;
	Priority = 1.0f;
	BlendWeight = 1.0f;
}
