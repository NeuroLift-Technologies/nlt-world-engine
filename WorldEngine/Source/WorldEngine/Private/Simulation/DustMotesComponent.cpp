#include "Simulation/DustMotesComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

UDustMotesComponent::UDustMotesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DustDensity = 0.5f;
	DriftSpeed = 1.0f;
	DustColor = FLinearColor(0.9f, 0.85f, 0.7f, 1.0f);
	VolumeSize = FVector(2000.0f, 2000.0f, 500.0f);
	bIsVisible = true;
}

void UDustMotesComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner) return;

	// Use the assigned template, otherwise fall back to project/engine assets.
	// Note: asset lookup happens at runtime, so ConstructorHelpers is NOT used here
	// (it is only valid inside the class constructor). Loop until we have a component.
	UParticleSystem* EffectiveTemplate = DustTemplate;
	if (!EffectiveTemplate)
	{
		EffectiveTemplate = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/VFX/Workplace/NS_DustMotes.NS_DustMotes"));
	}
	if (!EffectiveTemplate)
	{
		EffectiveTemplate = LoadObject<UParticleSystem>(nullptr, TEXT("/Engine/Effects/Tutorial/Dust.ParticleSystem"));
	}
	if (!EffectiveTemplate)
	{
		EffectiveTemplate = LoadObject<UParticleSystem>(nullptr, TEXT("/Engine/EngineResources/DefaultPawn/DefaultPawn_ParticleSystem.DefaultPawn_ParticleSystem"));
	}

	DustParticles = NewObject<UParticleSystemComponent>(Owner);
	if (EffectiveTemplate)
	{
		DustParticles->SetTemplate(EffectiveTemplate);
		DustTemplate = EffectiveTemplate;
	}
	DustParticles->bAutoActivate = false;
	DustParticles->SetupAttachment(Owner->GetRootComponent());
	DustParticles->RegisterComponent();

	if (EffectiveTemplate)
	{
		DustParticles->SetFloatParameter(TEXT("SpawnRate"), DustDensity * 50.0f);
		DustParticles->SetVectorParameter(TEXT("Color"), FVector(DustColor.R, DustColor.G, DustColor.B));
		DustParticles->SetVisibility(bIsVisible);
		if (bIsVisible)
		{
			DustParticles->ActivateSystem(true);
		}
	}
}

void UDustMotesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!DustParticles || !DustParticles->IsActive()) return;

	// Gentle drift rotation for visual variety
	FRotator DustRot = DustParticles->GetRelativeRotation();
	DustRot.Yaw += DeltaTime * DriftSpeed * 5.0f;
	DustParticles->SetRelativeRotation(DustRot);

	// Update spawn rate based on density
	DustParticles->SetFloatParameter(TEXT("SpawnRate"), DustDensity * 50.0f);
}

void UDustMotesComponent::SetVisibility(bool bVisible)
{
	bIsVisible = bVisible;
	if (!DustParticles) return;

	DustParticles->SetVisibility(bVisible);
	if (bVisible)
		DustParticles->ActivateSystem(true);
	else
		DustParticles->DeactivateSystem();
}

void UDustMotesComponent::SetDensity(float Density)
{
	DustDensity = FMath::Clamp(Density, 0.0f, 1.0f);
	if (DustParticles)
		DustParticles->SetFloatParameter(TEXT("SpawnRate"), DustDensity * 50.0f);
}

void UDustMotesComponent::SetParticleSystem(UParticleSystem* Template)
{
	DustTemplate = Template;
	if (DustParticles)
		DustParticles->SetTemplate(Template);
}

void UDustMotesComponent::SetDriftSpeed(float Speed)
{
	DriftSpeed = Speed;
}

void UDustMotesComponent::SetColorTint(const FLinearColor& Color)
{
	DustColor = Color;
	if (DustParticles)
		DustParticles->SetVectorParameter(TEXT("Color"), FVector(Color.R, Color.G, Color.B));
}

bool UDustMotesComponent::GetVisibility() const
{
	return bIsVisible;
}

float UDustMotesComponent::GetDensity() const
{
	return DustDensity;
}

void UDustMotesComponent::CreateProceduralDustSystem()
{
	// Placeholder for procedural particle creation if needed
}
