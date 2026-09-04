#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DustMotesActor.generated.h"

UCLASS()
class WORLDENGINE_API ADustMotesActor : public AActor
{
    GENERATED_BODY()

public:
    ADustMotesActor();

    /** The dust motes particle system component */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dust Motes")
    UParticleSystemComponent* DustParticles;

    /** The dust particle template - assigned from editor or content browser */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dust Motes")
    UParticleSystem* DustTemplate;

    /** Enable/disable the dust effect globally */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dust Motes")
    bool bActive = true;
};