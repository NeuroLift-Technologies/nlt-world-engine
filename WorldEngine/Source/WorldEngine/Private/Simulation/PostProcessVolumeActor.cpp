#include "Simulation/PostProcessVolumeActor.h"
#include "Components/PostProcessComponent.h"
#include "Engine/World.h"

APostProcessVolumeActor::APostProcessVolumeActor()
{
    PrimaryActorTick.bCanEverTick = false;
    PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
    RootComponent = PostProcessComponent;
    PostProcessComponent->bUnbound = true;
    PostProcessComponent->Priority = Priority;
    PostProcessComponent->BlendWeight = BlendWeight;
    ApplySettings();
}

void APostProcessVolumeActor::BeginPlay()
{
    Super::BeginPlay();
}

void APostProcessVolumeActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APostProcessVolumeActor::ApplySettings()
{
    if (!PostProcessComponent) return;
    PostProcessComponent->bEnabled = true;
    PostProcessComponent->bUnbound = bApplyUnbounded;
    PostProcessComponent->Priority = Priority;
    PostProcessComponent->BlendWeight = BlendWeight;
    PostProcessComponent->BlendRadius = BlendRadius;

    // Color Grading
    PostProcessComponent->Settings.bOverride_SceneColorTint = true;
    PostProcessComponent->Settings.SceneColorTint = ColorGradeTint;
    PostProcessComponent->Settings.bOverride_ColorSaturation = true;
    PostProcessComponent->Settings.ColorSaturation = FVector4(Saturation, Saturation, Saturation, 1.0f);
    PostProcessComponent->Settings.bOverride_ColorContrast = true;
    PostProcessComponent->Settings.ColorContrast = FVector4(Contrast, Contrast, Contrast, 1.0f);

    // Bloom
    PostProcessComponent->Settings.bOverride_BloomIntensity = true;
    PostProcessComponent->Settings.BloomIntensity = BloomIntensity;
    PostProcessComponent->Settings.bOverride_BloomThreshold = true;
    PostProcessComponent->Settings.BloomThreshold = BloomThreshold;

    // Exposure
    PostProcessComponent->Settings.bOverride_AutoExposureMinBrightness = true;
    PostProcessComponent->Settings.bOverride_AutoExposureMaxBrightness = true;
    PostProcessComponent->Settings.AutoExposureMinBrightness = FMath::Max(0.0f, 1.0f - FMath::Abs(Exposure));
    PostProcessComponent->Settings.AutoExposureMaxBrightness = FMath::Max(0.0f, 1.0f + FMath::Abs(Exposure));

    // Ambient Occlusion
    PostProcessComponent->Settings.bOverride_AmbientOcclusionIntensity = true;
    PostProcessComponent->Settings.AmbientOcclusionIntensity = AmbientOcclusion;

    // Film Grain
    PostProcessComponent->Settings.bOverride_FilmGrainIntensity = true;
    PostProcessComponent->Settings.FilmGrainIntensity = FilmGrain;

    // Chromatic Aberration
    PostProcessComponent->Settings.bOverride_SceneFringeIntensity = true;
    PostProcessComponent->Settings.SceneFringeIntensity = ChromaticAberration;

    // Lens Flare
    PostProcessComponent->Settings.bOverride_LensFlareIntensity = true;
    PostProcessComponent->Settings.LensFlareIntensity = LensFlareIntensity;
    PostProcessComponent->Settings.bOverride_LensFlareTint = true;
    PostProcessComponent->Settings.LensFlareTint = LensFlareTint;

    // Vignette
    PostProcessComponent->Settings.bOverride_VignetteIntensity = true;
    PostProcessComponent->Settings.VignetteIntensity = VignetteIntensity;

    // Motion Blur
    PostProcessComponent->Settings.bOverride_MotionBlurAmount = true;
    PostProcessComponent->Settings.MotionBlurAmount = MotionBlurAmount;

    // Depth of Field
    PostProcessComponent->Settings.bOverride_DepthOfFieldFocalDistance = true;
    PostProcessComponent->Settings.DepthOfFieldFocalDistance = DOFFocalDistance;
    PostProcessComponent->Settings.bOverride_DepthOfFieldFstop = true;
    PostProcessComponent->Settings.DepthOfFieldFstop = DOFAperture;
}
