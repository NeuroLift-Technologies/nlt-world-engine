#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "MassEntityQuery.h"
#include "MassEntityManager.h"
#include "MassEntitySubsystem.h"
#include "NLTAgentVisualizer.generated.h"

UCLASS()
class ANLTAgentVisualizer : public AActor
{
    GENERATED_BODY()

public:
    ANLTAgentVisualizer();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualization")
    UStaticMesh* AgentMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualization")
    UMaterialInterface* AgentMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualization")
    float AgentScale = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visualization")
    bool bShowDebugText = true;

private:
    UPROPERTY()
    UInstancedStaticMeshComponent* ISMComponent;

    FMassEntityQuery EntityQuery;

    void SetupQuery();
    void UpdateVisuals();
};
