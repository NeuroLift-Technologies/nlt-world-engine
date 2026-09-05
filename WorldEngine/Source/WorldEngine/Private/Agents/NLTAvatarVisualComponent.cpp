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

	SkeletalMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));

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

UMaterialInstanceDynamic* UNLTAvatarVisualComponent::GetAvatarMaterial()
{
	if (AvatarMaterialInstance) return AvatarMaterialInstance;
	if (!SkeletalMesh) return nullptr;

	UMaterialInterface* BaseMat = SkeletalMesh->GetMaterial(0);
	if (!BaseMat) return nullptr;

	AvatarMaterialInstance = UMaterialInstanceDynamic::Create(BaseMat, SkeletalMesh);
	SkeletalMesh->SetMaterial(0, AvatarMaterialInstance);
	return AvatarMaterialInstance;
}
