// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/NLTEnvironmentVariation.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTEnvironmentVariation() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTEnvironmentState(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEnvironmentVariationSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEnvironmentVariationSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTEnvironmentState **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTEnvironmentState_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTEnvironmentState>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTEnvironmentState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Deterministic environment state produced from (ScenarioId, RunSeed).\n * Same scenario ID + different run seed => different clutter, lighting, VFX.\n */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deterministic environment state produced from (ScenarioId, RunSeed).\nSame scenario ID + different run seed => different clutter, lighting, VFX." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClutterDensity_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ---- Clutter ----\n" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "---- Clutter ----" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClutterSpread_MetaData[] = {
		{ "Category", "NLT|Environment" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClutterVariantIndices_MetaData[] = {
		{ "Category", "NLT|Environment" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LightingIntensity_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ---- Lighting ----\n" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "---- Lighting ----" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LightingColor_MetaData[] = {
		{ "Category", "NLT|Environment" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorTemperature_MetaData[] = {
		{ "Category", "NLT|Environment" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VfxSeed_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ---- VFX ----\n" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "---- VFX ----" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VfxIntensity_MetaData[] = {
		{ "Category", "NLT|Environment" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AmbientNoiseLevel_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ---- Ambient ----\n" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "---- Ambient ----" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VariationIndex_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ---- Meta ----\n" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "---- Meta ----" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTEnvironmentState constinit property declarations **************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClutterDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ClutterSpread;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ClutterVariantIndices_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ClutterVariantIndices;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LightingIntensity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LightingColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ColorTemperature;
	static const UECodeGen_Private::FIntPropertyParams NewProp_VfxSeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VfxIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AmbientNoiseLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_VariationIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTEnvironmentState constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTEnvironmentState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTEnvironmentState Property Definitions *************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ClutterDensity = { "ClutterDensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, ClutterDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClutterDensity_MetaData), NewProp_ClutterDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ClutterSpread = { "ClutterSpread", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, ClutterSpread), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClutterSpread_MetaData), NewProp_ClutterSpread_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ClutterVariantIndices_Inner = { "ClutterVariantIndices", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ClutterVariantIndices = { "ClutterVariantIndices", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, ClutterVariantIndices), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClutterVariantIndices_MetaData), NewProp_ClutterVariantIndices_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LightingIntensity = { "LightingIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, LightingIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LightingIntensity_MetaData), NewProp_LightingIntensity_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_LightingColor = { "LightingColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, LightingColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LightingColor_MetaData), NewProp_LightingColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ColorTemperature = { "ColorTemperature", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, ColorTemperature), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorTemperature_MetaData), NewProp_ColorTemperature_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_VfxSeed = { "VfxSeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, VfxSeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VfxSeed_MetaData), NewProp_VfxSeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_VfxIntensity = { "VfxIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, VfxIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VfxIntensity_MetaData), NewProp_VfxIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AmbientNoiseLevel = { "AmbientNoiseLevel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, AmbientNoiseLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AmbientNoiseLevel_MetaData), NewProp_AmbientNoiseLevel_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_VariationIndex = { "VariationIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTEnvironmentState, VariationIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VariationIndex_MetaData), NewProp_VariationIndex_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClutterDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClutterSpread,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClutterVariantIndices_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClutterVariantIndices,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LightingIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LightingColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorTemperature,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VfxSeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VfxIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AmbientNoiseLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VariationIndex,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTEnvironmentState Property Definitions ***************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTEnvironmentState",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTEnvironmentState>(),
	alignof(FNLTEnvironmentState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTEnvironmentState;
UScriptStruct* Z_Construct_UScriptStruct_FNLTEnvironmentState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTEnvironmentState.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTEnvironmentState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTEnvironmentState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTEnvironmentState"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTEnvironmentState.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTEnvironmentState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTEnvironmentState.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTEnvironmentState.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTEnvironmentState ************************************************

// ********** Begin Class UNLTEnvironmentVariationSubsystem Function ApplyEnvironmentVariation *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_ApplyEnvironmentVariation_Statics
struct UHT_STATICS
{
	struct NLTEnvironmentVariationSubsystem_eventApplyEnvironmentVariation_Parms
	{
		FName ScenarioId;
		int32 RunSeed;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Generate and store as the active environment state. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Generate and store as the active environment state." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ApplyEnvironmentVariation constinit property declarations *************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ScenarioId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RunSeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ApplyEnvironmentVariation constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ApplyEnvironmentVariation Property Definitions ************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ScenarioId = { "ScenarioId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventApplyEnvironmentVariation_Parms, ScenarioId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RunSeed = { "RunSeed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventApplyEnvironmentVariation_Parms, RunSeed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScenarioId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RunSeed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ApplyEnvironmentVariation Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEnvironmentVariationSubsystem, nullptr, "ApplyEnvironmentVariation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEnvironmentVariationSubsystem_eventApplyEnvironmentVariation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEnvironmentVariationSubsystem_eventApplyEnvironmentVariation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_ApplyEnvironmentVariation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEnvironmentVariationSubsystem::execApplyEnvironmentVariation)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ScenarioId);
	P_GET_PROPERTY(FIntProperty,Z_Param_RunSeed);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ApplyEnvironmentVariation(Z_Param_ScenarioId,Z_Param_RunSeed);
	P_NATIVE_END;
}
// ********** End Class UNLTEnvironmentVariationSubsystem Function ApplyEnvironmentVariation *******

// ********** Begin Class UNLTEnvironmentVariationSubsystem Function GenerateEnvironmentVariation **
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GenerateEnvironmentVariation_Statics
struct UHT_STATICS
{
	struct NLTEnvironmentVariationSubsystem_eventGenerateEnvironmentVariation_Parms
	{
		FName ScenarioId;
		int32 RunSeed;
		FNLTEnvironmentState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Generate deterministic environment state from (ScenarioId, RunSeed). */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Generate deterministic environment state from (ScenarioId, RunSeed)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GenerateEnvironmentVariation constinit property declarations **********
	static const UECodeGen_Private::FNamePropertyParams NewProp_ScenarioId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RunSeed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GenerateEnvironmentVariation constinit property declarations ************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GenerateEnvironmentVariation Property Definitions *********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ScenarioId = { "ScenarioId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventGenerateEnvironmentVariation_Parms, ScenarioId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RunSeed = { "RunSeed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventGenerateEnvironmentVariation_Parms, RunSeed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventGenerateEnvironmentVariation_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTEnvironmentState, METADATA_PARAMS(0, nullptr) }; // c2a69411591474cd84c1b50e205a1d8d9dfbff95
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScenarioId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RunSeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GenerateEnvironmentVariation Property Definitions ***********************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEnvironmentVariationSubsystem, nullptr, "GenerateEnvironmentVariation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEnvironmentVariationSubsystem_eventGenerateEnvironmentVariation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEnvironmentVariationSubsystem_eventGenerateEnvironmentVariation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GenerateEnvironmentVariation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEnvironmentVariationSubsystem::execGenerateEnvironmentVariation)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ScenarioId);
	P_GET_PROPERTY(FIntProperty,Z_Param_RunSeed);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTEnvironmentState*)Z_Param__Result=P_THIS->GenerateEnvironmentVariation(Z_Param_ScenarioId,Z_Param_RunSeed);
	P_NATIVE_END;
}
// ********** End Class UNLTEnvironmentVariationSubsystem Function GenerateEnvironmentVariation ****

// ********** Begin Class UNLTEnvironmentVariationSubsystem Function GetActiveEnvironmentState *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GetActiveEnvironmentState_Statics
struct UHT_STATICS
{
	struct NLTEnvironmentVariationSubsystem_eventGetActiveEnvironmentState_Parms
	{
		FNLTEnvironmentState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetActiveEnvironmentState constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActiveEnvironmentState constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActiveEnvironmentState Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventGetActiveEnvironmentState_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTEnvironmentState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // c2a69411591474cd84c1b50e205a1d8d9dfbff95
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetActiveEnvironmentState Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEnvironmentVariationSubsystem, nullptr, "GetActiveEnvironmentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEnvironmentVariationSubsystem_eventGetActiveEnvironmentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEnvironmentVariationSubsystem_eventGetActiveEnvironmentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GetActiveEnvironmentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEnvironmentVariationSubsystem::execGetActiveEnvironmentState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTEnvironmentState*)Z_Param__Result=P_THIS->GetActiveEnvironmentState();
	P_NATIVE_END;
}
// ********** End Class UNLTEnvironmentVariationSubsystem Function GetActiveEnvironmentState *******

// ********** Begin Class UNLTEnvironmentVariationSubsystem Function GetVariationCount *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GetVariationCount_Statics
struct UHT_STATICS
{
	struct NLTEnvironmentVariationSubsystem_eventGetVariationCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of distinct base variations (moods) the system can produce. */" },
#endif
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of distinct base variations (moods) the system can produce." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetVariationCount constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetVariationCount constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetVariationCount Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEnvironmentVariationSubsystem_eventGetVariationCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetVariationCount Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEnvironmentVariationSubsystem, nullptr, "GetVariationCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEnvironmentVariationSubsystem_eventGetVariationCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEnvironmentVariationSubsystem_eventGetVariationCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GetVariationCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEnvironmentVariationSubsystem::execGetVariationCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=UNLTEnvironmentVariationSubsystem::GetVariationCount();
	P_NATIVE_END;
}
// ********** End Class UNLTEnvironmentVariationSubsystem Function GetVariationCount ***************

// ********** Begin Class UNLTEnvironmentVariationSubsystem ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTEnvironmentVariationSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Seeded micro-variation subsystem for Workplace_Level.\n * Extends FNLTRandomStream to env dressing: same scenario ID produces\n * different environmental states (clutter, lighting, VFX seed) per run.\n */" },
#endif
		{ "IncludePath", "World/NLTEnvironmentVariation.h" },
		{ "ModuleRelativePath", "Public/World/NLTEnvironmentVariation.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Seeded micro-variation subsystem for Workplace_Level.\nExtends FNLTRandomStream to env dressing: same scenario ID produces\ndifferent environmental states (clutter, lighting, VFX seed) per run." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTEnvironmentVariationSubsystem constinit property declarations ********
// ********** End Class UNLTEnvironmentVariationSubsystem constinit property declarations **********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ApplyEnvironmentVariation"), .Pointer = &UNLTEnvironmentVariationSubsystem::execApplyEnvironmentVariation },
		{ .NameUTF8 = UTF8TEXT("GenerateEnvironmentVariation"), .Pointer = &UNLTEnvironmentVariationSubsystem::execGenerateEnvironmentVariation },
		{ .NameUTF8 = UTF8TEXT("GetActiveEnvironmentState"), .Pointer = &UNLTEnvironmentVariationSubsystem::execGetActiveEnvironmentState },
		{ .NameUTF8 = UTF8TEXT("GetVariationCount"), .Pointer = &UNLTEnvironmentVariationSubsystem::execGetVariationCount },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_ApplyEnvironmentVariation, "ApplyEnvironmentVariation" }, // a504aae813fe0c677a6995448520b59a48ae120c
		{ &Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GenerateEnvironmentVariation, "GenerateEnvironmentVariation" }, // 9f126e59de1216a9a7c15ad7247e48d51b28bf5c
		{ &Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GetActiveEnvironmentState, "GetActiveEnvironmentState" }, // 8fa85147c2a8b664a13e1f0f1f638a365b8949b7
		{ &Z_Construct_UFunction_UNLTEnvironmentVariationSubsystem_GetVariationCount, "GetVariationCount" }, // c0a1543648bdba22596160e5cc772cb57f844d31
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTEnvironmentVariationSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTEnvironmentVariationSubsystem,
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
static void UNLTEnvironmentVariationSubsystem_StaticRegisterNativesUNLTEnvironmentVariationSubsystem()
{
	UClass* Class = UNLTEnvironmentVariationSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem;
UClass* Z_Construct_UClass_UNLTEnvironmentVariationSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTEnvironmentVariationSubsystem;
		if (!Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTEnvironmentVariationSubsystem"),
				Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem.InnerSingleton,
				UNLTEnvironmentVariationSubsystem_StaticRegisterNativesUNLTEnvironmentVariationSubsystem,
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
		return Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTEnvironmentVariationSubsystem::UNLTEnvironmentVariationSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTEnvironmentVariationSubsystem);
UNLTEnvironmentVariationSubsystem::~UNLTEnvironmentVariationSubsystem() {}
// ********** End Class UNLTEnvironmentVariationSubsystem ******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTEnvironmentState, Z_Construct_UScriptStruct_FNLTEnvironmentState_Statics::NewStructOps, TEXT("NLTEnvironmentState"),&Z_Registration_Info_UScriptStruct_FNLTEnvironmentState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTEnvironmentState), 3265696785U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTEnvironmentVariationSubsystem, TEXT("UNLTEnvironmentVariationSubsystem"), &Z_Registration_Info_UClass_UNLTEnvironmentVariationSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTEnvironmentVariationSubsystem), 3461512292U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h__Script_WorldEngine_e2cc68bf660c9feb0fc3c7bb24b9c8008a5b73f3{
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
