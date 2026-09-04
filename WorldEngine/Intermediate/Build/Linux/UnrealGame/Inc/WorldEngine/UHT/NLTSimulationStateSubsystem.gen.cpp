// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/NLTSimulationStateSubsystem.h"
#include "Core/NLTSimulationState.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTSimulationStateSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentState(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTRandomStream(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSimulationState(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationStateSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationStateSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UNLTSimulationStateSubsystem Function CreateSnapshot *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_CreateSnapshot_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventCreateSnapshot_Parms
	{
		FNLTSimulationState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateSnapshot constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateSnapshot constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateSnapshot Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventCreateSnapshot_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTSimulationState, METADATA_PARAMS(0, nullptr) }; // d2514c3a27d3f8d8b369beaa828692d48e3e4d8f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function CreateSnapshot Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "CreateSnapshot", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventCreateSnapshot_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventCreateSnapshot_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_CreateSnapshot(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execCreateSnapshot)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTSimulationState*)Z_Param__Result=P_THIS->CreateSnapshot();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function CreateSnapshot ***********************

// ********** Begin Class UNLTSimulationStateSubsystem Function GetAgentState **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetAgentState_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventGetAgentState_Parms
	{
		FName AgentId;
		FNLTAgentState OutAgentState;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAgentState constinit property declarations *************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutAgentState;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSimulationStateSubsystem_eventGetAgentState_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAgentState constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAgentState Property Definitions ************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetAgentState_Parms, AgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutAgentState = { "OutAgentState", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetAgentState_Parms, OutAgentState), Z_Construct_UScriptStruct_FNLTAgentState, METADATA_PARAMS(0, nullptr) }; // 8f96309e449e8b4e3589b2439e4bb2f68406d13e
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSimulationStateSubsystem_eventGetAgentState_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutAgentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAgentState Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "GetAgentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventGetAgentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventGetAgentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetAgentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execGetAgentState)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentId);
	P_GET_STRUCT_REF(FNLTAgentState,Z_Param_Out_OutAgentState);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetAgentState(Z_Param_AgentId,Z_Param_Out_OutAgentState);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function GetAgentState ************************

// ********** Begin Class UNLTSimulationStateSubsystem Function GetAllAgentStates ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetAllAgentStates_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventGetAllAgentStates_Parms
	{
		TArray<FNLTAgentState> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllAgentStates constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllAgentStates constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllAgentStates Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTAgentState, METADATA_PARAMS(0, nullptr) }; // 8f96309e449e8b4e3589b2439e4bb2f68406d13e
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetAllAgentStates_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // 8f96309e449e8b4e3589b2439e4bb2f68406d13e
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllAgentStates Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "GetAllAgentStates", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventGetAllAgentStates_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventGetAllAgentStates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetAllAgentStates(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execGetAllAgentStates)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FNLTAgentState>*)Z_Param__Result=P_THIS->GetAllAgentStates();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function GetAllAgentStates ********************

// ********** Begin Class UNLTSimulationStateSubsystem Function GetCurrentState ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetCurrentState_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventGetCurrentState_Parms
	{
		FNLTSimulationState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentState constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentState constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentState Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetCurrentState_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTSimulationState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // d2514c3a27d3f8d8b369beaa828692d48e3e4d8f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCurrentState Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "GetCurrentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventGetCurrentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventGetCurrentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetCurrentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execGetCurrentState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTSimulationState*)Z_Param__Result=P_THIS->GetCurrentState();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function GetCurrentState **********************

// ********** Begin Class UNLTSimulationStateSubsystem Function GetMutableState ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetMutableState_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventGetMutableState_Parms
	{
		FNLTSimulationState ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMutableState constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMutableState constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMutableState Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetMutableState_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTSimulationState, METADATA_PARAMS(0, nullptr) }; // d2514c3a27d3f8d8b369beaa828692d48e3e4d8f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMutableState Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "GetMutableState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventGetMutableState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventGetMutableState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetMutableState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execGetMutableState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTSimulationState*)Z_Param__Result=P_THIS->GetMutableState();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function GetMutableState **********************

// ********** Begin Class UNLTSimulationStateSubsystem Function GetRNG *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetRNG_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventGetRNG_Parms
	{
		FNLTRandomStream ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRNG constinit property declarations ********************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRNG constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRNG Property Definitions *******************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetRNG_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTRandomStream, METADATA_PARAMS(0, nullptr) }; // a08a84f563486ccbb5a77664f5a1b7a394e9672d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRNG Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "GetRNG", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventGetRNG_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventGetRNG_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetRNG(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execGetRNG)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTRandomStream*)Z_Param__Result=P_THIS->GetRNG();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function GetRNG *******************************

// ********** Begin Class UNLTSimulationStateSubsystem Function GetRNGConst ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetRNGConst_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventGetRNGConst_Parms
	{
		FNLTRandomStream ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetRNGConst constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRNGConst constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRNGConst Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventGetRNGConst_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTRandomStream, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // a08a84f563486ccbb5a77664f5a1b7a394e9672d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRNGConst Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "GetRNGConst", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventGetRNGConst_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventGetRNGConst_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetRNGConst(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execGetRNGConst)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTRandomStream*)Z_Param__Result=P_THIS->GetRNGConst();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function GetRNGConst **************************

// ********** Begin Class UNLTSimulationStateSubsystem Function RemoveAgentState *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_RemoveAgentState_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventRemoveAgentState_Parms
	{
		FName AgentId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RemoveAgentState constinit property declarations **********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSimulationStateSubsystem_eventRemoveAgentState_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RemoveAgentState constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RemoveAgentState Property Definitions *********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventRemoveAgentState_Parms, AgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSimulationStateSubsystem_eventRemoveAgentState_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RemoveAgentState Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "RemoveAgentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventRemoveAgentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventRemoveAgentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_RemoveAgentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execRemoveAgentState)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->RemoveAgentState(Z_Param_AgentId);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function RemoveAgentState *********************

// ********** Begin Class UNLTSimulationStateSubsystem Function ResetState *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_ResetState_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResetState constinit property declarations ****************************
// ********** End Function ResetState constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "ResetState", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_ResetState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execResetState)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetState();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function ResetState ***************************

// ********** Begin Class UNLTSimulationStateSubsystem Function RestoreFromSnapshot ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_RestoreFromSnapshot_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventRestoreFromSnapshot_Parms
	{
		FNLTSimulationState Snapshot;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Snapshot_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RestoreFromSnapshot constinit property declarations *******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Snapshot;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RestoreFromSnapshot constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RestoreFromSnapshot Property Definitions ******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Snapshot = { "Snapshot", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventRestoreFromSnapshot_Parms, Snapshot), Z_Construct_UScriptStruct_FNLTSimulationState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Snapshot_MetaData), NewProp_Snapshot_MetaData) }; // d2514c3a27d3f8d8b369beaa828692d48e3e4d8f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Snapshot,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RestoreFromSnapshot Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "RestoreFromSnapshot", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventRestoreFromSnapshot_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventRestoreFromSnapshot_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_RestoreFromSnapshot(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execRestoreFromSnapshot)
{
	P_GET_STRUCT_REF(FNLTSimulationState,Z_Param_Out_Snapshot);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RestoreFromSnapshot(Z_Param_Out_Snapshot);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function RestoreFromSnapshot ******************

// ********** Begin Class UNLTSimulationStateSubsystem Function SetAgentState **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_SetAgentState_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventSetAgentState_Parms
	{
		FNLTAgentState AgentState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetAgentState constinit property declarations *************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_AgentState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetAgentState constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetAgentState Property Definitions ************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_AgentState = { "AgentState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventSetAgentState_Parms, AgentState), Z_Construct_UScriptStruct_FNLTAgentState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentState_MetaData), NewProp_AgentState_MetaData) }; // 8f96309e449e8b4e3589b2439e4bb2f68406d13e
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetAgentState Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "SetAgentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventSetAgentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventSetAgentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_SetAgentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execSetAgentState)
{
	P_GET_STRUCT_REF(FNLTAgentState,Z_Param_Out_AgentState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetAgentState(Z_Param_Out_AgentState);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function SetAgentState ************************

// ********** Begin Class UNLTSimulationStateSubsystem Function SetSeed ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationStateSubsystem_SetSeed_Statics
struct UHT_STATICS
{
	struct NLTSimulationStateSubsystem_eventSetSeed_Parms
	{
		int32 NewSeed;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetSeed constinit property declarations *******************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_NewSeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetSeed constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetSeed Property Definitions ******************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NewSeed = { "NewSeed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationStateSubsystem_eventSetSeed_Parms, NewSeed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewSeed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetSeed Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationStateSubsystem, nullptr, "SetSeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationStateSubsystem_eventSetSeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationStateSubsystem_eventSetSeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationStateSubsystem_SetSeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationStateSubsystem::execSetSeed)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_NewSeed);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSeed(Z_Param_NewSeed);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationStateSubsystem Function SetSeed ******************************

// ********** Begin Class UNLTSimulationStateSubsystem *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTSimulationStateSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Core/NLTSimulationStateSubsystem.h" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTSimulationStateSubsystem constinit property declarations *************
// ********** End Class UNLTSimulationStateSubsystem constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CreateSnapshot"), .Pointer = &UNLTSimulationStateSubsystem::execCreateSnapshot },
		{ .NameUTF8 = UTF8TEXT("GetAgentState"), .Pointer = &UNLTSimulationStateSubsystem::execGetAgentState },
		{ .NameUTF8 = UTF8TEXT("GetAllAgentStates"), .Pointer = &UNLTSimulationStateSubsystem::execGetAllAgentStates },
		{ .NameUTF8 = UTF8TEXT("GetCurrentState"), .Pointer = &UNLTSimulationStateSubsystem::execGetCurrentState },
		{ .NameUTF8 = UTF8TEXT("GetMutableState"), .Pointer = &UNLTSimulationStateSubsystem::execGetMutableState },
		{ .NameUTF8 = UTF8TEXT("GetRNG"), .Pointer = &UNLTSimulationStateSubsystem::execGetRNG },
		{ .NameUTF8 = UTF8TEXT("GetRNGConst"), .Pointer = &UNLTSimulationStateSubsystem::execGetRNGConst },
		{ .NameUTF8 = UTF8TEXT("RemoveAgentState"), .Pointer = &UNLTSimulationStateSubsystem::execRemoveAgentState },
		{ .NameUTF8 = UTF8TEXT("ResetState"), .Pointer = &UNLTSimulationStateSubsystem::execResetState },
		{ .NameUTF8 = UTF8TEXT("RestoreFromSnapshot"), .Pointer = &UNLTSimulationStateSubsystem::execRestoreFromSnapshot },
		{ .NameUTF8 = UTF8TEXT("SetAgentState"), .Pointer = &UNLTSimulationStateSubsystem::execSetAgentState },
		{ .NameUTF8 = UTF8TEXT("SetSeed"), .Pointer = &UNLTSimulationStateSubsystem::execSetSeed },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_CreateSnapshot, "CreateSnapshot" }, // 774a6cd84a51a8e8869e9ca7d7f91deacb8325eb
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetAgentState, "GetAgentState" }, // e98fc0df798db7d3018c2a72b71014bfd151365a
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetAllAgentStates, "GetAllAgentStates" }, // bb16a9df22c4ae554cfdb79f30fb90e63cfc91e3
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetCurrentState, "GetCurrentState" }, // 2bdd7a122c7c0e5620fb4c17a6897b24e3a205c2
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetMutableState, "GetMutableState" }, // 38bf15ee358cacff05f31ce8a174c854d2911fdf
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetRNG, "GetRNG" }, // 78d0f118600ad061581eb4f67792b46a7bbcb635
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_GetRNGConst, "GetRNGConst" }, // d1bbf727bb71692518fa9c298422f63b1d4c3ec8
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_RemoveAgentState, "RemoveAgentState" }, // 7c0fb39a384bbb15889606b460ad244f707cf5fe
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_ResetState, "ResetState" }, // 7174641d92a796973eba34618053be3ff16a80e4
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_RestoreFromSnapshot, "RestoreFromSnapshot" }, // 0fc71d92707dbde422f76b44208310c32e5b2327
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_SetAgentState, "SetAgentState" }, // d4a5913d27503acc10f524f93668840a0dbbb059
		{ &Z_Construct_UFunction_UNLTSimulationStateSubsystem_SetSeed, "SetSeed" }, // d7fa0c739ce11cad7400b86e12c974731931aefd
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTSimulationStateSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTSimulationStateSubsystem,
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
static void UNLTSimulationStateSubsystem_StaticRegisterNativesUNLTSimulationStateSubsystem()
{
	UClass* Class = UNLTSimulationStateSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTSimulationStateSubsystem;
UClass* Z_Construct_UClass_UNLTSimulationStateSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTSimulationStateSubsystem;
		if (!Z_Registration_Info_UClass_UNLTSimulationStateSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTSimulationStateSubsystem"),
				Z_Registration_Info_UClass_UNLTSimulationStateSubsystem.InnerSingleton,
				UNLTSimulationStateSubsystem_StaticRegisterNativesUNLTSimulationStateSubsystem,
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
		return Z_Registration_Info_UClass_UNLTSimulationStateSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTSimulationStateSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTSimulationStateSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTSimulationStateSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTSimulationStateSubsystem::UNLTSimulationStateSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTSimulationStateSubsystem);
UNLTSimulationStateSubsystem::~UNLTSimulationStateSubsystem() {}
// ********** End Class UNLTSimulationStateSubsystem ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTSimulationStateSubsystem, TEXT("UNLTSimulationStateSubsystem"), &Z_Registration_Info_UClass_UNLTSimulationStateSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTSimulationStateSubsystem), 3414948549U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h__Script_WorldEngine_6eaff48e71561f383a363297813465850761b2a2{
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
