#include "Simulation/DustMotesActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

ADustMotesActor::ADustMotesActor()
{
    // Create and root the particle system component
    DustParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DustParticles"));
    SetRootComponent(DustParticles);
    DustParticles->bAutoActivate = false;
    DustParticles->SetVisibility(false);

    // Set this actor to not need tick by default
    PrimaryActorTick.bCanEverTick = false;
}

void ADustMotesActor::BeginPlay()
{
    Super::BeginPlay();

    // Apply the assigned template if present, falling back to the engine dust asset
    UParticleSystem* EffectiveTemplate = DustTemplate;
    if (!EffectiveTemplate)
    {
        EffectiveTemplate = LoadObject<UParticleSystem>(nullptr, TEXT("/Engine/Effects/Tutorial/Dust.ParticleSystem"));
    }
    if (EffectiveTemplate)
    {
        SetDustTemplate(EffectiveTemplate);
    }

    // Activate now that the world is ready (SetVisibility alone does not activate)
    if (bActive && DustParticles && DustParticles->Template)
    {
        DustParticles->SetVisibility(true);
        DustParticles->ActivateSystem(true);
    }
    else if (DustParticles)
    {
        DustParticles->SetVisibility(false);
    }
}

void ADustMotesActor::SetDustTemplate(UParticleSystem* InTemplate)
{
    DustTemplate = InTemplate;
    if (DustParticles)
    {
        DustParticles->SetTemplate(InTemplate);
    }
}
