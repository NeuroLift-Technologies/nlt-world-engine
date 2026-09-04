#include "World/NLTWorldObjectRenderer.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"

ANLTWorldObjectRenderer::ANLTWorldObjectRenderer()
{
	PrimaryActorTick.bCanEverTick = false;

	// One ISM per building type so each can have its own material
	BuildingInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BuildingInstances"));
	RootComponent = BuildingInstances;

	RoadInstances = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("RoadInstances"));
	RoadInstances->SetupAttachment(RootComponent);

	// Default cube mesh for buildings and roads
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

	// Assign default materials if user didn't provide them
	UMaterialInterface* ResMat = ResidentialMaterial;
	UMaterialInterface* ComMat = CommercialMaterial;
	UMaterialInterface* IndMat = IndustrialMaterial;
	UMaterialInterface* PrkMat = ParkMaterial;
	UMaterialInterface* OffMat = OfficeMaterial;

	// Create default dynamic materials if not assigned
	UMaterialInstanceDynamic* DefaultResMat = ResMat ? nullptr : UMaterialInstanceDynamic::Create(BuildingInstances->GetMaterial(0), BuildingInstances);
	UMaterialInstanceDynamic* DefaultComMat = ComMat ? nullptr : UMaterialInstanceDynamic::Create(BuildingInstances->GetMaterial(0), BuildingInstances);
	UMaterialInstanceDynamic* DefaultIndMat = IndMat ? nullptr : UMaterialInstanceDynamic::Create(BuildingInstances->GetMaterial(0), BuildingInstances);
	UMaterialInstanceDynamic* DefaultPrkMat = PrkMat ? nullptr : UMaterialInstanceDynamic::Create(BuildingInstances->GetMaterial(0), BuildingInstances);
	UMaterialInstanceDynamic* DefaultOffMat = OffMat ? nullptr : UMaterialInstanceDynamic::Create(BuildingInstances->GetMaterial(0), BuildingInstances);

	if (DefaultResMat) DefaultResMat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.25f, 0.55f, 0.30f, 1.0f));
	if (DefaultComMat) DefaultComMat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.20f, 0.40f, 0.75f, 1.0f));
	if (DefaultIndMat) DefaultIndMat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.65f, 0.45f, 0.20f, 1.0f));
	if (DefaultPrkMat) DefaultPrkMat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.10f, 0.65f, 0.15f, 1.0f));
	if (DefaultOffMat) DefaultOffMat->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(0.45f, 0.50f, 0.60f, 1.0f));

	for (const FNLTGeneratedBuilding& Building : Buildings)
	{
		FVector Pos = Building.Transform.GetLocation();
		FVector Scale3D = Building.Transform.GetScale3D();

		// Determine building dimensions from type
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

		// UE default cube is 100cm, so scale = dimension / 100
		FVector BuildingScale(Width / 100.0f, Depth / 100.0f, Height / 100.0f);
		FTransform InstanceTransform(
			Building.Transform.GetRotation(),
			FVector(Pos.X, Pos.Y, Height * 0.5f),
			BuildingScale);

		BuildingInstances->AddInstance(InstanceTransform);

		// Apply material for this building type
		UMaterialInterface* Mat = GetBuildingMaterial(Building.BuildingType);
		if (!Mat)
		{
			// Use default dynamic material
			if (Building.BuildingType == TEXT("Apartment")) Mat = DefaultResMat;
			else if (Building.BuildingType == TEXT("Shop")) Mat = DefaultComMat;
			else if (Building.BuildingType == TEXT("Factory")) Mat = DefaultIndMat;
			else if (Building.BuildingType == TEXT("Park")) Mat = DefaultPrkMat;
			else if (Building.BuildingType == TEXT("Office")) Mat = DefaultOffMat;
		}

		if (Mat)
			BuildingInstances->SetMaterial(BuildingInstances->GetNumInstances() - 1, Mat);
	}
}

void ANLTWorldObjectRenderer::RenderRoads(const TArray<FTransform>& RoadPoints, float RoadWidth)
{
	if (!RoadInstances) return;

	for (int32 i = 0; i < RoadPoints.Num(); i++)
	{
		const FTransform& RoadPoint = RoadPoints[i];
		FVector Pos = RoadPoint.GetLocation();
		FRotator Rot = RoadPoint.GetRotation().Rotator();

		// Make roads wider and slightly thicker for visibility
		float RoadLength = 400.0f;
		// If there's a next point, stretch road to connect
		if (i < RoadPoints.Num() - 1)
		{
			FVector NextPos = RoadPoints[i + 1].GetLocation();
			FVector Dir = NextPos - Pos;
			float Dist = Dir.Size();
			if (Dist > 1.0f)
			{
				RoadLength = Dist;
				Rot = Dir.Rotation();
			}
		}

		FVector RoadScale(RoadWidth / 100.0f, RoadLength / 100.0f, 0.2f);
		FTransform InstanceTransform(Rot, FVector(Pos.X, Pos.Y, 2.0f), RoadScale);
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
		// UE plane is 100cm x 100cm, so scale = diameter / 100
		float Diameter = District.Radius * 2.0f;
		DistrictMesh->SetWorldScale3D(FVector(Diameter / 100.0f, Diameter / 100.0f, 1.0f));
		DistrictMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DistrictMesh->SetCastShadow(false);
		DistrictMesh->RegisterComponent();

		// Use district material or create a default
		if (DistrictMaterial)
		{
			UMaterialInstanceDynamic* DynMat = UMaterialInstanceDynamic::Create(DistrictMaterial, DistrictMesh);
			if (DynMat)
			{
				DynMat->SetVectorParameterValue(TEXT("DistrictColor"), GetDistrictColor(District.DistrictType));
				DynMat->SetScalarParameterValue(TEXT("Opacity"), 0.3f);
				DistrictMesh->SetMaterial(0, DynMat);
			}
		}
		else
		{
			// Default colored material
			UMaterialInstanceDynamic* DefaultMat = UMaterialInstanceDynamic::Create(DistrictMesh->GetMaterial(0), DistrictMesh);
			if (DefaultMat)
			{
				FLinearColor Color = GetDistrictColor(District.DistrictType);
				DefaultMat->SetVectorParameterValue(TEXT("BaseColor"), Color);
				DefaultMat->SetScalarParameterValue(TEXT("Opacity"), 0.3f);
				DistrictMesh->SetMaterial(0, DefaultMat);
			}
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
