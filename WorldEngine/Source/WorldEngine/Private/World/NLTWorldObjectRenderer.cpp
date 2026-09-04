#include "World/NLTWorldObjectRenderer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

ANLTWorldObjectRenderer::ANLTWorldObjectRenderer()
{
	PrimaryActorTick.bCanEverTick = false;

	BuildingHeightScale = 3.0f;
	bRenderDistricts = true;
	bRenderRoads = true;
	bRenderBuildings = true;

	RoadInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RoadInstances"));
	RootComponent = RoadInstances;

	// Pre-load the cube and plane meshes in the constructor. ConstructorHelpers
	// is only valid here (CDO construction), not at runtime in RenderDistricts
	// or GetBuildingISM — both of which run from BeginPlay/BuildFromWorld.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeFinder(TEXT("/Engine/BasicShapes/Cube"));
	if (CubeFinder.Succeeded())
	{
		RoadInstances->SetStaticMesh(CubeFinder.Object);
		CubeMeshCache = NewObject<UStaticMeshComponent>(this, TEXT("CubeMeshCache"));
		CubeMeshCache->SetStaticMesh(CubeFinder.Object);
		CubeMeshCache->SetHiddenInGame(true);
		CubeMeshCache->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CubeMeshCache->RegisterComponent();
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneFinder(TEXT("/Engine/BasicShapes/Plane"));
	if (PlaneFinder.Succeeded())
	{
		PlaneMeshCache = NewObject<UStaticMeshComponent>(this, TEXT("PlaneMeshCache"));
		PlaneMeshCache->SetStaticMesh(PlaneFinder.Object);
		PlaneMeshCache->SetHiddenInGame(true);
		PlaneMeshCache->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlaneMeshCache->RegisterComponent();
	}
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
	for (auto& Pair : BuildingISMs)
	{
		if (Pair.Value)
			Pair.Value->ClearInstances();
	}
	BuildingISMs.Empty();
	if (RoadInstances)
		RoadInstances->ClearInstances();

	for (UStaticMeshComponent* Mesh : DistrictMeshes)
	{
		if (Mesh) Mesh->DestroyComponent();
	}
	DistrictMeshes.Empty();
}

UInstancedStaticMeshComponent* ANLTWorldObjectRenderer::GetBuildingISM(FName BuildingType)
{
	if (UInstancedStaticMeshComponent** Existing = BuildingISMs.Find(BuildingType))
	{
		return *Existing;
	}

	// One ISM per building type so each type carries its own material.
	FName CompName = FName(*FString::Printf(TEXT("BuildingISM_%s"), *BuildingType.ToString()));
	UInstancedStaticMeshComponent* NewISM = NewObject<UInstancedStaticMeshComponent>(this, CompName);
	NewISM->SetupAttachment(RootComponent);
	NewISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NewISM->SetCastShadow(false);

	if (CubeMeshCache)
		NewISM->SetStaticMesh(CubeMeshCache->GetStaticMesh());

	// Assign the type-specific material once on the ISM (not per-instance).
	UMaterialInterface* Mat = GetBuildingMaterial(BuildingType);
	if (!Mat)
	{
		// Fallback: a default dynamic material colored per type so buildings
		// remain visually distinct even with no material asset assigned.
		UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(NewISM->GetMaterial(0), NewISM);
		if (DynMat)
		{
			DynMat->SetVectorParameterValue(TEXT("BaseColor"), GetDistrictColor(BuildingType));
			Mat = DynMat;
		}
	}
	if (Mat)
		NewISM->SetMaterial(0, Mat);

	NewISM->RegisterComponent();
	BuildingISMs.Add(BuildingType, NewISM);
	return NewISM;
}

void ANLTWorldObjectRenderer::RenderBuildings(const TArray<FNLTGeneratedBuilding>& Buildings)
{
	for (const FNLTGeneratedBuilding& Building : Buildings)
	{
		FVector Pos = Building.Transform.GetLocation();
		FVector Scale3D = Building.Transform.GetScale3D();

		float Width = 200.0f * FMath::Max(Scale3D.X, 0.5f);
		float Depth = 200.0f * FMath::Max(Scale3D.Y, 0.5f);
		float Height = 100.0f * BuildingHeightScale;

		if (Building.BuildingType == TEXT("Office"))
			Height = 400.0f * BuildingHeightScale;
		else if (Building.BuildingType == TEXT("Apartment"))
			Height = 300.0f * BuildingHeightScale;
		else if (Building.BuildingType == TEXT("Shop"))
			Height = 120.0f * BuildingHeightScale;
		else if (Building.BuildingType == TEXT("Factory"))
			Height = 200.0f * BuildingHeightScale;

		// UE default cube is 100cm, so scale = dimension / 100.
		FVector BuildingScale(Width / 100.0f, Depth / 100.0f, Height / 100.0f);
		FTransform InstanceTransform(
			Building.Transform.GetRotation(),
			FVector(Pos.X, Pos.Y, Height * 0.5f),
			BuildingScale);

		UInstancedStaticMeshComponent* ISM = GetBuildingISM(Building.BuildingType);
		ISM->AddInstance(InstanceTransform);
	}
}

void ANLTWorldObjectRenderer::RenderRoads(const TArray<FTransform>& RoadPoints, float RoadWidth)
{
	if (!RoadInstances) return;

	for (int32 i = 0; i < RoadPoints.Num(); i++)
	{
		const FVector& Pos = RoadPoints[i].GetLocation();

		FVector Dir(1.0f, 0.0f, 0.0f);
		float RoadLength = 400.0f;
		FVector MidPoint = Pos;

		if (i < RoadPoints.Num() - 1)
		{
			const FVector& NextPos = RoadPoints[i + 1].GetLocation();
			FVector Segment = NextPos - Pos;
			float Dist = Segment.Size();
			if (Dist > 1.0f)
			{
				Dir = Segment / Dist;
				RoadLength = Dist;
				MidPoint = (Pos + NextPos) * 0.5f;
			}
		}

		FRotator Rot = Dir.Rotation();
		// Dir.Rotation() aligns local X with the road direction, so
		// X = length, Y = width (previously swapped).
		FVector RoadScale(RoadLength / 100.0f, RoadWidth / 100.0f, 0.2f);
		FTransform InstanceTransform(Rot, FVector(MidPoint.X, MidPoint.Y, 2.0f), RoadScale);
		RoadInstances->AddInstance(InstanceTransform);
	}
}

void ANLTWorldObjectRenderer::RenderDistricts(const TArray<FNLTGeneratedDistrict>& Districts)
{
	UWorld* World = GetWorld();
	if (!World) return;

	for (const FNLTGeneratedDistrict& District : Districts)
	{
		UStaticMeshComponent* DistrictMesh = NewObject<UStaticMeshComponent>(this);
		if (PlaneMeshCache)
			DistrictMesh->SetStaticMesh(PlaneMeshCache->GetStaticMesh());
		DistrictMesh->SetWorldLocation(FVector(District.Center.X, District.Center.Y, 1.0f));
		// UE plane is 100cm x 100cm, so scale = diameter / 100.
		float Diameter = District.Radius * 2.0f;
		DistrictMesh->SetWorldScale3D(FVector(Diameter / 100.0f, Diameter / 100.0f, 1.0f));
		DistrictMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DistrictMesh->SetCastShadow(false);
		DistrictMesh->RegisterComponent();

		// Use district material or a default colored dynamic material.
		UMaterialInterface* Mat = DistrictMaterial;
		UMaterialInstanceDynamic* AppliedMat = nullptr;
		if (Mat)
			AppliedMat = UMaterialInstanceDynamic::Create(Mat, DistrictMesh);
		if (!AppliedMat)
			AppliedMat = UMaterialInstanceDynamic::Create(DistrictMesh->GetMaterial(0), DistrictMesh);
		if (AppliedMat)
		{
			AppliedMat->SetVectorParameterValue(TEXT("DistrictColor"), GetDistrictColor(District.DistrictType));
			AppliedMat->SetScalarParameterValue(TEXT("Opacity"), 0.3f);
			DistrictMesh->SetMaterial(0, AppliedMat);
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
	if (DistrictType == TEXT("Residential")) return FLinearColor(0.2f, 0.6f, 0.3f, 1.0f);
	if (DistrictType == TEXT("Commercial")) return FLinearColor(0.2f, 0.4f, 0.8f, 1.0f);
	if (DistrictType == TEXT("Industrial")) return FLinearColor(0.7f, 0.5f, 0.2f, 1.0f);
	if (DistrictType == TEXT("Park")) return FLinearColor(0.1f, 0.7f, 0.2f, 1.0f);
	return FLinearColor(0.5f, 0.5f, 0.5f, 1.0f);
}
