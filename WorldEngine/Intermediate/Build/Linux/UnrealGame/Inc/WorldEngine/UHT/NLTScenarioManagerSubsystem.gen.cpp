// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scenarios/Demo/NLTScenarioManagerSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTScenarioManagerSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioManagerSubsystem(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioParams(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEnvironmentVariationSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioManagerSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTScenarioParams ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTScenarioParams_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTScenarioParams>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTScenarioParams); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Parameters for one scenario run. Everything needed to reproduce a run\n * deterministically is captured here (agent count, spawn area, seed).\n */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Parameters for one scenario run. Everything needed to reproduce a run\ndeterministically is captured here (agent count, spawn area, seed)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumAgents_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnOrigin_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnRadius_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoStartSimulation_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTScenarioParams constinit property declarations ****************
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumAgents;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SpawnOrigin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpawnRadius;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Seed;
	static void NewProp_bAutoStartSimulation_SetBit(void* Obj)
	{
		((FNLTScenarioParams*)Obj)->bAutoStartSimulation = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoStartSimulation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTScenarioParams constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTScenarioParams>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTScenarioParams Property Definitions ***************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumAgents = { "NumAgents", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioParams, NumAgents), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumAgents_MetaData), NewProp_NumAgents_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SpawnOrigin = { "SpawnOrigin", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioParams, SpawnOrigin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnOrigin_MetaData), NewProp_SpawnOrigin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SpawnRadius = { "SpawnRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioParams, SpawnRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnRadius_MetaData), NewProp_SpawnRadius_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioParams, Seed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Seed_MetaData), NewProp_Seed_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAutoStartSimulation = { "bAutoStartSimulation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FNLTScenarioParams), &UHT_STATICS::NewProp_bAutoStartSimulation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoStartSimulation_MetaData), NewProp_bAutoStartSimulation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumAgents,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnOrigin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Seed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAutoStartSimulation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTScenarioParams Property Definitions *****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTScenarioParams",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTScenarioParams>(),
	alignof(FNLTScenarioParams),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTScenarioParams;
UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioParams(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTScenarioParams.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTScenarioParams.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTScenarioParams, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTScenarioParams"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTScenarioParams.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTScenarioParams.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTScenarioParams.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTScenarioParams.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTScenarioParams **************************************************

// ********** Begin Class UNLTScenarioManagerSubsystem Function GetActiveParams ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetActiveParams_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventGetActiveParams_Parms
	{
		FNLTScenarioParams ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetActiveParams constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActiveParams constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActiveParams Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventGetActiveParams_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTScenarioParams, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // d42eeb8e04e5a10ad01878ca226486452c71fe23
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetActiveParams Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "GetActiveParams", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventGetActiveParams_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventGetActiveParams_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetActiveParams(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execGetActiveParams)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTScenarioParams*)Z_Param__Result=P_THIS->GetActiveParams();
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function GetActiveParams **********************

// ********** Begin Class UNLTScenarioManagerSubsystem Function GetActiveScenario ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetActiveScenario_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventGetActiveScenario_Parms
	{
		UScenarioDataAsset* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetActiveScenario constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetActiveScenario constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetActiveScenario Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventGetActiveScenario_Parms, ReturnValue), Z_Construct_UClass_UScenarioDataAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetActiveScenario Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "GetActiveScenario", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventGetActiveScenario_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventGetActiveScenario_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetActiveScenario(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execGetActiveScenario)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UScenarioDataAsset**)Z_Param__Result=P_THIS->GetActiveScenario();
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function GetActiveScenario ********************

// ********** Begin Class UNLTScenarioManagerSubsystem Function GetEnvironmentVariationSubsystem ***
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetEnvironmentVariationSubsystem_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventGetEnvironmentVariationSubsystem_Parms
	{
		UNLTEnvironmentVariationSubsystem* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns the environment variation subsystem for the active run. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the environment variation subsystem for the active run." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetEnvironmentVariationSubsystem constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEnvironmentVariationSubsystem constinit property declarations ********
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEnvironmentVariationSubsystem Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventGetEnvironmentVariationSubsystem_Parms, ReturnValue), Z_Construct_UClass_UNLTEnvironmentVariationSubsystem, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetEnvironmentVariationSubsystem Property Definitions *******************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "GetEnvironmentVariationSubsystem", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventGetEnvironmentVariationSubsystem_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventGetEnvironmentVariationSubsystem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetEnvironmentVariationSubsystem(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execGetEnvironmentVariationSubsystem)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UNLTEnvironmentVariationSubsystem**)Z_Param__Result=P_THIS->GetEnvironmentVariationSubsystem();
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function GetEnvironmentVariationSubsystem *****

// ********** Begin Class UNLTScenarioManagerSubsystem Function GetScenarioTick ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetScenarioTick_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventGetScenarioTick_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetScenarioTick constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetScenarioTick constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetScenarioTick Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventGetScenarioTick_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetScenarioTick Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "GetScenarioTick", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventGetScenarioTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventGetScenarioTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetScenarioTick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execGetScenarioTick)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetScenarioTick();
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function GetScenarioTick **********************

// ********** Begin Class UNLTScenarioManagerSubsystem Function IsScenarioActive *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_IsScenarioActive_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventIsScenarioActive_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsScenarioActive constinit property declarations **********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTScenarioManagerSubsystem_eventIsScenarioActive_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsScenarioActive constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsScenarioActive Property Definitions *********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTScenarioManagerSubsystem_eventIsScenarioActive_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsScenarioActive Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "IsScenarioActive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventIsScenarioActive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventIsScenarioActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_IsScenarioActive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execIsScenarioActive)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsScenarioActive();
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function IsScenarioActive *********************

// ********** Begin Class UNLTScenarioManagerSubsystem Function StartScenario **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StartScenario_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventStartScenario_Parms
	{
		FNLTScenarioParams Params;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Despawns any previous run, spawns agents deterministically, optionally starts the sim clock. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Despawns any previous run, spawns agents deterministically, optionally starts the sim clock." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Params_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartScenario constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Params;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTScenarioManagerSubsystem_eventStartScenario_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartScenario constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartScenario Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Params = { "Params", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventStartScenario_Parms, Params), Z_Construct_UScriptStruct_FNLTScenarioParams, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Params_MetaData), NewProp_Params_MetaData) }; // d42eeb8e04e5a10ad01878ca226486452c71fe23
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTScenarioManagerSubsystem_eventStartScenario_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Params,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartScenario Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "StartScenario", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventStartScenario_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventStartScenario_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StartScenario(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execStartScenario)
{
	P_GET_STRUCT_REF(FNLTScenarioParams,Z_Param_Out_Params);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->StartScenario(Z_Param_Out_Params);
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function StartScenario ************************

// ********** Begin Class UNLTScenarioManagerSubsystem Function StartScenarioWithAsset *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StartScenarioWithAsset_Statics
struct UHT_STATICS
{
	struct NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms
	{
		FNLTScenarioParams Params;
		UScenarioDataAsset* Scenario;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n     * Scenario-driven start: like StartScenario, but derives the need-growth\n     * multiplier from the scenario definition (aversiveness + cognitive demand)\n     * and keeps the asset for inspection (GetActiveScenario).\n     */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scenario-driven start: like StartScenario, but derives the need-growth\nmultiplier from the scenario definition (aversiveness + cognitive demand)\nand keeps the asset for inspection (GetActiveScenario)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Params_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartScenarioWithAsset constinit property declarations ****************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Params;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Scenario;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StartScenarioWithAsset constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StartScenarioWithAsset Property Definitions ***************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Params = { "Params", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms, Params), Z_Construct_UScriptStruct_FNLTScenarioParams, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Params_MetaData), NewProp_Params_MetaData) }; // d42eeb8e04e5a10ad01878ca226486452c71fe23
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Scenario = { "Scenario", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms, Scenario), Z_Construct_UClass_UScenarioDataAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Params,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Scenario,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StartScenarioWithAsset Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "StartScenarioWithAsset", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTScenarioManagerSubsystem_eventStartScenarioWithAsset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StartScenarioWithAsset(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execStartScenarioWithAsset)
{
	P_GET_STRUCT_REF(FNLTScenarioParams,Z_Param_Out_Params);
	P_GET_OBJECT(UScenarioDataAsset,Z_Param_Scenario);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->StartScenarioWithAsset(Z_Param_Out_Params,Z_Param_Scenario);
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function StartScenarioWithAsset ***************

// ********** Begin Class UNLTScenarioManagerSubsystem Function StopScenario ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StopScenario_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Despawns all scenario agents and stops the run. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Despawns all scenario agents and stops the run." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StopScenario constinit property declarations **************************
// ********** End Function StopScenario constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTScenarioManagerSubsystem, nullptr, "StopScenario", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StopScenario(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTScenarioManagerSubsystem::execStopScenario)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopScenario();
	P_NATIVE_END;
}
// ********** End Class UNLTScenarioManagerSubsystem Function StopScenario *************************

// ********** Begin Class UNLTScenarioManagerSubsystem *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTScenarioManagerSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Owns the lifecycle of a demo scenario run:\n *  - deterministic agent spawning (via UNLTAgentSpawnerSubsystem)\n *  - simulation clock advancement (StepTick once per TickScenarioManager call)\n *  - periodic deterministic checkpoints (state hash over identity-sorted agents)\n *  - headless self-test mode for the QA determinism gate:\n *      run N ticks, log checkpoints + final hash, then exit cleanly.\n */" },
#endif
		{ "IncludePath", "Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTScenarioManagerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Owns the lifecycle of a demo scenario run:\n - deterministic agent spawning (via UNLTAgentSpawnerSubsystem)\n - simulation clock advancement (StepTick once per TickScenarioManager call)\n - periodic deterministic checkpoints (state hash over identity-sorted agents)\n - headless self-test mode for the QA determinism gate:\n     run N ticks, log checkpoints + final hash, then exit cleanly." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTScenarioManagerSubsystem constinit property declarations *************
// ********** End Class UNLTScenarioManagerSubsystem constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetActiveParams"), .Pointer = &UNLTScenarioManagerSubsystem::execGetActiveParams },
		{ .NameUTF8 = UTF8TEXT("GetActiveScenario"), .Pointer = &UNLTScenarioManagerSubsystem::execGetActiveScenario },
		{ .NameUTF8 = UTF8TEXT("GetEnvironmentVariationSubsystem"), .Pointer = &UNLTScenarioManagerSubsystem::execGetEnvironmentVariationSubsystem },
		{ .NameUTF8 = UTF8TEXT("GetScenarioTick"), .Pointer = &UNLTScenarioManagerSubsystem::execGetScenarioTick },
		{ .NameUTF8 = UTF8TEXT("IsScenarioActive"), .Pointer = &UNLTScenarioManagerSubsystem::execIsScenarioActive },
		{ .NameUTF8 = UTF8TEXT("StartScenario"), .Pointer = &UNLTScenarioManagerSubsystem::execStartScenario },
		{ .NameUTF8 = UTF8TEXT("StartScenarioWithAsset"), .Pointer = &UNLTScenarioManagerSubsystem::execStartScenarioWithAsset },
		{ .NameUTF8 = UTF8TEXT("StopScenario"), .Pointer = &UNLTScenarioManagerSubsystem::execStopScenario },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetActiveParams, "GetActiveParams" }, // 257ad8546bf0b0919af3b3ae7a67a056866f2f23
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetActiveScenario, "GetActiveScenario" }, // f710ecac6aac93e1502d57f1d3668399694ba402
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetEnvironmentVariationSubsystem, "GetEnvironmentVariationSubsystem" }, // 753e5afbf58562908ac788ea00be1552843abeee
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_GetScenarioTick, "GetScenarioTick" }, // 59d8a15512952557af807a6eefa80c7075568501
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_IsScenarioActive, "IsScenarioActive" }, // 8e2f389b36351124587f31cc6533a0a5750342ac
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StartScenario, "StartScenario" }, // 08bf4b7a67551c84dea8f77abbe9abe685cc8304
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StartScenarioWithAsset, "StartScenarioWithAsset" }, // 4f09aabf8eb758c3b9503d3e41c030099abb581e
		{ &Z_Construct_UFunction_UNLTScenarioManagerSubsystem_StopScenario, "StopScenario" }, // 5b06bcc23cc7e47536610ac5aa4e248e62857670
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTScenarioManagerSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTScenarioManagerSubsystem,
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
static void UNLTScenarioManagerSubsystem_StaticRegisterNativesUNLTScenarioManagerSubsystem()
{
	UClass* Class = UNLTScenarioManagerSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem;
UClass* Z_Construct_UClass_UNLTScenarioManagerSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTScenarioManagerSubsystem;
		if (!Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTScenarioManagerSubsystem"),
				Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem.InnerSingleton,
				UNLTScenarioManagerSubsystem_StaticRegisterNativesUNLTScenarioManagerSubsystem,
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
		return Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTScenarioManagerSubsystem::UNLTScenarioManagerSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTScenarioManagerSubsystem);
UNLTScenarioManagerSubsystem::~UNLTScenarioManagerSubsystem() {}
// ********** End Class UNLTScenarioManagerSubsystem ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTScenarioParams, Z_Construct_UScriptStruct_FNLTScenarioParams_Statics::NewStructOps, TEXT("NLTScenarioParams"),&Z_Registration_Info_UScriptStruct_FNLTScenarioParams, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTScenarioParams), 3559844750U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTScenarioManagerSubsystem, TEXT("UNLTScenarioManagerSubsystem"), &Z_Registration_Info_UClass_UNLTScenarioManagerSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTScenarioManagerSubsystem), 90374969U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h__Script_WorldEngine_e7561a424303b48fb446e95d5de157f5ba6d3a42{
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
