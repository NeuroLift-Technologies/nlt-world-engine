#include "Simulation/DustMotesComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

UDustMotesComponent::UDustMotesComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	DustDensity = 0.5f;
	DriftSpeed = 1.0f;
	DustColor = FLinearColor(0.9f, 0.85f, 0.7f, 1.0f);
	VolumeSize = FVector(2000.0f, 2000.0f, 500.0f);
}

void UDustMotesComponent::BeginPlay()
{
	Super::BeginPlay();

	// Try the specified template first
	if (DustTemplate)
	{
		DustParticles = NewObject<UParticleSystemComponent>(GetOwner());
		DustParticles->SetTemplate(DustTemplate);
		DustParticles->bAutoActivate = false;
		DustParticles->RegisterComponent();
	}
	else
	{
		// Try engine starter content particles
		static ConstructorHelpers::FObjectFinder<UParticleSystem> DustFinder(
			TEXT("/Game/VFX/Workplace/NS_DustMotes.NS_DustMotes"));
		if (DustFinder.Succeeded())
		{
			DustTemplate = DustFinder.Object;
			DustParticles = NewObject<UParticleSystemComponent>(GetOwner());
			DustParticles->SetTemplate(DustTemplate);
			DustParticles->bAutoActivate = false;
			DustParticles->RegisterComponent();
		}
		else
		{
			// Last resort: try the engine's built-in particle
			static ConstructorHelpers::FObjectFinder<UParticleSystem> SparkFinder(
				TEXT("/Engine/EngineResources/DefaultPawn/DefaultPawn_ParticleSystem.DefaultPawn_ParticleSystem"));
			if (SparkFinder.Succeeded())
			{
				DustParticles = NewObject<UParticleSystemComponent>(GetOwner());
				DustParticles->SetTemplate(SparkFinder.Object);
				DustParticles->bAutoActivate = false;
				DustParticles->RegisterComponent();
			}
		}
	}

	if (DustParticles)
	{
		DustParticles->SetFloatParameter(TEXT("SpawnRate"), DustDensity * 50.0f);
		DustParticles->SetVectorParameter(TEXT("Color"), FVector(DustColor.R, DustColor.G, DustColor.B));
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
		DustParticles->Activate();
	else
		DustParticles->Deactivate();
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
