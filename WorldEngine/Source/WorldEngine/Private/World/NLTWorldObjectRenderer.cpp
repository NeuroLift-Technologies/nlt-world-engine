#include "World/NLTWorldObjectRenderer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

ANLTWorldObjectRenderer::ANLTWorldObjectRenderer()
{
	PrimaryActorTick.bCanEverTick = false;

	BuildingInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BuildingInstances"));
	RootComponent = BuildingInstances;

	RoadInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RoadInstances"));
	RoadInstances->SetupAttachment(RootComponent);

	// Default cube mesh for buildings
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeMesh.Succeeded())
	{
		BuildingInstances->SetStaticMesh(CubeMesh.Object);
		RoadInstances->SetStaticMesh(CubeMesh.Object);
	}

	BuildingHeightScale = 3.0f;
	bRenderDistricts = true;
	bRenderRoads = true;
	bRenderBuildings = true;
}

void ANLTWorldObjectRenderer::BeginPlay()
{
	Super::BeginPlay();
}

void ANLTWorldObjectRenderer::BuildFromWorld(const FNLTWorldGenerationResult& WorldResult)
{
	ClearWorld();

	if (bRenderBuildings)
		RenderBuildings(WorldResult.Buildings);

	if (bRenderRoads)
		RenderRoads(WorldResult.RoadPoints, 200.0f);

	if (bRenderDistricts)
		RenderDistricts(WorldResult.Districts);
}

void ANLTWorldObjectRenderer::ClearWorld()
{
	if (BuildingInstances)
		BuildingInstances->ClearInstances();
	if (RoadInstances)
		RoadInstances->ClearInstances();

	for (UStaticMeshComponent* Mesh : DistrictMeshes)
	{
		if (Mesh) Mesh->DestroyComponent();
	}
	DistrictMeshes.Empty();
}

void ANLTWorldObjectRenderer::RenderBuildings(const TArray<FNLTGeneratedBuilding>& Buildings)
{
	if (!BuildingInstances) return;

	for (const FNLTGeneratedBuilding& Building : Buildings)
	{
		FVector Pos = Building.Transform.GetLocation();
		FVector Scale = Building.Transform.GetScale3D();

		// Determine building dimensions from type
		float Width = 200.0f * Scale.X;
		float Depth = 200.0f * Scale.Y;
		float Height = 0.0f;

		if (Building.BuildingType == TEXT("Office"))
			Height = 400.0f * BuildingHeightScale;
		else if (Building.BuildingType == TEXT("Apartment"))
			Height = 300.0f * BuildingHeightScale;
		else if (Building.BuildingType == TEXT("Shop"))
			Height = 120.0f * BuildingHeightScale;
		else if (Building.BuildingType == TEXT("Factory"))
			Height = 200.0f * BuildingHeightScale;
		else
			Height = 100.0f * BuildingHeightScale;

		FVector BuildingScale(Width / 50.0f, Depth / 50.0f, Height / 50.0f);
		FTransform InstanceTransform(
			Building.Transform.GetRotation(),
			FVector(Pos.X, Pos.Y, Height * 0.5f),
			BuildingScale);

		BuildingInstances->AddInstance(InstanceTransform);

		// Apply per-instance material
			UMaterialInterface* Mat = GetBuildingMaterial(Building.BuildingType);
			if (Mat)
			{
				UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(Mat, BuildingInstances);
				BuildingInstances->SetMaterial(BuildingInstances->GetNumInstances() - 1, DynMat);
			}
	}
}

void ANLTWorldObjectRenderer::RenderRoads(const TArray<FTransform>& RoadPoints, float RoadWidth)
{
	if (!RoadInstances) return;

	for (const FTransform& RoadPoint : RoadPoints)
	{
		FVector Pos = RoadPoint.GetLocation();
		FRotator Rot = RoadPoint.GetRotation().Rotator();

		FVector RoadScale(RoadWidth / 50.0f, 400.0f / 50.0f, 0.5f);
		FTransform InstanceTransform(	Rot, FVector(Pos.X, Pos.Y, 2.0f), RoadScale);
		RoadInstances->AddInstance(InstanceTransform);
	}
}

void ANLTWorldObjectRenderer::RenderDistricts(const TArray<FNLTGeneratedDistrict>& Districts)
{
	UWorld* World = GetWorld();
	if (!World) return;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(TEXT("/Engine/BasicShapes/Plane"));
	if (!PlaneMesh.Succeeded()) return;

	for (const FNLTGeneratedDistrict& District : Districts)
	{
		UStaticMeshComponent* DistrictMesh = NewObject<UStaticMeshComponent>(this);
		DistrictMesh->SetStaticMesh(PlaneMesh.Object);
		DistrictMesh->SetWorldLocation(FVector(District.Center.X, District.Center.Y, 1.0f));
		DistrictMesh->SetWorldScale3D(FVector(District.Radius / 50.0f, District.Radius / 50.0f, 1.0f));
		DistrictMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DistrictMesh->SetCastShadow(false);
		DistrictMesh->RegisterComponent();

		UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(DistrictMaterial, DistrictMesh);
		if (DynMat)
		{
			DynMat->SetVectorParameterValue(TEXT("DistrictColor"), GetDistrictColor(District.DistrictType));
			DynMat->SetScalarParameterValue(TEXT("Opacity"), 0.3f);
			DistrictMesh->SetMaterial(0, DynMat);
		}

		DistrictMeshes.Add(DistrictMesh);
	}
}

UMaterialInterface* ANLTWorldObjectRenderer::GetBuildingMaterial(FName BuildingType) const
{
	if (BuildingType == TEXT("Apartment")) return ResidentialMaterial;
	if (BuildingType == TEXT("Shop")) return CommercialMaterial;
	if (BuildingType == TEXT("Factory")) return IndustrialMaterial;
	if (BuildingType == TEXT("Park")) return ParkMaterial;
	if (BuildingType == TEXT("Office")) return OfficeMaterial;
	return nullptr;
}

FLinearColor ANLTWorldObjectRenderer::GetDistrictColor(FName DistrictType) const
{
	if (DistrictType == TEXT("Residential")) return FLinearColor(0.2f, 0.6f, 0.3f, 0.3f);
	if (DistrictType == TEXT("Commercial")) return FLinearColor(0.2f, 0.4f, 0.8f, 0.3f);
	if (DistrictType == TEXT("Industrial")) return FLinearColor(0.7f, 0.5f, 0.2f, 0.3f);
	if (DistrictType == TEXT("Park")) return FLinearColor(0.1f, 0.7f, 0.2f, 0.3f);
	return FLinearColor(0.5f, 0.5f, 0.5f, 0.3f);
}
