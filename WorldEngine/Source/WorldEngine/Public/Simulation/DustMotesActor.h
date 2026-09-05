#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "DustMotesActor.generated.h"

UCLASS()
class WORLDENGINE_API ADustMotesActor : public AActor
{
    GENERATED_BODY()
public:
    ADustMotesActor();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dust")
    UStaticMeshComponent* DustMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dust")
    UParticleSystemComponent* DustParticles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dust")
    float DustDensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dust")
    float TimeOfDay = 8.5f;

    /** Optional particle template used by NLTWorkplaceEnvironmentSubsystem */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dust")
    TObjectPtr<UParticleSystem> DustTemplate;
};
