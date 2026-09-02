#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "Agents/NLTAgentFragments.h"
#include "MassMovementFragments.h"
#include "NLTAgentTrait.generated.h"

UCLASS(MinimalAPI, meta = (DisplayName = "NLTAgent"))
class UNLTAgentTrait : public UMassEntityTraitBase
{
    GENERATED_BODY()

protected:
    virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;

    UPROPERTY(Category = "NLTAgent", EditAnywhere)
    FName ProfileId = NAME_None;

    UPROPERTY(Category = "NLTAgent", EditAnywhere)
    ENLTAgentRole Role = ENLTAgentRole::Avatar;

    UPROPERTY(Category = "NLTAgent", EditAnywhere)
    FString DisplayName;

    UPROPERTY(Category = "NLTAgent", EditAnywhere)
    FVector InitialPosition = FVector::ZeroVector;

    UPROPERTY(Category = "NLTAgent", EditAnywhere)
    bool bCanMove = true;

    UPROPERTY(Category = "NLTAgent", EditAnywhere, meta = (EditCondition = "bCanMove"))
    float MaxSpeed = 200.0f;
};

