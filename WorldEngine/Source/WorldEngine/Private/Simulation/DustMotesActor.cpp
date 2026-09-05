#include "Simulation/DustMotesActor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

ADustMotesActor::ADustMotesActor()
{
    PrimaryActorTick.bCanEverTick = false;
    DustMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DustMesh"));
    RootComponent = DustMesh;
    DustMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    DustParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DustParticles"));
    DustParticles->SetupAttachment(RootComponent);
    DustParticles->bAutoActivate = true;
}

void ADustMotesActor::BeginPlay()
{
    Super::BeginPlay();

    if (DustTemplate && DustParticles)
    {
        DustParticles->SetTemplate(DustTemplate);
    }
}

void ADustMotesActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
