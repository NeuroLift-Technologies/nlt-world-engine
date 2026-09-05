#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PostProcessComponent.h"
#include "PostProcessVolumeActor.generated.h"

UCLASS()
class WORLDENGINE_API APostProcessVolumeActor : public AActor
{
    GENERATED_BODY()
public:
    APostProcessVolumeActor();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    /** Global scene color tint for warm/cool grading */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|ColorGrading")
    FLinearColor ColorGradeTint;

    /** Overall saturation multiplier (1.0 = neutral) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|ColorGrading")
    float Saturation = 1.0f;

    /** Overall contrast multiplier (1.0 = neutral) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|ColorGrading")
    float Contrast = 1.0f;

    /** Bloom effect intensity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Bloom")
    float BloomIntensity = 1.0f;

    /** Bloom threshold (lower = more bloom bleeding) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Bloom")
    float BloomThreshold = 1.0f;

    /** Camera exposure compensation stops */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Exposure")
    float Exposure = 0.0f;

    /** Ambient occlusion intensity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|AmbientOcclusion")
    float AmbientOcclusion = 0.5f;

    /** Film grain strength */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Film")
    float FilmGrain = 0.0f;

    /** Chromatic aberration */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Lens")
    float ChromaticAberration = 0.0f;

    /** Lens flare intensity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Lens")
    float LensFlareIntensity = 1.0f;

    /** Lens flare tint */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Lens")
    FLinearColor LensFlareTint;

    /** Vignette intensity */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|Vignette")
    float VignetteIntensity = 0.5f;

    /** Motion blur amount */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|MotionBlur")
    float MotionBlurAmount = 0.5f;

    /** Depth of field focal distance */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|DepthOfField")
    float DOFFocalDistance = 1000.0f;

    /** Depth of field aperture (f-stop) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess|DepthOfField")
    float DOFAperture = 8.0f;

    /** Apply settings to the actor's post process component */
    UFUNCTION(BlueprintCallable, Category = "PostProcess")
    void ApplySettings();

    /** Whether the volume is unbound (affects whole level) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
    bool bApplyUnbounded = true;

    /** Priority for overlapping volumes */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
    float Priority = 1.0f;

    /** Blend weight 0..1 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
    float BlendWeight = 1.0f;

    /** Blend radius */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
    float BlendRadius = 0.0f;

private:
    UPROPERTY(VisibleAnywhere, Category = "PostProcess")
    UPostProcessComponent* PostProcessComponent;
};
