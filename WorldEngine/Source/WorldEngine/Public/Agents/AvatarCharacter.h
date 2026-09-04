// AvatarCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PostProcessVolumeComponent.h"
#include "AvatarCharacter.generated.h"

// Visual state for character
UENUM(BlueprintType)
enum class ECharacterVisualState : uint8
{
    Normal UMETA(DisplayName = "Normal"),
    Focused UMETA(DisplayName = "Focused"),
    Stressed UMETA(DisplayName = "Stressed"),
    Interacting UMETA(DisplayName = "Interacting")
};

// Team identification
UENUM(BlueprintType)
enum class ECharacterTeam : uint8
{
    Neutral UMETA(DisplayName = "Neutral"),
    TeamA UMETA(DisplayName = "Team A"),
    TeamB UMETA(DisplayName = "Team B"),
    TeamC UMETA(DisplayName = "Team C")
};

UCLASS()
class WORLDENGINE_API AAvatarCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AAvatarCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // ============== AI Properties ==============
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WanderRadius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMin = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float WaitTimeMax = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float InteractionRange = 200.0f;

    // ============== Visual Properties ==============
    
    // Team identification
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Team")
    ECharacterTeam Team = ECharacterTeam::Neutral;

    // Material overrides for different body parts
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Materials")
    UMaterialInterface* BodyMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Materials")
    UMaterialInterface* HeadMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Materials")
    UMaterialInterface* LimbsMaterial;

    // Dynamic material instances
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|Materials")
    UMaterialInstanceDynamic* DynamicBodyMaterial;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|Materials")
    UMaterialInstanceDynamic* DynamicHeadMaterial;

    // ============== Particle Effects ==============
    
    // Stress particles (appears when stressed)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Particles")
    UParticleSystem* StressParticles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|Particles")
    UParticleSystemComponent* StressParticleComponent;

    // Focus aura (appears when focused)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Particles")
    UParticleSystem* FocusAuraParticles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|Particles")
    UParticleSystemComponent* FocusAuraComponent;

    // Interaction particles
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|Particles")
    UParticleSystem* InteractionParticles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|Particles")
    UParticleSystemComponent* InteractionParticleComponent;

    // ============== Post-Processing ==============
    
    // Character-specific post processing volume
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|PostProcessing")
    UPostProcessVolumeComponent* PostProcessVolume;

    // ============== Visual State ==============
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual|State")
    ECharacterVisualState CurrentVisualState = ECharacterVisualState::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|State")
    float StressThresholdForParticles = 0.6f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual|State")
    float FocusThresholdForAura = 0.7f;

    // ============== Cognitive State ==============
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cognitive")
    class ULTCognitiveStateComponent* CognitiveState;

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Visual update functions
    void UpdateVisualState();
    void UpdateMaterials();
    void UpdateParticleEffects();
    void UpdatePostProcessing();

    // Helper functions
    FLinearColor GetTeamColor() const;
    float GetStressLevel() const;
    float GetFocusLevel() const;

    // Material parameter names
    static const FName ParamTeamColor;
    static const FName ParamStressLevel;
    static const FName ParamFocusLevel;
    static const FName ParamVisualState;
    static const FName ParamPulseIntensity;
};
