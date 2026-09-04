// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scaling/NLTPopulationScaler.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTPopulationScaler() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTPopulationScaler(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScaleMetrics(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTPopulationScaler(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTScaleMetrics **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTScaleMetrics_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTScaleMetrics>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTScaleMetrics); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentCount_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FrameTime_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulationTickTime_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MemoryUsageMB_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MassProcessorTime_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateTreeTime_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NavigationTime_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveEntities_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CognitionLatency_MetaData[] = {
		{ "Category", "NLTScaleMetrics" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTScaleMetrics constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_AgentCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FrameTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SimulationTickTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MemoryUsageMB;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MassProcessorTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StateTreeTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NavigationTime;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ActiveEntities;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CognitionLatency;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTScaleMetrics constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTScaleMetrics>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTScaleMetrics Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AgentCount = { "AgentCount", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, AgentCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentCount_MetaData), NewProp_AgentCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FrameTime = { "FrameTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, FrameTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FrameTime_MetaData), NewProp_FrameTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SimulationTickTime = { "SimulationTickTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, SimulationTickTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulationTickTime_MetaData), NewProp_SimulationTickTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MemoryUsageMB = { "MemoryUsageMB", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, MemoryUsageMB), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MemoryUsageMB_MetaData), NewProp_MemoryUsageMB_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MassProcessorTime = { "MassProcessorTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, MassProcessorTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MassProcessorTime_MetaData), NewProp_MassProcessorTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_StateTreeTime = { "StateTreeTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, StateTreeTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateTreeTime_MetaData), NewProp_StateTreeTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NavigationTime = { "NavigationTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, NavigationTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NavigationTime_MetaData), NewProp_NavigationTime_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ActiveEntities = { "ActiveEntities", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, ActiveEntities), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveEntities_MetaData), NewProp_ActiveEntities_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CognitionLatency = { "CognitionLatency", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScaleMetrics, CognitionLatency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CognitionLatency_MetaData), NewProp_CognitionLatency_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FrameTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SimulationTickTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MemoryUsageMB,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MassProcessorTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StateTreeTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NavigationTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEntities,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitionLatency,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTScaleMetrics Property Definitions *******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTScaleMetrics",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTScaleMetrics>(),
	alignof(FNLTScaleMetrics),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTScaleMetrics;
UScriptStruct* Z_Construct_UScriptStruct_FNLTScaleMetrics(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTScaleMetrics.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTScaleMetrics.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTScaleMetrics, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTScaleMetrics"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTScaleMetrics.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTScaleMetrics.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTScaleMetrics.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTScaleMetrics.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTScaleMetrics ****************************************************

// ********** Begin Class UNLTPopulationScaler Function GetCurrentMetrics **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPopulationScaler_GetCurrentMetrics_Statics
struct UHT_STATICS
{
	struct NLTPopulationScaler_eventGetCurrentMetrics_Parms
	{
		FNLTScaleMetrics ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scaling" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentMetrics constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentMetrics constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentMetrics Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPopulationScaler_eventGetCurrentMetrics_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTScaleMetrics, METADATA_PARAMS(0, nullptr) }; // 1c7c2a3b502f459a213e8f028fca57b756f3f9a6
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCurrentMetrics Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPopulationScaler, nullptr, "GetCurrentMetrics", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPopulationScaler_eventGetCurrentMetrics_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPopulationScaler_eventGetCurrentMetrics_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPopulationScaler_GetCurrentMetrics(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPopulationScaler::execGetCurrentMetrics)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTScaleMetrics*)Z_Param__Result=P_THIS->GetCurrentMetrics();
	P_NATIVE_END;
}
// ********** End Class UNLTPopulationScaler Function GetCurrentMetrics ****************************

// ********** Begin Class UNLTPopulationScaler Function IsBenchmarking *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPopulationScaler_IsBenchmarking_Statics
struct UHT_STATICS
{
	struct NLTPopulationScaler_eventIsBenchmarking_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scaling" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsBenchmarking constinit property declarations ************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTPopulationScaler_eventIsBenchmarking_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsBenchmarking constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsBenchmarking Property Definitions ***********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTPopulationScaler_eventIsBenchmarking_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsBenchmarking Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPopulationScaler, nullptr, "IsBenchmarking", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPopulationScaler_eventIsBenchmarking_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPopulationScaler_eventIsBenchmarking_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPopulationScaler_IsBenchmarking(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPopulationScaler::execIsBenchmarking)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsBenchmarking();
	P_NATIVE_END;
}
// ********** End Class UNLTPopulationScaler Function IsBenchmarking *******************************

// ********** Begin Class UNLTPopulationScaler Function ScalePopulation ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPopulationScaler_ScalePopulation_Statics
struct UHT_STATICS
{
	struct NLTPopulationScaler_eventScalePopulation_Parms
	{
		int32 NewAgentCount;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scaling" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ScalePopulation constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewAgentCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ScalePopulation constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ScalePopulation Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NewAgentCount = { "NewAgentCount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPopulationScaler_eventScalePopulation_Parms, NewAgentCount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewAgentCount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ScalePopulation Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPopulationScaler, nullptr, "ScalePopulation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPopulationScaler_eventScalePopulation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPopulationScaler_eventScalePopulation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPopulationScaler_ScalePopulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPopulationScaler::execScalePopulation)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_NewAgentCount);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ScalePopulation(Z_Param_NewAgentCount);
	P_NATIVE_END;
}
// ********** End Class UNLTPopulationScaler Function ScalePopulation ******************************

// ********** Begin Class UNLTPopulationScaler Function StartBenchmark *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPopulationScaler_StartBenchmark_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scaling" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartBenchmark constinit property declarations ************************
// ********** End Function StartBenchmark constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPopulationScaler, nullptr, "StartBenchmark", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTPopulationScaler_StartBenchmark(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPopulationScaler::execStartBenchmark)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartBenchmark();
	P_NATIVE_END;
}
// ********** End Class UNLTPopulationScaler Function StartBenchmark *******************************

// ********** Begin Class UNLTPopulationScaler Function StopBenchmark ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPopulationScaler_StopBenchmark_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scaling" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StopBenchmark constinit property declarations *************************
// ********** End Function StopBenchmark constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPopulationScaler, nullptr, "StopBenchmark", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTPopulationScaler_StopBenchmark(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPopulationScaler::execStopBenchmark)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopBenchmark();
	P_NATIVE_END;
}
// ********** End Class UNLTPopulationScaler Function StopBenchmark ********************************

// ********** Begin Class UNLTPopulationScaler *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTPopulationScaler_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Scaling/NLTPopulationScaler.h" },
		{ "ModuleRelativePath", "Public/Scaling/NLTPopulationScaler.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTPopulationScaler constinit property declarations *********************
// ********** End Class UNLTPopulationScaler constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentMetrics"), .Pointer = &UNLTPopulationScaler::execGetCurrentMetrics },
		{ .NameUTF8 = UTF8TEXT("IsBenchmarking"), .Pointer = &UNLTPopulationScaler::execIsBenchmarking },
		{ .NameUTF8 = UTF8TEXT("ScalePopulation"), .Pointer = &UNLTPopulationScaler::execScalePopulation },
		{ .NameUTF8 = UTF8TEXT("StartBenchmark"), .Pointer = &UNLTPopulationScaler::execStartBenchmark },
		{ .NameUTF8 = UTF8TEXT("StopBenchmark"), .Pointer = &UNLTPopulationScaler::execStopBenchmark },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTPopulationScaler_GetCurrentMetrics, "GetCurrentMetrics" }, // 7475ca7592a4761b45e1c22f705a14b64b06473a
		{ &Z_Construct_UFunction_UNLTPopulationScaler_IsBenchmarking, "IsBenchmarking" }, // a40ff8e2d4223533249774d1a881c6f96e1c37e7
		{ &Z_Construct_UFunction_UNLTPopulationScaler_ScalePopulation, "ScalePopulation" }, // a6d8c677bb3ca393a5a8d8d93fa8e61dfde4c808
		{ &Z_Construct_UFunction_UNLTPopulationScaler_StartBenchmark, "StartBenchmark" }, // 44a1e138e176a9e7c6d776ce5f1190f81fd094f7
		{ &Z_Construct_UFunction_UNLTPopulationScaler_StopBenchmark, "StopBenchmark" }, // 4cbc8f8244925ca26ab60a247c901d661e4c22f7
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTPopulationScaler>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTPopulationScaler,
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
static void UNLTPopulationScaler_StaticRegisterNativesUNLTPopulationScaler()
{
	UClass* Class = UNLTPopulationScaler::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTPopulationScaler;
UClass* Z_Construct_UClass_UNLTPopulationScaler(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTPopulationScaler;
		if (!Z_Registration_Info_UClass_UNLTPopulationScaler.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTPopulationScaler"),
				Z_Registration_Info_UClass_UNLTPopulationScaler.InnerSingleton,
				UNLTPopulationScaler_StaticRegisterNativesUNLTPopulationScaler,
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
		return Z_Registration_Info_UClass_UNLTPopulationScaler.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTPopulationScaler.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTPopulationScaler.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTPopulationScaler.OuterSingleton;
}
#undef UHT_STATICS
UNLTPopulationScaler::UNLTPopulationScaler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTPopulationScaler);
UNLTPopulationScaler::~UNLTPopulationScaler() {}
// ********** End Class UNLTPopulationScaler *******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTScaleMetrics, Z_Construct_UScriptStruct_FNLTScaleMetrics_Statics::NewStructOps, TEXT("NLTScaleMetrics"),&Z_Registration_Info_UScriptStruct_FNLTScaleMetrics, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTScaleMetrics), 477899323U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTPopulationScaler, TEXT("UNLTPopulationScaler"), &Z_Registration_Info_UClass_UNLTPopulationScaler, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTPopulationScaler), 72957942U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h__Script_WorldEngine_82a1e604e14f33cf444fcd1c9cefac3ab530e254{
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
