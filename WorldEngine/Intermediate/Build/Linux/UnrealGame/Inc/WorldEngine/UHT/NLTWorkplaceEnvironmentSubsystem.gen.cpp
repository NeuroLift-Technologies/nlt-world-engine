// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/NLTWorkplaceEnvironmentSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTWorkplaceEnvironmentSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function ConfigureEnvironment **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_ConfigureEnvironment_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms
	{
		FName ScenarioId;
		int32 RoomSeed;
		bool bStartSimulation;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * (Re)configure the workplace environment from a master room seed.\n\x09 * Derives all category streams, registers the standard workplace rooms\n\x09 * with deterministic initial state, applies seeded micro-variation, and\n\x09 * optionally starts the clock.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "(Re)configure the workplace environment from a master room seed.\nDerives all category streams, registers the standard workplace rooms\nwith deterministic initial state, applies seeded micro-variation, and\noptionally starts the clock." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ConfigureEnvironment constinit property declarations ******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ScenarioId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RoomSeed;
	static void NewProp_bStartSimulation_SetBit(void* Obj)
	{
		((NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms*)Obj)->bStartSimulation = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bStartSimulation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ConfigureEnvironment constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ConfigureEnvironment Property Definitions *****************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ScenarioId = { "ScenarioId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms, ScenarioId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RoomSeed = { "RoomSeed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms, RoomSeed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bStartSimulation = { "bStartSimulation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms), &UHT_STATICS::NewProp_bStartSimulation_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScenarioId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomSeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bStartSimulation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ConfigureEnvironment Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "ConfigureEnvironment", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventConfigureEnvironment_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_ConfigureEnvironment(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execConfigureEnvironment)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_ScenarioId);
	P_GET_PROPERTY(FIntProperty,Z_Param_RoomSeed);
	P_GET_UBOOL(Z_Param_bStartSimulation);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ConfigureEnvironment(Z_Param_ScenarioId,Z_Param_RoomSeed,Z_Param_bStartSimulation);
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function ConfigureEnvironment ************

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function DeserializeEnvironmentState ***
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_DeserializeEnvironmentState_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventDeserializeEnvironmentState_Parms
	{
		TArray<uint8> InData;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Restore a previously serialized environment state. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Restore a previously serialized environment state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DeserializeEnvironmentState constinit property declarations ***********
	static const UECodeGen_Private::FBytePropertyParams NewProp_InData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InData;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTWorkplaceEnvironmentSubsystem_eventDeserializeEnvironmentState_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeserializeEnvironmentState constinit property declarations *************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeserializeEnvironmentState Property Definitions **********************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_InData_Inner = { "InData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_InData = { "InData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventDeserializeEnvironmentState_Parms, InData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InData_MetaData), NewProp_InData_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTWorkplaceEnvironmentSubsystem_eventDeserializeEnvironmentState_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeserializeEnvironmentState Property Definitions ************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "DeserializeEnvironmentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventDeserializeEnvironmentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventDeserializeEnvironmentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_DeserializeEnvironmentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execDeserializeEnvironmentState)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_InData);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DeserializeEnvironmentState(Z_Param_Out_InData);
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function DeserializeEnvironmentState *****

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function GetMasterSeed *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_GetMasterSeed_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventGetMasterSeed_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the active master room seed. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the active master room seed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetMasterSeed constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMasterSeed constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMasterSeed Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventGetMasterSeed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMasterSeed Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "GetMasterSeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventGetMasterSeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventGetMasterSeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_GetMasterSeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execGetMasterSeed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetMasterSeed();
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function GetMasterSeed *******************

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function GetScenarioId *****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_GetScenarioId_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventGetScenarioId_Parms
	{
		FName ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the active scenario id (may be NAME_None for a bare environment). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the active scenario id (may be NAME_None for a bare environment)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetScenarioId constinit property declarations *************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetScenarioId constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetScenarioId Property Definitions ************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventGetScenarioId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetScenarioId Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "GetScenarioId", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventGetScenarioId_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventGetScenarioId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_GetScenarioId(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execGetScenarioId)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FName*)Z_Param__Result=P_THIS->GetScenarioId();
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function GetScenarioId *******************

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function HandleAuthoritativeTick *******
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_HandleAuthoritativeTick_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventHandleAuthoritativeTick_Parms
	{
		int32 Tick;
		double WorldTimeSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** React to each authoritative clock tick: publish time-of-day + refresh rooms. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "React to each authoritative clock tick: publish time-of-day + refresh rooms." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HandleAuthoritativeTick constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Tick;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_WorldTimeSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HandleAuthoritativeTick constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HandleAuthoritativeTick Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Tick = { "Tick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventHandleAuthoritativeTick_Parms, Tick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDoublePropertyParams UHT_STATICS::NewProp_WorldTimeSeconds = { "WorldTimeSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventHandleAuthoritativeTick_Parms, WorldTimeSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldTimeSeconds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HandleAuthoritativeTick Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "HandleAuthoritativeTick", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventHandleAuthoritativeTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventHandleAuthoritativeTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_HandleAuthoritativeTick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execHandleAuthoritativeTick)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Tick);
	P_GET_PROPERTY(FDoubleProperty,Z_Param_WorldTimeSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->HandleAuthoritativeTick(Z_Param_Tick,Z_Param_WorldTimeSeconds);
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function HandleAuthoritativeTick *********

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function IsRunning *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_IsRunning_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventIsRunning_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the clock is currently running. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the clock is currently running." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsRunning constinit property declarations *****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTWorkplaceEnvironmentSubsystem_eventIsRunning_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsRunning constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsRunning Property Definitions ****************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTWorkplaceEnvironmentSubsystem_eventIsRunning_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsRunning Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "IsRunning", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventIsRunning_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventIsRunning_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_IsRunning(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execIsRunning)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsRunning();
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function IsRunning ***********************

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function SerializeEnvironmentState *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_SerializeEnvironmentState_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventSerializeEnvironmentState_Parms
	{
		TArray<uint8> OutData;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Full environment persistence: clock + seed streams + all room states. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Full environment persistence: clock + seed streams + all room states." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SerializeEnvironmentState constinit property declarations *************
	static const UECodeGen_Private::FBytePropertyParams NewProp_OutData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SerializeEnvironmentState constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SerializeEnvironmentState Property Definitions ************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_OutData_Inner = { "OutData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutData = { "OutData", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventSerializeEnvironmentState_Parms, OutData), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SerializeEnvironmentState Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "SerializeEnvironmentState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventSerializeEnvironmentState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventSerializeEnvironmentState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_SerializeEnvironmentState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execSerializeEnvironmentState)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_OutData);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SerializeEnvironmentState(Z_Param_Out_OutData);
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function SerializeEnvironmentState *******

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function StartEnvironmentSimulation ****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StartEnvironmentSimulation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Start advancing the authoritative clock. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Start advancing the authoritative clock." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StartEnvironmentSimulation constinit property declarations ************
// ********** End Function StartEnvironmentSimulation constinit property declarations **************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "StartEnvironmentSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StartEnvironmentSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execStartEnvironmentSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartEnvironmentSimulation();
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function StartEnvironmentSimulation ******

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function StepEnvironmentSimulation *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StepEnvironmentSimulation_Statics
struct UHT_STATICS
{
	struct NLTWorkplaceEnvironmentSubsystem_eventStepEnvironmentSimulation_Parms
	{
		int32 NumTicks;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Advance the environment by NumTicks fixed clicks. Each tick advances the\n\x09 * clock; the OnAuthoritativeTick handler publishes time-of-day and\n\x09 * periodically refreshes room detail, raising env events. Call once per\n\x09 * frame with 1 (game), or batch N for headless determinism runs.\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Advance the environment by NumTicks fixed clicks. Each tick advances the\nclock; the OnAuthoritativeTick handler publishes time-of-day and\nperiodically refreshes room detail, raising env events. Call once per\nframe with 1 (game), or batch N for headless determinism runs." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StepEnvironmentSimulation constinit property declarations *************
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumTicks;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StepEnvironmentSimulation constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StepEnvironmentSimulation Property Definitions ************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumTicks = { "NumTicks", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTWorkplaceEnvironmentSubsystem_eventStepEnvironmentSimulation_Parms, NumTicks), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumTicks,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StepEnvironmentSimulation Property Definitions **************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "StepEnvironmentSimulation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventStepEnvironmentSimulation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTWorkplaceEnvironmentSubsystem_eventStepEnvironmentSimulation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StepEnvironmentSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execStepEnvironmentSimulation)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_NumTicks);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StepEnvironmentSimulation(Z_Param_NumTicks);
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function StepEnvironmentSimulation *******

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Function StopEnvironmentSimulation *****
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StopEnvironmentSimulation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stop advancing the clock (preserves state for persistence). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop advancing the clock (preserves state for persistence)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function StopEnvironmentSimulation constinit property declarations *************
// ********** End Function StopEnvironmentSimulation constinit property declarations ***************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, nullptr, "StopEnvironmentSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StopEnvironmentSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTWorkplaceEnvironmentSubsystem::execStopEnvironmentSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopEnvironmentSimulation();
	P_NATIVE_END;
}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Function StopEnvironmentSimulation *******

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Environment-only simulation driver for Workplace_Level.\n *\n * Ties the authoritative clock (UNLTSimulationClockSubsystem), the event bus\n * (UNLTEventBus, environment event channels), the deterministic seed system\n * (UNLTDeterministicSeedSubsystem) and room-state persistence\n * (UNLTRoomStateSubsystem) together into one coherent, reproducible\n * environment pass.\n *\n * Deliberately agent-free: this subsystem never spawns or drives Avatar/Aide/\n * Mass entities. It only advances the environment (time-of-day, lighting,\n * room state) from a single master \"room seed\" so the same seed always\n * produces the same environment events and room states.\n *\n * Usage (from the Workplace_Level GameMode or level Blueprint):\n *   - ConfigureEnvironment(ScenarioId, RoomSeed, bStartSimulation) to seed\n *     everything and register the workplace rooms.\n *   - Each frame while running, call StepEnvironmentSimulation(1) (batch the\n *     count for headless / -game -nullrhi runs) to advance the clock one fixed\n *     tick and emit environment events.\n */" },
#endif
		{ "IncludePath", "Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Environment-only simulation driver for Workplace_Level.\n\nTies the authoritative clock (UNLTSimulationClockSubsystem), the event bus\n(UNLTEventBus, environment event channels), the deterministic seed system\n(UNLTDeterministicSeedSubsystem) and room-state persistence\n(UNLTRoomStateSubsystem) together into one coherent, reproducible\nenvironment pass.\n\nDeliberately agent-free: this subsystem never spawns or drives Avatar/Aide/\nMass entities. It only advances the environment (time-of-day, lighting,\nroom state) from a single master \"room seed\" so the same seed always\nproduces the same environment events and room states.\n\nUsage (from the Workplace_Level GameMode or level Blueprint):\n  - ConfigureEnvironment(ScenarioId, RoomSeed, bStartSimulation) to seed\n    everything and register the workplace rooms.\n  - Each frame while running, call StepEnvironmentSimulation(1) (batch the\n    count for headless / -game -nullrhi runs) to advance the clock one fixed\n    tick and emit environment events." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DetailRefreshIntervalTicks_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of fixed ticks between per-room detail refreshes (default 60). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of fixed ticks between per-room detail refreshes (default 60)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustTemplate_MetaData[] = {
		{ "Category", "NLT|Environment|Workplace" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Optional dust particle template */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTWorkplaceEnvironmentSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional dust particle template" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem constinit property declarations ********
	static const UECodeGen_Private::FIntPropertyParams NewProp_DetailRefreshIntervalTicks;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DustTemplate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNLTWorkplaceEnvironmentSubsystem constinit property declarations **********
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ConfigureEnvironment"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execConfigureEnvironment },
		{ .NameUTF8 = UTF8TEXT("DeserializeEnvironmentState"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execDeserializeEnvironmentState },
		{ .NameUTF8 = UTF8TEXT("GetMasterSeed"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execGetMasterSeed },
		{ .NameUTF8 = UTF8TEXT("GetScenarioId"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execGetScenarioId },
		{ .NameUTF8 = UTF8TEXT("HandleAuthoritativeTick"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execHandleAuthoritativeTick },
		{ .NameUTF8 = UTF8TEXT("IsRunning"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execIsRunning },
		{ .NameUTF8 = UTF8TEXT("SerializeEnvironmentState"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execSerializeEnvironmentState },
		{ .NameUTF8 = UTF8TEXT("StartEnvironmentSimulation"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execStartEnvironmentSimulation },
		{ .NameUTF8 = UTF8TEXT("StepEnvironmentSimulation"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execStepEnvironmentSimulation },
		{ .NameUTF8 = UTF8TEXT("StopEnvironmentSimulation"), .Pointer = &UNLTWorkplaceEnvironmentSubsystem::execStopEnvironmentSimulation },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_ConfigureEnvironment, "ConfigureEnvironment" }, // dbffb3b6d0c17ccf8ab61700651e8a2b97370414
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_DeserializeEnvironmentState, "DeserializeEnvironmentState" }, // 7ad03ddf45a46cb4d0241540da999c4552209047
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_GetMasterSeed, "GetMasterSeed" }, // dd7aaba20139efa47513b6f410fd41000278200e
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_GetScenarioId, "GetScenarioId" }, // 21dbd23020ad4ad185572ca67c17124803f6fdb3
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_HandleAuthoritativeTick, "HandleAuthoritativeTick" }, // 100ed2851150bfd6ce9e02b5d65508524dd6f29b
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_IsRunning, "IsRunning" }, // a5898d695d7cc5271723fb792c93629fe02349f5
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_SerializeEnvironmentState, "SerializeEnvironmentState" }, // c569f672c38daa09cc75326e96b58da686ad3265
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StartEnvironmentSimulation, "StartEnvironmentSimulation" }, // 8ce36511c1e2241fa6d920b23b8e92a9846af8e2
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StepEnvironmentSimulation, "StepEnvironmentSimulation" }, // ab164b7c10f203977390eba118af51845e7bbca6
		{ &Z_Construct_UFunction_UNLTWorkplaceEnvironmentSubsystem_StopEnvironmentSimulation, "StopEnvironmentSimulation" }, // 3d6f78a8af6e3a74edc1aae89146e6bf85af8d95
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTWorkplaceEnvironmentSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem Property Definitions *******************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DetailRefreshIntervalTicks = { "DetailRefreshIntervalTicks", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTWorkplaceEnvironmentSubsystem, DetailRefreshIntervalTicks), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DetailRefreshIntervalTicks_MetaData), NewProp_DetailRefreshIntervalTicks_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DustTemplate = { "DustTemplate", nullptr, (EPropertyFlags)0x0144000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTWorkplaceEnvironmentSubsystem, DustTemplate), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustTemplate_MetaData), NewProp_DustTemplate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DetailRefreshIntervalTicks,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustTemplate,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UNLTWorkplaceEnvironmentSubsystem Property Definitions *********************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UNLTWorkplaceEnvironmentSubsystem_StaticRegisterNativesUNLTWorkplaceEnvironmentSubsystem()
{
	UClass* Class = UNLTWorkplaceEnvironmentSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem;
UClass* Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTWorkplaceEnvironmentSubsystem;
		if (!Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTWorkplaceEnvironmentSubsystem"),
				Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem.InnerSingleton,
				UNLTWorkplaceEnvironmentSubsystem_StaticRegisterNativesUNLTWorkplaceEnvironmentSubsystem,
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
		return Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTWorkplaceEnvironmentSubsystem::UNLTWorkplaceEnvironmentSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTWorkplaceEnvironmentSubsystem);
UNLTWorkplaceEnvironmentSubsystem::~UNLTWorkplaceEnvironmentSubsystem() {}
// ********** End Class UNLTWorkplaceEnvironmentSubsystem ******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem, TEXT("UNLTWorkplaceEnvironmentSubsystem"), &Z_Registration_Info_UClass_UNLTWorkplaceEnvironmentSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTWorkplaceEnvironmentSubsystem), 1788452716U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h__Script_WorldEngine_fa866192182f13dc07ec970e2e6aaa920e3acdc5{
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
