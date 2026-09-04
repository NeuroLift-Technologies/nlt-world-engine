// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/NLTWorldObjectRenderer.h"
#include "World/NLTWorldGenerator.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTWorldObjectRenderer() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UInstancedStaticMeshComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationResult(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTWorldObjectRenderer(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTWorldObjectRenderer(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ANLTWorldObjectRenderer Function BuildFromWorld **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ANLTWorldObjectRenderer_BuildFromWorld_Statics
struct UHT_STATICS
{
	struct NLTWorldObjectRenderer_eventBuildFromWorld_Parms
	{
		FNLTWorldGenerationResult WorldResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Build all visual meshes from a world generation result. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Build all visual meshes from a world generation result." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function BuildFromWorld constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BuildFromWorld constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BuildFromWorld Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WorldResult = { "WorldResult", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorldObjectRenderer_eventBuildFromWorld_Parms, WorldResult), Z_Construct_UScriptStruct_FNLTWorldGenerationResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldResult_MetaData), NewProp_WorldResult_MetaData) }; // 7db764a0f3a70c295a9fee8a515d87ae2f47e42a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldResult,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BuildFromWorld Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ANLTWorldObjectRenderer, nullptr, "BuildFromWorld", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorldObjectRenderer_eventBuildFromWorld_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorldObjectRenderer_eventBuildFromWorld_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ANLTWorldObjectRenderer_BuildFromWorld(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ANLTWorldObjectRenderer::execBuildFromWorld)
{
	P_GET_STRUCT_REF(FNLTWorldGenerationResult,Z_Param_Out_WorldResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BuildFromWorld(Z_Param_Out_WorldResult);
	P_NATIVE_END;
}
// ********** End Class ANLTWorldObjectRenderer Function BuildFromWorld ****************************

// ********** Begin Class ANLTWorldObjectRenderer Function ClearWorld ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ANLTWorldObjectRenderer_ClearWorld_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Clear all rendered meshes. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Clear all rendered meshes." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ClearWorld constinit property declarations ****************************
// ********** End Function ClearWorld constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ANLTWorldObjectRenderer, nullptr, "ClearWorld", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ANLTWorldObjectRenderer_ClearWorld(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ANLTWorldObjectRenderer::execClearWorld)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearWorld();
	P_NATIVE_END;
}
// ********** End Class ANLTWorldObjectRenderer Function ClearWorld ********************************

// ********** Begin Class ANLTWorldObjectRenderer **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ANLTWorldObjectRenderer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Visual renderer for the procedural world generated by NLTWorldGenerator.\n * Renders buildings as 3D boxes with type-specific materials,\n * roads as flat ribbons, and districts as colored ground zones.\n */" },
#endif
		{ "IncludePath", "World/NLTWorldObjectRenderer.h" },
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Visual renderer for the procedural world generated by NLTWorldGenerator.\nRenders buildings as 3D boxes with type-specific materials,\nroads as flat ribbons, and districts as colored ground zones." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRenderDistricts_MetaData[] = {
		{ "Category", "NLT|World|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to render district zones as colored ground planes. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to render district zones as colored ground planes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRenderRoads_MetaData[] = {
		{ "Category", "NLT|World|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to render roads. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to render roads." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRenderBuildings_MetaData[] = {
		{ "Category", "NLT|World|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to render buildings. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to render buildings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuildingHeightScale_MetaData[] = {
		{ "Category", "NLT|World|Render" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Height multiplier for buildings (taller = more visible). */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Height multiplier for buildings (taller = more visible)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ResidentialMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for residential buildings. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for residential buildings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CommercialMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for commercial buildings. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for commercial buildings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IndustrialMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for industrial buildings. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for industrial buildings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParkMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for park areas. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for park areas." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OfficeMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for office buildings. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for office buildings." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoadMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for roads. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for roads." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistrictMaterial_MetaData[] = {
		{ "Category", "NLT|World|Render|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Material for district zones. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material for district zones." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuildingInstances_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoadInstances_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistrictMeshes_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldObjectRenderer.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ANLTWorldObjectRenderer constinit property declarations ******************
	static void NewProp_bRenderDistricts_SetBit(void* Obj)
	{
		((ANLTWorldObjectRenderer*)Obj)->bRenderDistricts = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRenderDistricts;
	static void NewProp_bRenderRoads_SetBit(void* Obj)
	{
		((ANLTWorldObjectRenderer*)Obj)->bRenderRoads = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRenderRoads;
	static void NewProp_bRenderBuildings_SetBit(void* Obj)
	{
		((ANLTWorldObjectRenderer*)Obj)->bRenderBuildings = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRenderBuildings;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BuildingHeightScale;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ResidentialMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CommercialMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_IndustrialMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ParkMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OfficeMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RoadMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DistrictMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BuildingInstances;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_RoadInstances;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DistrictMeshes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DistrictMeshes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ANLTWorldObjectRenderer constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("BuildFromWorld"), .Pointer = &ANLTWorldObjectRenderer::execBuildFromWorld },
		{ .NameUTF8 = UTF8TEXT("ClearWorld"), .Pointer = &ANLTWorldObjectRenderer::execClearWorld },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ANLTWorldObjectRenderer_BuildFromWorld, "BuildFromWorld" }, // 1d3aae389851b6a66d9003ef74079b57ea7cfbf6
		{ &Z_Construct_UFunction_ANLTWorldObjectRenderer_ClearWorld, "ClearWorld" }, // a22323fe5aa22b5b580f28ebdf9b7bfe97e3ead5
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANLTWorldObjectRenderer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ANLTWorldObjectRenderer Property Definitions *****************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRenderDistricts = { "bRenderDistricts", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTWorldObjectRenderer), &UHT_STATICS::NewProp_bRenderDistricts_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRenderDistricts_MetaData), NewProp_bRenderDistricts_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRenderRoads = { "bRenderRoads", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTWorldObjectRenderer), &UHT_STATICS::NewProp_bRenderRoads_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRenderRoads_MetaData), NewProp_bRenderRoads_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRenderBuildings = { "bRenderBuildings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTWorldObjectRenderer), &UHT_STATICS::NewProp_bRenderBuildings_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRenderBuildings_MetaData), NewProp_bRenderBuildings_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BuildingHeightScale = { "BuildingHeightScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, BuildingHeightScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuildingHeightScale_MetaData), NewProp_BuildingHeightScale_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ResidentialMaterial = { "ResidentialMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, ResidentialMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ResidentialMaterial_MetaData), NewProp_ResidentialMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CommercialMaterial = { "CommercialMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, CommercialMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CommercialMaterial_MetaData), NewProp_CommercialMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_IndustrialMaterial = { "IndustrialMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, IndustrialMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IndustrialMaterial_MetaData), NewProp_IndustrialMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ParkMaterial = { "ParkMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, ParkMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParkMaterial_MetaData), NewProp_ParkMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OfficeMaterial = { "OfficeMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, OfficeMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OfficeMaterial_MetaData), NewProp_OfficeMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RoadMaterial = { "RoadMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, RoadMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoadMaterial_MetaData), NewProp_RoadMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DistrictMaterial = { "DistrictMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, DistrictMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistrictMaterial_MetaData), NewProp_DistrictMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BuildingInstances = { "BuildingInstances", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, BuildingInstances), Z_Construct_UClass_UInstancedStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuildingInstances_MetaData), NewProp_BuildingInstances_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_RoadInstances = { "RoadInstances", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, RoadInstances), Z_Construct_UClass_UInstancedStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoadInstances_MetaData), NewProp_RoadInstances_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DistrictMeshes_Inner = { "DistrictMeshes", nullptr, (EPropertyFlags)0x0104000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, 0, Z_Construct_UClass_UStaticMeshComponent, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_DistrictMeshes = { "DistrictMeshes", nullptr, (EPropertyFlags)0x0144008000000008, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTWorldObjectRenderer, DistrictMeshes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistrictMeshes_MetaData), NewProp_DistrictMeshes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRenderDistricts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRenderRoads,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRenderBuildings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BuildingHeightScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ResidentialMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CommercialMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_IndustrialMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ParkMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OfficeMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoadMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DistrictMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BuildingInstances,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoadInstances,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DistrictMeshes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DistrictMeshes,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ANLTWorldObjectRenderer Property Definitions *******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ANLTWorldObjectRenderer,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ANLTWorldObjectRenderer_StaticRegisterNativesANLTWorldObjectRenderer()
{
	UClass* Class = ANLTWorldObjectRenderer::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ANLTWorldObjectRenderer;
UClass* Z_Construct_UClass_ANLTWorldObjectRenderer(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ANLTWorldObjectRenderer;
		if (!Z_Registration_Info_UClass_ANLTWorldObjectRenderer.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTWorldObjectRenderer"),
				Z_Registration_Info_UClass_ANLTWorldObjectRenderer.InnerSingleton,
				ANLTWorldObjectRenderer_StaticRegisterNativesANLTWorldObjectRenderer,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_ANLTWorldObjectRenderer.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ANLTWorldObjectRenderer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANLTWorldObjectRenderer.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ANLTWorldObjectRenderer.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ANLTWorldObjectRenderer);
ANLTWorldObjectRenderer::~ANLTWorldObjectRenderer() {}
// ********** End Class ANLTWorldObjectRenderer ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANLTWorldObjectRenderer, TEXT("ANLTWorldObjectRenderer"), &Z_Registration_Info_UClass_ANLTWorldObjectRenderer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANLTWorldObjectRenderer), 2056345399U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h__Script_WorldEngine_75bc1be6d22667aef827adf51d5c9263b72791f3{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
