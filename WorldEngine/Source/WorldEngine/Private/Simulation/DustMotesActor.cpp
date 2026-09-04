#include "Simulation/DustMotesActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"

ADustMotesActor::ADustMotesActor()
{
    // Create the particle system component
    DustParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DustParticles"));
    DustParticles->bAutoActivate = false;
    DustParticles->SetVisibility(false);

    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // Load default dust particle template
    static ConstructorHelpers::FObjectFinder<UParticleSystem> DustParticleAsset(
        TEXT("/Engine/Effects/Tutorial/Dust.ParticleSystem"));
    if (DustParticleAsset.Succeeded())
    {
        DustTemplate = DustParticleAsset.Object;
        DustParticles->SetTemplate(DustTemplate);
    }
}