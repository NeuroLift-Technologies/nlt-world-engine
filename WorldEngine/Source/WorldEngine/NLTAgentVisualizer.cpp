#include "NLTAgentVisualizer.h"
#include "Public/Agents/NLTAgentFragments.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/Material.h"
#include "MassEntityManager.h"
#include "MassEntitySubsystem.h"
#include "MassExecutionContext.h"

ANLTAgentVisualizer::ANLTAgentVisualizer()
{
    PrimaryActorTick.bCanEverTick = true;

    ISMComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMComponent"));
    RootComponent = ISMComponent;

    // Default mesh: low-poly stylized sim body (already authored at ~179.5cm,
    // feet flat at Z=0). Falls back to the engine cube if the kit asset is
    // missing so the visualizer still renders something.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SimBodyMesh(TEXT("/Game/Kits/SimBody/SM_SimBody_Base"));
    if (SimBodyMesh.Succeeded())
    {
        AgentMesh = SimBodyMesh.Object;
    }
    else
    {
        static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
        if (CubeMesh.Succeeded())
        {
            AgentMesh = CubeMesh.Object;
        }
    }

    if (AgentMesh)
    {
        ISMComponent->SetStaticMesh(AgentMesh);
    }

    AgentScale = 1.0f;
    bShowDebugText = true;
}

void ANLTAgentVisualizer::BeginPlay()
{
    Super::BeginPlay();
    SetupQuery();
}

void ANLTAgentVisualizer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateVisuals();
}

void ANLTAgentVisualizer::SetupQuery()
{
    UWorld* World = GetWorld();
    if (!World) return;

    UMassEntitySubsystem* EntitySub = World->GetSubsystem<UMassEntitySubsystem>();
    if (!EntitySub) return;

    // A FMassEntityQuery must be initialized with the entity manager before
    // fragment requirements can be added (asserts on bInitialized otherwise).
    EntityQuery.Initialize(EntitySub->GetMutableEntityManager().AsShared());

    EntityQuery.AddRequirement<FNLTAgentIdentityFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
    EntityQuery.AddRequirement<FNLTAgentLocationFragment>(EMassFragmentAccess::ReadOnly, EMassFragmentPresence::All);
}

void ANLTAgentVisualizer::UpdateVisuals()
{
    UWorld* World = GetWorld();
    if (!World) return;

    UMassEntitySubsystem* EntitySub = World->GetSubsystem<UMassEntitySubsystem>();
    if (!EntitySub) return;

    FMassEntityManager& EntityManager = EntitySub->GetMutableEntityManager();

    // Clear existing instances
    ISMComponent->ClearInstances();

    // Build instance transforms from entity positions
    TArray<FTransform> InstanceTransforms;

    FMassExecutionContext Context(EntityManager);
    const float LocalAgentScale = AgentScale;
    EntityQuery.ForEachEntityChunk(EntityManager, Context, [&InstanceTransforms, LocalAgentScale](FMassExecutionContext& Context)
    {
        const int32 NumEntities = Context.GetNumEntities();
        const TConstArrayView<FNLTAgentLocationFragment> Locations = Context.GetFragmentView<FNLTAgentLocationFragment>();

        for (int32 i = 0; i < NumEntities; i++)
        {
            FTransform T;
            T.SetLocation(Locations[i].Position);
            // AgentMesh is authored at real-world scale (cm), so use AgentScale
            // directly (1.0 = life size) rather than the old 100x cube hack.
            T.SetScale3D(FVector(LocalAgentScale));
            InstanceTransforms.Add(T);
        }
    });

    // Add instances
    for (const FTransform& T : InstanceTransforms)
    {
        ISMComponent->AddInstance(T);
    }

    if (bShowDebugText)
    {
        UE_LOG(LogTemp, Log, TEXT("Visualizer: rendering %d agents"), InstanceTransforms.Num());
    }
}
