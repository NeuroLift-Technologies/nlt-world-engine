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

    // Default mesh (simple cube)
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMesh.Succeeded())
    {
        AgentMesh = CubeMesh.Object;
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
    EntityQuery.ForEachEntityChunk(EntityManager, Context, [&InstanceTransforms](FMassExecutionContext& Context)
    {
        const int32 NumEntities = Context.GetNumEntities();
        const TConstArrayView<FNLTAgentLocationFragment> Locations = Context.GetFragmentView<FNLTAgentLocationFragment>();

        for (int32 i = 0; i < NumEntities; i++)
        {
            FTransform T;
            T.SetLocation(Locations[i].Position);
            T.SetScale3D(FVector(100.0f)); // 100cm cube per agent
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
