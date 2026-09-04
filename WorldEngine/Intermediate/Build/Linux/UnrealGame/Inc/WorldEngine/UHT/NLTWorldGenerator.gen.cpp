// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/NLTWorldGenerator.h"
#include "World/NLTWorldData.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTWorldGenerator() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FTransform(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTGeneratedBuilding(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTGeneratedDistrict(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTLocationSemanticData(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationParams(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationResult(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWorldGeneratorSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWorldGeneratorSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTWorldGenerationParams *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTWorldGenerationParams_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTWorldGenerationParams>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTWorldGenerationParams); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldSize_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumDistricts_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumBuildings_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumRoads_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoadWidth_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuildingDensity_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GreenSpaceRatio_MetaData[] = {
		{ "Category", "NLTWorldGenerationParams" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTWorldGenerationParams constinit property declarations *********
	static const UECodeGen_Private::FIntPropertyParams NewProp_Seed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumDistricts;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumBuildings;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumRoads;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RoadWidth;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BuildingDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_GreenSpaceRatio;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTWorldGenerationParams constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTWorldGenerationParams>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTWorldGenerationParams Property Definitions ********************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, Seed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Seed_MetaData), NewProp_Seed_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WorldSize = { "WorldSize", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, WorldSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldSize_MetaData), NewProp_WorldSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumDistricts = { "NumDistricts", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, NumDistricts), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumDistricts_MetaData), NewProp_NumDistricts_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumBuildings = { "NumBuildings", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, NumBuildings), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumBuildings_MetaData), NewProp_NumBuildings_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumRoads = { "NumRoads", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, NumRoads), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumRoads_MetaData), NewProp_NumRoads_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RoadWidth = { "RoadWidth", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, RoadWidth), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoadWidth_MetaData), NewProp_RoadWidth_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BuildingDensity = { "BuildingDensity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, BuildingDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuildingDensity_MetaData), NewProp_BuildingDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_GreenSpaceRatio = { "GreenSpaceRatio", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationParams, GreenSpaceRatio), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GreenSpaceRatio_MetaData), NewProp_GreenSpaceRatio_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Seed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumDistricts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumBuildings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumRoads,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoadWidth,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BuildingDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_GreenSpaceRatio,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTWorldGenerationParams Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTWorldGenerationParams",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTWorldGenerationParams>(),
	alignof(FNLTWorldGenerationParams),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams;
UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationParams(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTWorldGenerationParams, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTWorldGenerationParams"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTWorldGenerationParams *******************************************

// ********** Begin ScriptStruct FNLTGeneratedDistrict *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTGeneratedDistrict_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTGeneratedDistrict>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTGeneratedDistrict); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistrictType_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Center_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Activities_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseLevel_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SocialDensity_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Privacy_MetaData[] = {
		{ "Category", "NLTGeneratedDistrict" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTGeneratedDistrict constinit property declarations *************
	static const UECodeGen_Private::FNamePropertyParams NewProp_DistrictType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Center;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Activities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Activities;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SocialDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Privacy;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTGeneratedDistrict constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTGeneratedDistrict>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTGeneratedDistrict Property Definitions ************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DistrictType = { "DistrictType", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, DistrictType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistrictType_MetaData), NewProp_DistrictType_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Center = { "Center", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, Center), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Center_MetaData), NewProp_Center_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, Radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Radius_MetaData), NewProp_Radius_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_Activities_Inner = { "Activities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Activities = { "Activities", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, Activities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Activities_MetaData), NewProp_Activities_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseLevel = { "NoiseLevel", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, NoiseLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseLevel_MetaData), NewProp_NoiseLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SocialDensity = { "SocialDensity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, SocialDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SocialDensity_MetaData), NewProp_SocialDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Privacy = { "Privacy", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedDistrict, Privacy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Privacy_MetaData), NewProp_Privacy_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DistrictType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Center,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Activities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Activities,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SocialDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Privacy,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTGeneratedDistrict Property Definitions **************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTGeneratedDistrict",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTGeneratedDistrict>(),
	alignof(FNLTGeneratedDistrict),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict;
UScriptStruct* Z_Construct_UScriptStruct_FNLTGeneratedDistrict(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTGeneratedDistrict, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTGeneratedDistrict"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTGeneratedDistrict ***********************************************

// ********** Begin ScriptStruct FNLTGeneratedBuilding *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTGeneratedBuilding_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTGeneratedBuilding>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTGeneratedBuilding); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Transform_MetaData[] = {
		{ "Category", "NLTGeneratedBuilding" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BuildingType_MetaData[] = {
		{ "Category", "NLTGeneratedBuilding" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SemanticData_MetaData[] = {
		{ "Category", "NLTGeneratedBuilding" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTGeneratedBuilding constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Transform;
	static const UECodeGen_Private::FNamePropertyParams NewProp_BuildingType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SemanticData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTGeneratedBuilding constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTGeneratedBuilding>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTGeneratedBuilding Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Transform = { "Transform", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedBuilding, Transform), Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Transform_MetaData), NewProp_Transform_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_BuildingType = { "BuildingType", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedBuilding, BuildingType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BuildingType_MetaData), NewProp_BuildingType_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SemanticData = { "SemanticData", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTGeneratedBuilding, SemanticData), Z_Construct_UScriptStruct_FNLTLocationSemanticData, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SemanticData_MetaData), NewProp_SemanticData_MetaData) }; // 4b9e197952dd0137ddb4173cb680b2cd5e8967a2
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Transform,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BuildingType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SemanticData,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTGeneratedBuilding Property Definitions **************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTGeneratedBuilding",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTGeneratedBuilding>(),
	alignof(FNLTGeneratedBuilding),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding;
UScriptStruct* Z_Construct_UScriptStruct_FNLTGeneratedBuilding(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTGeneratedBuilding, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTGeneratedBuilding"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTGeneratedBuilding ***********************************************

// ********** Begin ScriptStruct FNLTWorldGenerationResult *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTWorldGenerationResult_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTWorldGenerationResult>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTWorldGenerationResult); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Districts_MetaData[] = {
		{ "Category", "NLTWorldGenerationResult" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Buildings_MetaData[] = {
		{ "Category", "NLTWorldGenerationResult" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoadPoints_MetaData[] = {
		{ "Category", "NLTWorldGenerationResult" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTWorldGenerationResult constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Districts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Districts;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Buildings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Buildings;
	static const UECodeGen_Private::FStructPropertyParams NewProp_RoadPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RoadPoints;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTWorldGenerationResult constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTWorldGenerationResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTWorldGenerationResult Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Districts_Inner = { "Districts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTGeneratedDistrict, METADATA_PARAMS(0, nullptr) }; // b86fa5d031a3735f05dac03462527e95e727b039
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Districts = { "Districts", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationResult, Districts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Districts_MetaData), NewProp_Districts_MetaData) }; // b86fa5d031a3735f05dac03462527e95e727b039
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Buildings_Inner = { "Buildings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTGeneratedBuilding, METADATA_PARAMS(0, nullptr) }; // 1b0d4d7bce639bd1868a87063046e28d0390dc62
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Buildings = { "Buildings", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationResult, Buildings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Buildings_MetaData), NewProp_Buildings_MetaData) }; // 1b0d4d7bce639bd1868a87063046e28d0390dc62
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_RoadPoints_Inner = { "RoadPoints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTransform, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_RoadPoints = { "RoadPoints", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldGenerationResult, RoadPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoadPoints_MetaData), NewProp_RoadPoints_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Districts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Districts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Buildings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Buildings,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoadPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoadPoints,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTWorldGenerationResult Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTWorldGenerationResult",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTWorldGenerationResult>(),
	alignof(FNLTWorldGenerationResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult;
UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationResult(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTWorldGenerationResult, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTWorldGenerationResult"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTWorldGenerationResult *******************************************

// ********** Begin Class UNLTWorldGeneratorSubsystem Function ClearWorld **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_ClearWorld_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ClearWorld constinit property declarations ****************************
// ********** End Function ClearWorld constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorldGeneratorSubsystem, nullptr, "ClearWorld", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_ClearWorld(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorldGeneratorSubsystem::execClearWorld)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ClearWorld();
	P_NATIVE_END;
}
// ********** End Class UNLTWorldGeneratorSubsystem Function ClearWorld ****************************

// ********** Begin Class UNLTWorldGeneratorSubsystem Function GenerateWorld ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_GenerateWorld_Statics
struct UHT_STATICS
{
	struct NLTWorldGeneratorSubsystem_eventGenerateWorld_Parms
	{
		FNLTWorldGenerationParams Params;
		FNLTWorldGenerationResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Params_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GenerateWorld constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Params;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GenerateWorld constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GenerateWorld Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Params = { "Params", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorldGeneratorSubsystem_eventGenerateWorld_Parms, Params), Z_Construct_UScriptStruct_FNLTWorldGenerationParams, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Params_MetaData), NewProp_Params_MetaData) }; // eb1bc449d98f170920adb2a80a4a396057dc6fee
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorldGeneratorSubsystem_eventGenerateWorld_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTWorldGenerationResult, METADATA_PARAMS(0, nullptr) }; // 7db764a0f3a70c295a9fee8a515d87ae2f47e42a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Params,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GenerateWorld Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorldGeneratorSubsystem, nullptr, "GenerateWorld", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorldGeneratorSubsystem_eventGenerateWorld_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorldGeneratorSubsystem_eventGenerateWorld_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_GenerateWorld(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorldGeneratorSubsystem::execGenerateWorld)
{
	P_GET_STRUCT_REF(FNLTWorldGenerationParams,Z_Param_Out_Params);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTWorldGenerationResult*)Z_Param__Result=P_THIS->GenerateWorld(Z_Param_Out_Params);
	P_NATIVE_END;
}
// ********** End Class UNLTWorldGeneratorSubsystem Function GenerateWorld *************************

// ********** Begin Class UNLTWorldGeneratorSubsystem Function GetGeneratedWorld *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_GetGeneratedWorld_Statics
struct UHT_STATICS
{
	struct NLTWorldGeneratorSubsystem_eventGetGeneratedWorld_Parms
	{
		FNLTWorldGenerationResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetGeneratedWorld constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetGeneratedWorld constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetGeneratedWorld Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorldGeneratorSubsystem_eventGetGeneratedWorld_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTWorldGenerationResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 7db764a0f3a70c295a9fee8a515d87ae2f47e42a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetGeneratedWorld Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorldGeneratorSubsystem, nullptr, "GetGeneratedWorld", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorldGeneratorSubsystem_eventGetGeneratedWorld_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorldGeneratorSubsystem_eventGetGeneratedWorld_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_GetGeneratedWorld(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorldGeneratorSubsystem::execGetGeneratedWorld)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTWorldGenerationResult*)Z_Param__Result=P_THIS->GetGeneratedWorld();
	P_NATIVE_END;
}
// ********** End Class UNLTWorldGeneratorSubsystem Function GetGeneratedWorld *********************

// ********** Begin Class UNLTWorldGeneratorSubsystem Function IsWorldGenerated ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_IsWorldGenerated_Statics
struct UHT_STATICS
{
	struct NLTWorldGeneratorSubsystem_eventIsWorldGenerated_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsWorldGenerated constinit property declarations **********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTWorldGeneratorSubsystem_eventIsWorldGenerated_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsWorldGenerated constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsWorldGenerated Property Definitions *********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTWorldGeneratorSubsystem_eventIsWorldGenerated_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsWorldGenerated Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorldGeneratorSubsystem, nullptr, "IsWorldGenerated", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorldGeneratorSubsystem_eventIsWorldGenerated_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorldGeneratorSubsystem_eventIsWorldGenerated_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_IsWorldGenerated(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorldGeneratorSubsystem::execIsWorldGenerated)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsWorldGenerated();
	P_NATIVE_END;
}
// ********** End Class UNLTWorldGeneratorSubsystem Function IsWorldGenerated **********************

// ********** Begin Class UNLTWorldGeneratorSubsystem **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTWorldGeneratorSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "World/NLTWorldGenerator.h" },
		{ "ModuleRelativePath", "Public/World/NLTWorldGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTWorldGeneratorSubsystem constinit property declarations **************
// ********** End Class UNLTWorldGeneratorSubsystem constinit property declarations ****************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ClearWorld"), .Pointer = &UNLTWorldGeneratorSubsystem::execClearWorld },
		{ .NameUTF8 = UTF8TEXT("GenerateWorld"), .Pointer = &UNLTWorldGeneratorSubsystem::execGenerateWorld },
		{ .NameUTF8 = UTF8TEXT("GetGeneratedWorld"), .Pointer = &UNLTWorldGeneratorSubsystem::execGetGeneratedWorld },
		{ .NameUTF8 = UTF8TEXT("IsWorldGenerated"), .Pointer = &UNLTWorldGeneratorSubsystem::execIsWorldGenerated },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_ClearWorld, "ClearWorld" }, // faf3fb2270dc5cbe7271818122487320144efc4d
		{ &Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_GenerateWorld, "GenerateWorld" }, // 7e2ea6b95457bf5bc107b639f31e501456b556b4
		{ &Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_GetGeneratedWorld, "GetGeneratedWorld" }, // 605ee7b472cfa30b61d9369e784a3daabdb4c7e5
		{ &Z_Construct_UFunction_UNLTWorldGeneratorSubsystem_IsWorldGenerated, "IsWorldGenerated" }, // cff70abf79d15dbe9c7a500003c6249f48c74d08
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTWorldGeneratorSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTWorldGeneratorSubsystem,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UNLTWorldGeneratorSubsystem_StaticRegisterNativesUNLTWorldGeneratorSubsystem()
{
	UClass* Class = UNLTWorldGeneratorSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem;
UClass* Z_Construct_UClass_UNLTWorldGeneratorSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTWorldGeneratorSubsystem;
		if (!Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTWorldGeneratorSubsystem"),
				Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem.InnerSingleton,
				UNLTWorldGeneratorSubsystem_StaticRegisterNativesUNLTWorldGeneratorSubsystem,
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
		return Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTWorldGeneratorSubsystem::UNLTWorldGeneratorSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTWorldGeneratorSubsystem);
UNLTWorldGeneratorSubsystem::~UNLTWorldGeneratorSubsystem() {}
// ********** End Class UNLTWorldGeneratorSubsystem ************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTWorldGenerationParams, Z_Construct_UScriptStruct_FNLTWorldGenerationParams_Statics::NewStructOps, TEXT("NLTWorldGenerationParams"),&Z_Registration_Info_UScriptStruct_FNLTWorldGenerationParams, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTWorldGenerationParams), 3944465481U) },
		{ Z_Construct_UScriptStruct_FNLTGeneratedDistrict, Z_Construct_UScriptStruct_FNLTGeneratedDistrict_Statics::NewStructOps, TEXT("NLTGeneratedDistrict"),&Z_Registration_Info_UScriptStruct_FNLTGeneratedDistrict, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTGeneratedDistrict), 3094324688U) },
		{ Z_Construct_UScriptStruct_FNLTGeneratedBuilding, Z_Construct_UScriptStruct_FNLTGeneratedBuilding_Statics::NewStructOps, TEXT("NLTGeneratedBuilding"),&Z_Registration_Info_UScriptStruct_FNLTGeneratedBuilding, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTGeneratedBuilding), 453856635U) },
		{ Z_Construct_UScriptStruct_FNLTWorldGenerationResult, Z_Construct_UScriptStruct_FNLTWorldGenerationResult_Statics::NewStructOps, TEXT("NLTWorldGenerationResult"),&Z_Registration_Info_UScriptStruct_FNLTWorldGenerationResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTWorldGenerationResult), 2109170848U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTWorldGeneratorSubsystem, TEXT("UNLTWorldGeneratorSubsystem"), &Z_Registration_Info_UClass_UNLTWorldGeneratorSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTWorldGeneratorSubsystem), 304320967U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h__Script_WorldEngine_471c26ea8dc2ddb9181b954ca09cfb5dd7a3078f{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
