// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/NLTWorldData.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTWorldData() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FBox(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTLocationSemanticData(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldState(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTLocationSemanticData ******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTLocationSemanticData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTLocationSemanticData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTLocationSemanticData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocationType_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseLevel_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SocialDensity_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Privacy_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Accessibility_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvailableActivities_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bounds_MetaData[] = {
		{ "Category", "NLTLocationSemanticData" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTLocationSemanticData constinit property declarations **********
	static const UECodeGen_Private::FNamePropertyParams NewProp_LocationType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SocialDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Privacy;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Accessibility;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AvailableActivities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AvailableActivities;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bounds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTLocationSemanticData constinit property declarations ************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTLocationSemanticData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTLocationSemanticData Property Definitions *********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_LocationType = { "LocationType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, LocationType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocationType_MetaData), NewProp_LocationType_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseLevel = { "NoiseLevel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, NoiseLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseLevel_MetaData), NewProp_NoiseLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SocialDensity = { "SocialDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, SocialDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SocialDensity_MetaData), NewProp_SocialDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Privacy = { "Privacy", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, Privacy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Privacy_MetaData), NewProp_Privacy_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Accessibility = { "Accessibility", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, Accessibility), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Accessibility_MetaData), NewProp_Accessibility_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AvailableActivities_Inner = { "AvailableActivities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_AvailableActivities = { "AvailableActivities", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, AvailableActivities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvailableActivities_MetaData), NewProp_AvailableActivities_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Bounds = { "Bounds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTLocationSemanticData, Bounds), Z_Construct_UScriptStruct_FBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bounds_MetaData), NewProp_Bounds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LocationType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SocialDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Privacy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Accessibility,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvailableActivities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvailableActivities,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bounds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTLocationSemanticData Property Definitions ***********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTLocationSemanticData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTLocationSemanticData>(),
	alignof(FNLTLocationSemanticData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData;
UScriptStruct* Z_Construct_UScriptStruct_FNLTLocationSemanticData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTLocationSemanticData, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTLocationSemanticData"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTLocationSemanticData ********************************************

// ********** Begin ScriptStruct FNLTWorldState ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTWorldState_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTWorldState>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTWorldState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulationTick_MetaData[] = {
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveEvents_MetaData[] = {
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeOfDay_MetaData[] = {
		{ "ModuleRelativePath", "Public/World/NLTWorldData.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTWorldState constinit property declarations ********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SimulationTick;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_WorldTime;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ActiveEvents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActiveEvents;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeOfDay;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTWorldState constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTWorldState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTWorldState Property Definitions *******************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SimulationTick = { "SimulationTick", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldState, SimulationTick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulationTick_MetaData), NewProp_SimulationTick_MetaData) };
const UECodeGen_Private::FDoublePropertyParams UHT_STATICS::NewProp_WorldTime = { "WorldTime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Double, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldState, WorldTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldTime_MetaData), NewProp_WorldTime_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ActiveEvents_Inner = { "ActiveEvents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ActiveEvents = { "ActiveEvents", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldState, ActiveEvents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveEvents_MetaData), NewProp_ActiveEvents_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TimeOfDay = { "TimeOfDay", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldState, TimeOfDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeOfDay_MetaData), NewProp_TimeOfDay_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SimulationTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEvents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEvents,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TimeOfDay,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTWorldState Property Definitions *********************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTWorldState",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTWorldState>(),
	alignof(FNLTWorldState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTWorldState;
UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTWorldState.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTWorldState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTWorldState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTWorldState"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTWorldState.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTWorldState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTWorldState.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTWorldState.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTWorldState ******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldData_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTLocationSemanticData, Z_Construct_UScriptStruct_FNLTLocationSemanticData_Statics::NewStructOps, TEXT("NLTLocationSemanticData"),&Z_Registration_Info_UScriptStruct_FNLTLocationSemanticData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTLocationSemanticData), 1268652409U) },
		{ Z_Construct_UScriptStruct_FNLTWorldState, Z_Construct_UScriptStruct_FNLTWorldState_Statics::NewStructOps, TEXT("NLTWorldState"),&Z_Registration_Info_UScriptStruct_FNLTWorldState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTWorldState), 1970515806U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldData_h__Script_WorldEngine_e86d24195628fb53d7c1e0783691876c2c985758{
	TEXT("/Script/WorldEngine"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
