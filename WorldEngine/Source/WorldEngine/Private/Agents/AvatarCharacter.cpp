// AvatarCharacter.cpp
#include "Agents/AvatarCharacter.h"
#include "Agents/AvatarAIController.h"
#include "Agents/LTCognitiveStateComponent.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PostProcessComponent.h"
#include "UObject/ConstructorHelpers.h"

// Initialize static material parameter names
const FName AAvatarCharacter::ParamTeamColor = TEXT("TeamColor");
const FName AAvatarCharacter::ParamStressLevel = TEXT("StressLevel");
const FName AAvatarCharacter::ParamFocusLevel = TEXT("FocusLevel");
const FName AAvatarCharacter::ParamVisualState = TEXT("VisualState");
const FName AAvatarCharacter::ParamPulseIntensity = TEXT("PulseIntensity");

AAvatarCharacter::AAvatarCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set default AI controller
    AIControllerClass = AAvatarAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    // Create cognitive state component
    CognitiveState = CreateDefaultSubobject<ULTCognitiveStateComponent>(TEXT("CognitiveState"));

    // Configure character movement
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        MoveComp->MaxWalkSpeed = 300.0f;
        MoveComp->bOrientRotationToMovement = true;
        MoveComp->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
    }

    // ============== Initialize Visual Components ==============
    
    // Load the SimBody static mesh for the avatar's visible body
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SimBodyMeshObj(
        TEXT("/Game/Kits/SimBody/SM_SimBody_Base.SM_SimBody_Base"));

    // Create a dedicated BodyMesh static mesh component for the avatar
    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(GetRootComponent()); // attach to the capsule
    BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BodyMesh->SetCastShadow(true);
    
    // Load the mesh asset
    if (SimBodyMeshObj.Succeeded())
    {
        BodyMesh->SetStaticMesh(SimBodyMeshObj.Object);
        SimBodyMesh = SimBodyMeshObj.Object;
        
        // Load the material that comes with SimBody
        static ConstructorHelpers::FObjectFinder<UMaterialInterface> SimBodyMaterialObj(
            TEXT("/Game/Kits/SimBody/M_SimBody_Base.M_SimBody_Base"));
        if (SimBodyMaterialObj.Succeeded())
        {
            BodyMaterial = SimBodyMaterialObj.Object;
        }
    }
    
    // Position the mesh so it sits on the ground (centered on capsule)
    BodyMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
    BodyMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 1.0f));
    
    // Create particle system components
    StressParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("StressParticles"));
    StressParticleComponent->SetupAttachment(BodyMesh);
    StressParticleComponent->bAutoActivate = false;
    StressParticleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

    FocusAuraComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FocusAuraParticles"));
    FocusAuraComponent->SetupAttachment(BodyMesh);
    FocusAuraComponent->bAutoActivate = false;
    FocusAuraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

    InteractionParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("InteractionParticles"));
    InteractionParticleComponent->SetupAttachment(BodyMesh);
    InteractionParticleComponent->bAutoActivate = false;
    InteractionParticleComponent->SetRelativeLocation(FVector(50.0f, 0.0f, 50.0f));

    // Create post process component
    PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
    PostProcessComponent->SetupAttachment(BodyMesh);
    PostProcessComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

    // Create the cognitive-state-driven avatar visual component
    AvatarVisualComponent = CreateDefaultSubobject<UNLTAvatarVisualComponent>(TEXT("AvatarVisual"));

    // Initialize values
    StressThresholdForParticles = 0.6f;
    FocusThresholdForAura = 0.7f;
    Team = ECharacterTeam::Neutral;
}

void AAvatarCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize dynamic materials on BodyMesh
    if (BodyMaterial && BodyMesh)
    {
        DynamicBodyMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, BodyMesh);
        BodyMesh->SetMaterial(0, DynamicBodyMaterial);
    }
    
    // Set particle systems if assigned
    if (StressParticles)
    {
        StressParticleComponent->SetTemplate(StressParticles);
    }
    
    if (FocusAuraParticles)
    {
        FocusAuraComponent->SetTemplate(FocusAuraParticles);
    }
    
    if (InteractionParticles)
    {
        InteractionParticleComponent->SetTemplate(InteractionParticles);
    }
    
    // Update all visual systems
    UpdateVisualState();
    UpdateMaterials();
    UpdateParticleEffects();
    UpdatePostProcessing();

    // Drive the cognitive-state visual component from the CognitiveState
    if (AvatarVisualComponent && CognitiveState)
    {
        AvatarVisualComponent->UpdateFromCognitiveState(
            CognitiveState->Focus,
            CognitiveState->Stress,
            CognitiveState->CognitiveLoad,
            CognitiveState->EmotionalState);
    }
}

void AAvatarCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Update all visual systems
    UpdateVisualState();
    UpdateMaterials();
    UpdateParticleEffects();
    UpdatePostProcessing();
}

void AAvatarCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // No player input — AI controlled
}

// ============== Visual State Updates ==============

void AAvatarCharacter::UpdateVisualState()
{
    float StressLevel = GetStressLevel();
    float FocusLevel = GetFocusLevel();
    
    ECharacterVisualState NewState = ECharacterVisualState::Normal;
    
    if (StressLevel > 0.8f)
    {
        NewState = ECharacterVisualState::Stressed;
    }
    else if (FocusLevel > FocusThresholdForAura)
    {
        NewState = ECharacterVisualState::Focused;
    }
    
    CurrentVisualState = NewState;
}

void AAvatarCharacter::UpdateMaterials()
{
    if (!BodyMesh) return;
    
    FLinearColor TeamColor = GetTeamColor();
    float StressLevel = GetStressLevel();
    float FocusLevel = GetFocusLevel();
    float PulseIntensity = GetWorld() ? FMath::Sin(GetWorld()->GetTimeSeconds() * 2.0f) * 0.5f + 0.5f : 0.5f;
    
    // Update body material
    if (DynamicBodyMaterial)
    {
        DynamicBodyMaterial->SetVectorParameterValue(ParamTeamColor, TeamColor);
        DynamicBodyMaterial->SetScalarParameterValue(ParamStressLevel, StressLevel);
        DynamicBodyMaterial->SetScalarParameterValue(ParamFocusLevel, FocusLevel);
        DynamicBodyMaterial->SetScalarParameterValue(ParamPulseIntensity, PulseIntensity);
        
        // Convert enum to float for material
        int32 StateInt = static_cast<int32>(CurrentVisualState);
        DynamicBodyMaterial->SetScalarParameterValue(ParamVisualState, static_cast<float>(StateInt));
    }
}

void AAvatarCharacter::UpdateParticleEffects()
{
    if (!StressParticleComponent || !FocusAuraComponent) return;
    
    float StressLevel = GetStressLevel();
    float FocusLevel = GetFocusLevel();
    
    // Stress particles - activate when stress exceeds threshold
    if (StressLevel > StressThresholdForParticles)
    {
        if (!StressParticleComponent->IsActive())
        {
            StressParticleComponent->ActivateSystem(true);
        }
        
        // Scale particle spawn rate with stress level
        if (StressParticleComponent->Template)
        {
            float SpawnRateScale = FMath::Clamp(StressLevel / StressThresholdForParticles, 0.5f, 2.0f);
            StressParticleComponent->SetFloatParameter(TEXT("SpawnRateScale"), SpawnRateScale);
        }
    }
    else
    {
        if (StressParticleComponent->IsActive())
        {
            StressParticleComponent->DeactivateSystem();
        }
    }
    
    // Focus aura - activate when focus exceeds threshold
    if (FocusLevel > FocusThresholdForAura)
    {
        if (!FocusAuraComponent->IsActive())
        {
            FocusAuraComponent->ActivateSystem(true);
        }
        
        // Scale aura intensity with focus level
        if (FocusAuraComponent->Template)
        {
            float AuraIntensity = FMath::Clamp(FocusLevel / FocusThresholdForAura, 0.5f, 2.0f);
            FocusAuraComponent->SetFloatParameter(TEXT("AuraIntensity"), AuraIntensity);
        }
    }
    else
    {
        if (FocusAuraComponent->IsActive())
        {
            FocusAuraComponent->DeactivateSystem();
        }
    }
}

void AAvatarCharacter::UpdatePostProcessing()
{
    if (!PostProcessComponent) return;
    
    float StressLevel = GetStressLevel();
    float FocusLevel = GetFocusLevel();
    
    // Calculate blend weight based on visual state
    float BlendWeight = 0.0f;
    
    switch (CurrentVisualState)
    {
        case ECharacterVisualState::Normal:
            BlendWeight = 0.0f;
            break;
        case ECharacterVisualState::Focused:
            BlendWeight = FocusLevel * 0.3f; // Subtle effect for focus
            break;
        case ECharacterVisualState::Stressed:
            BlendWeight = 0.5f + StressLevel * 0.5f; // Stronger effect for stress
            break;
        case ECharacterVisualState::Interacting:
            BlendWeight = 0.2f;
            break;
        default:
            BlendWeight = 0.0f;
    }
    
    PostProcessComponent->BlendWeight = BlendWeight;
}

// ============== Helper Functions ==============

FLinearColor AAvatarCharacter::GetTeamColor() const
{
    switch (Team)
    {
        case ECharacterTeam::Neutral:
            return FLinearColor(0.7f, 0.7f, 0.7f, 1.0f); // Gray
        case ECharacterTeam::TeamA:
            return FLinearColor(0.2f, 0.6f, 1.0f, 1.0f); // Blue
        case ECharacterTeam::TeamB:
            return FLinearColor(1.0f, 0.4f, 0.2f, 1.0f); // Orange
        case ECharacterTeam::TeamC:
            return FLinearColor(0.3f, 0.8f, 0.3f, 1.0f); // Green
        default:
            return FLinearColor(0.7f, 0.7f, 0.7f, 1.0f); // Gray
    }
}

float AAvatarCharacter::GetStressLevel() const
{
    if (CognitiveState)
    {
        return CognitiveState->Stress;
    }
    return 0.0f;
}

float AAvatarCharacter::GetFocusLevel() const
{
    if (CognitiveState)
    {
        return CognitiveState->Focus;
    }
    return 0.0f;
}