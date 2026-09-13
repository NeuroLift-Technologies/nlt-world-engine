#include "Agents/NLTAvatarVisualComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

UNLTAvatarVisualComponent::UNLTAvatarVisualComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bShowStatusRing = true;
	bShowParticles = true;
	MaxGlowIntensity = 3.0f;

	// Load the status ring mesh in the constructor (ConstructorHelpers is
	// only valid here, not in BeginPlay / CreateStatusRing).
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(
		TEXT("/Engine/BasicShapes/Cylinder"));
	if (CylinderMesh.Succeeded())
	{
		StatusRingMeshAsset = CylinderMesh.Object;
	}
}

void UNLTAvatarVisualComponent::BeginPlay()
{
	Super::BeginPlay();

	// Look for a SkeletalMeshComponent (rigged character).
	SkeletalMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	// Fallback: look for a StaticMeshComponent (SimBody procedural body).
	if (!SkeletalMesh)
	{
		StaticMeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	}

	if (bShowStatusRing)
		CreateStatusRing();
	if (bShowParticles)
		CreateParticleComponents();
}

void UNLTAvatarVisualComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Smooth glow interpolation
	if (FMath::Abs(CurrentGlow - TargetGlow) > 0.01f)
	{
		CurrentGlow = FMath::FInterpTo(CurrentGlow, TargetGlow, DeltaTime, 4.0f);
		UMaterialInstanceDynamic* Mat = GetAvatarMaterial();
		if (Mat)
			Mat->SetScalarParameterValue(TEXT("EmissiveGlow"), CurrentGlow);
	}

	// Animate status ring rotation
	if (StatusRingMesh && bShowStatusRing)
	{
		FRotator Rot = StatusRingMesh->GetRelativeRotation();
		Rot.Yaw += DeltaTime * 30.0f;
		StatusRingMesh->SetRelativeRotation(Rot);
	}
}

void UNLTAvatarVisualComponent::UpdateFromCognitiveState(float Focus, float Stress, float CognitiveLoad, FName EmotionalState)
{
	// Determine target glow based on state
	if (Stress > 0.7f)
	{
		TargetGlow = MaxGlowIntensity;
		SetStatusRingColor(StressGlowColor);
		if (StressParticles && !StressParticles->IsActive()) StressParticles->Activate();
		if (FocusParticles && FocusParticles->IsActive()) FocusParticles->Deactivate();
		if (BurnoutParticles && BurnoutParticles->IsActive()) BurnoutParticles->Deactivate();
	}
	else if (Focus > 0.7f)
	{
		TargetGlow = MaxGlowIntensity * 0.7f;
		SetStatusRingColor(FocusGlowColor);
		if (StressParticles && StressParticles->IsActive()) StressParticles->Deactivate();
		if (FocusParticles && !FocusParticles->IsActive()) FocusParticles->Activate();
		if (BurnoutParticles && BurnoutParticles->IsActive()) BurnoutParticles->Deactivate();
	}
	else if (CognitiveLoad > 0.8f)
	{
		TargetGlow = MaxGlowIntensity * 0.5f;
		SetStatusRingColor(BurnoutGlowColor);
		if (StressParticles && StressParticles->IsActive()) StressParticles->Deactivate();
		if (FocusParticles && FocusParticles->IsActive()) FocusParticles->Deactivate();
		if (BurnoutParticles && !BurnoutParticles->IsActive()) BurnoutParticles->Activate();
	}
	else
	{
		TargetGlow = 0.5f;
		SetStatusRingColor(FLinearColor(0.2f, 0.8f, 0.4f, 1.0f)); // Green = idle
		if (StressParticles && StressParticles->IsActive()) StressParticles->Deactivate();
		if (FocusParticles && FocusParticles->IsActive()) FocusParticles->Deactivate();
		if (BurnoutParticles && BurnoutParticles->IsActive()) BurnoutParticles->Deactivate();
	}
}

void UNLTAvatarVisualComponent::SetStatusRingColor(const FLinearColor& Color)
{
	if (StatusRingMaterial)
		StatusRingMaterial->SetVectorParameterValue(TEXT("RingColor"), Color);
}

void UNLTAvatarVisualComponent::SetEmissiveGlow(float Intensity)
{
	TargetGlow = Intensity;
}

void UNLTAvatarVisualComponent::CreateStatusRing()
{
	AActor* Owner = GetOwner();
	if (!Owner || !StatusRingMeshAsset) return;

	StatusRingMesh = NewObject<UStaticMeshComponent>(Owner, TEXT("StatusRing"));
	StatusRingMesh->SetStaticMesh(StatusRingMeshAsset);
	StatusRingMesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 0.05f));
	StatusRingMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	StatusRingMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StatusRingMesh->SetCastShadow(false);

	// Attach to owner root so the ring follows the avatar transform.
	StatusRingMesh->SetupAttachment(Owner->GetRootComponent());
	StatusRingMesh->RegisterComponent();

	StatusRingMaterial = UMaterialInstanceDynamic::Create(StatusRingMesh->GetMaterial(0), StatusRingMesh);
	StatusRingMesh->SetMaterial(0, StatusRingMaterial);
}

void UNLTAvatarVisualComponent::CreateParticleComponents()
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	if (StressParticleTemplate)
	{
		StressParticles = NewObject<UParticleSystemComponent>(Owner, TEXT("StressFX"));
		StressParticles->SetTemplate(StressParticleTemplate);
		StressParticles->bAutoActivate = false;
		StressParticles->SetupAttachment(Owner->GetRootComponent());
		StressParticles->RegisterComponent();
	}

	if (FocusParticleTemplate)
	{
		FocusParticles = NewObject<UParticleSystemComponent>(Owner, TEXT("FocusFX"));
		FocusParticles->SetTemplate(FocusParticleTemplate);
		FocusParticles->bAutoActivate = false;
		FocusParticles->SetupAttachment(Owner->GetRootComponent());
		FocusParticles->RegisterComponent();
	}

	if (BurnoutParticleTemplate)
	{
		BurnoutParticles = NewObject<UParticleSystemComponent>(Owner, TEXT("BurnoutFX"));
		BurnoutParticles->SetTemplate(BurnoutParticleTemplate);
		BurnoutParticles->bAutoActivate = false;
		BurnoutParticles->SetupAttachment(Owner->GetRootComponent());
		BurnoutParticles->RegisterComponent();
	}
}

void UNLTAvatarVisualComponent::UpdateFromEmotion(ENLTEmotionState Emotion, ENLTAnimationState AnimState, float Intensity)
{
	// Map emotion → status ring color + particle state.
	// Intensity (0–1) dims the glow for low-intensity emotions.
	const float EffectiveGlow = FMath::Max(0.1f, Intensity) * MaxGlowIntensity;

	FLinearColor RingColor;
	FString EmotionName;

	switch (Emotion)
	{
	case ENLTEmotionState::Neutral:
		TargetGlow = 0.3f * EffectiveGlow;
		RingColor = FLinearColor(0.2f, 0.8f, 0.4f, 1.0f);
		EmotionName = TEXT("Neutral");
		break;
	case ENLTEmotionState::Focused:
	case ENLTEmotionState::Working:
		TargetGlow = 0.7f * EffectiveGlow;
		RingColor = FocusGlowColor;
		EmotionName = TEXT("Focused");
		break;
	case ENLTEmotionState::Struggling:
		TargetGlow = 0.6f * EffectiveGlow;
		RingColor = StressGlowColor;
		EmotionName = TEXT("Struggling");
		break;
	case ENLTEmotionState::Overwhelmed:
		TargetGlow = 1.0f * EffectiveGlow;
		RingColor = StressGlowColor;
		EmotionName = TEXT("Overwhelmed");
		break;
	case ENLTEmotionState::Drifting:
		TargetGlow = 0.3f * EffectiveGlow;
		RingColor = FLinearColor(0.5f, 0.5f, 0.8f, 1.0f);
		EmotionName = TEXT("Drifting");
		break;
	case ENLTEmotionState::Hyperfocus:
		TargetGlow = 0.8f * EffectiveGlow;
		RingColor = FLinearColor(0.0f, 0.8f, 1.0f, 1.0f);
		EmotionName = TEXT("Hyperfocus");
		break;
	case ENLTEmotionState::Coached:
		TargetGlow = 0.6f * EffectiveGlow;
		RingColor = FLinearColor(0.6f, 0.4f, 1.0f, 1.0f);
		EmotionName = TEXT("Coached");
		break;
	case ENLTEmotionState::Fatigued:
		TargetGlow = 0.2f * EffectiveGlow;
		RingColor = BurnoutGlowColor;
		EmotionName = TEXT("Fatigued");
		break;
	case ENLTEmotionState::Celebrating:
		TargetGlow = 1.0f * EffectiveGlow;
		RingColor = FLinearColor(1.0f, 0.8f, 0.2f, 1.0f);
		EmotionName = TEXT("Celebrating");
		break;
	default:
		TargetGlow = 0.3f * EffectiveGlow;
		RingColor = FLinearColor(0.2f, 0.8f, 0.4f, 1.0f);
		EmotionName = TEXT("Unknown");
		break;
	}

	SetStatusRingColor(RingColor);
}

UMaterialInstanceDynamic* UNLTAvatarVisualComponent::GetAvatarMaterial()
{
	if (AvatarMaterialInstance) return AvatarMaterialInstance;

	// Try SkeletalMesh first (rigged character)
	if (SkeletalMesh)
	{
		UMaterialInterface* BaseMat = SkeletalMesh->GetMaterial(0);
		if (BaseMat)
		{
			AvatarMaterialInstance = UMaterialInstanceDynamic::Create(BaseMat, SkeletalMesh);
			SkeletalMesh->SetMaterial(0, AvatarMaterialInstance);
			return AvatarMaterialInstance;
		}
	}

	// Fallback: StaticMesh (SimBody procedural body)
	if (StaticMeshComp)
	{
		UMaterialInterface* BaseMat = StaticMeshComp->GetMaterial(0);
		if (BaseMat)
		{
			AvatarMaterialInstance = UMaterialInstanceDynamic::Create(BaseMat, StaticMeshComp);
			StaticMeshComp->SetMaterial(0, AvatarMaterialInstance);
			return AvatarMaterialInstance;
		}
	}

	return nullptr;
}
