// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/NLTSimulationClockSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTSimulationClockSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationClockSubsystem(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnAuthoritativeTick__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnClockRateChanged__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationClockSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FOnAuthoritativeTick **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_WorldEngine_OnAuthoritativeTick__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_WorldEngine_eventOnAuthoritativeTick_Parms
	{
		int32 Tick;
		double WorldTimeSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnAuthoritativeTick constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Tick;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_WorldTimeSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnAuthoritativeTick constinit property declarations ********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnAuthoritativeTick Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Tick = { "Tick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnAuthoritativeTick_Parms, Tick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDoublePropertyParams UHT_STATICS::NewProp_WorldTimeSeconds = { "WorldTimeSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Double, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnAuthoritativeTick_Parms, WorldTimeSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldTimeSeconds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FOnAuthoritativeTick Property Definitions *******************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine, nullptr, "OnAuthoritativeTick__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_WorldEngine_eventOnAuthoritativeTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_WorldEngine_eventOnAuthoritativeTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnAuthoritativeTick__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnAuthoritativeTick ****************************************************

// ********** Begin Delegate FOnClockRateChanged ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_WorldEngine_OnClockRateChanged__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_WorldEngine_eventOnClockRateChanged_Parms
	{
		float NewRate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnClockRateChanged constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnClockRateChanged constinit property declarations *********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnClockRateChanged Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NewRate = { "NewRate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnClockRateChanged_Parms, NewRate), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewRate,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FOnClockRateChanged Property Definitions ********************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine, nullptr, "OnClockRateChanged__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_WorldEngine_eventOnClockRateChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_WorldEngine_eventOnClockRateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnClockRateChanged__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnClockRateChanged *****************************************************

// ********** Begin Class UNLTSimulationClockSubsystem Function AdvanceTick ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_AdvanceTick_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Advance the clock by one fixed tick. Call from sim loop, not Tick(). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Advance the clock by one fixed tick. Call from sim loop, not Tick()." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AdvanceTick constinit property declarations ***************************
// ********** End Function AdvanceTick constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "AdvanceTick", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_AdvanceTick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execAdvanceTick)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdvanceTick();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function AdvanceTick **************************

// ********** Begin Class UNLTSimulationClockSubsystem Function AdvanceTicks ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_AdvanceTicks_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventAdvanceTicks_Parms
	{
		int32 Count;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Advance the clock by N fixed ticks (batch stepping for headless/deterministic modes). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Advance the clock by N fixed ticks (batch stepping for headless/deterministic modes)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function AdvanceTicks constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AdvanceTicks constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AdvanceTicks Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventAdvanceTicks_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Count,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function AdvanceTicks Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "AdvanceTicks", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventAdvanceTicks_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventAdvanceTicks_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_AdvanceTicks(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execAdvanceTicks)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdvanceTicks(Z_Param_Count);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function AdvanceTicks *************************

// ********** Begin Class UNLTSimulationClockSubsystem Function DeserializeClockState **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_DeserializeClockState_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventDeserializeClockState_Parms
	{
		TArray<uint8> InData;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deserialize and restore clock state. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deserialize and restore clock state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DeserializeClockState constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_InData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InData;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSimulationClockSubsystem_eventDeserializeClockState_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeserializeClockState constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeserializeClockState Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_InData_Inner = { "InData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_InData = { "InData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventDeserializeClockState_Parms, InData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InData_MetaData), NewProp_InData_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSimulationClockSubsystem_eventDeserializeClockState_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeserializeClockState Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "DeserializeClockState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventDeserializeClockState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventDeserializeClockState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_DeserializeClockState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execDeserializeClockState)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_InData);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DeserializeClockState(Z_Param_Out_InData);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function DeserializeClockState ****************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetCurrentTick *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetCurrentTick_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetCurrentTick_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current authoritative tick index (monotonically increasing). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current authoritative tick index (monotonically increasing)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentTick constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentTick constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentTick Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetCurrentTick_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCurrentTick Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetCurrentTick", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetCurrentTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetCurrentTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetCurrentTick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetCurrentTick)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCurrentTick();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetCurrentTick ***********************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetDaysElapsed *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetDaysElapsed_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetDaysElapsed_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of simulated days elapsed since clock start. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of simulated days elapsed since clock start." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDaysElapsed constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDaysElapsed constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDaysElapsed Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetDaysElapsed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDaysElapsed Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetDaysElapsed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetDaysElapsed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetDaysElapsed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetDaysElapsed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetDaysElapsed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetDaysElapsed();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetDaysElapsed ***********************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetFixedTimestepSeconds ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetFixedTimestepSeconds_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetFixedTimestepSeconds_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Duration of one fixed tick in seconds. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Duration of one fixed tick in seconds." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetFixedTimestepSeconds constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetFixedTimestepSeconds constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetFixedTimestepSeconds Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetFixedTimestepSeconds_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetFixedTimestepSeconds Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetFixedTimestepSeconds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetFixedTimestepSeconds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetFixedTimestepSeconds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetFixedTimestepSeconds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetFixedTimestepSeconds)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetFixedTimestepSeconds();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetFixedTimestepSeconds **************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetInitialTimeOfDay ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetInitialTimeOfDay_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetInitialTimeOfDay_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the initial time-of-day used for day-rollover math. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the initial time-of-day used for day-rollover math." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetInitialTimeOfDay constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetInitialTimeOfDay constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetInitialTimeOfDay Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetInitialTimeOfDay_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetInitialTimeOfDay Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetInitialTimeOfDay", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetInitialTimeOfDay_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetInitialTimeOfDay_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetInitialTimeOfDay(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetInitialTimeOfDay)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetInitialTimeOfDay();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetInitialTimeOfDay ******************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetTimeOfDayHours ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetTimeOfDayHours_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetTimeOfDayHours_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Simulated time-of-day in hours [0, 24). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simulated time-of-day in hours [0, 24)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetTimeOfDayHours constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTimeOfDayHours constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTimeOfDayHours Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetTimeOfDayHours_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetTimeOfDayHours Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetTimeOfDayHours", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetTimeOfDayHours_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetTimeOfDayHours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetTimeOfDayHours(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetTimeOfDayHours)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTimeOfDayHours();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetTimeOfDayHours ********************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetTimeScale ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetTimeScale_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetTimeScale_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time scale multiplier (1.0 = realtime, 0.0 = paused, >1.0 = fast-forward). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time scale multiplier (1.0 = realtime, 0.0 = paused, >1.0 = fast-forward)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetTimeScale constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTimeScale constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTimeScale Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetTimeScale_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetTimeScale Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetTimeScale", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetTimeScale_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetTimeScale_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetTimeScale(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetTimeScale)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTimeScale();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetTimeScale *************************

// ********** Begin Class UNLTSimulationClockSubsystem Function GetWorldTimeSeconds ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetWorldTimeSeconds_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventGetWorldTimeSeconds_Parms
	{
		double ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Total simulated time in seconds since clock start. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Total simulated time in seconds since clock start." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetWorldTimeSeconds constinit property declarations *******************
	static const UECodeGen_Private::FDoublePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetWorldTimeSeconds constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetWorldTimeSeconds Property Definitions ******************************
const UECodeGen_Private::FDoublePropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Double, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventGetWorldTimeSeconds_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetWorldTimeSeconds Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "GetWorldTimeSeconds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventGetWorldTimeSeconds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventGetWorldTimeSeconds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetWorldTimeSeconds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execGetWorldTimeSeconds)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(double*)Z_Param__Result=P_THIS->GetWorldTimeSeconds();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function GetWorldTimeSeconds ******************

// ********** Begin Class UNLTSimulationClockSubsystem Function IsRunning **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_IsRunning_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventIsRunning_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether the clock is currently advancing. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether the clock is currently advancing." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsRunning constinit property declarations *****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSimulationClockSubsystem_eventIsRunning_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsRunning constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsRunning Property Definitions ****************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSimulationClockSubsystem_eventIsRunning_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsRunning Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "IsRunning", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventIsRunning_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventIsRunning_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_IsRunning(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execIsRunning)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsRunning();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function IsRunning ****************************

// ********** Begin Class UNLTSimulationClockSubsystem Function ResetClock *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_ResetClock_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Reset clock to tick 0, time 0. Does not change timestep or scale. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reset clock to tick 0, time 0. Does not change timestep or scale." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetClock constinit property declarations ****************************
// ********** End Function ResetClock constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "ResetClock", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_ResetClock(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execResetClock)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetClock();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function ResetClock ***************************

// ********** Begin Class UNLTSimulationClockSubsystem Function SerializeClockState ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_SerializeClockState_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventSerializeClockState_Parms
	{
		TArray<uint8> OutData;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Serialize clock state for persistence. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Serialize clock state for persistence." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SerializeClockState constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_OutData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SerializeClockState constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SerializeClockState Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_OutData_Inner = { "OutData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutData = { "OutData", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventSerializeClockState_Parms, OutData), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SerializeClockState Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "SerializeClockState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventSerializeClockState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventSerializeClockState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_SerializeClockState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execSerializeClockState)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_OutData);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SerializeClockState(Z_Param_Out_OutData);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function SerializeClockState ******************

// ********** Begin Class UNLTSimulationClockSubsystem Function SetFixedTimestepSeconds ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetFixedTimestepSeconds_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventSetFixedTimestepSeconds_Parms
	{
		float InSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the fixed timestep (seconds per tick). Affects all downstream subsystems. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the fixed timestep (seconds per tick). Affects all downstream subsystems." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetFixedTimestepSeconds constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetFixedTimestepSeconds constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetFixedTimestepSeconds Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InSeconds = { "InSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventSetFixedTimestepSeconds_Parms, InSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InSeconds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetFixedTimestepSeconds Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "SetFixedTimestepSeconds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventSetFixedTimestepSeconds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventSetFixedTimestepSeconds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetFixedTimestepSeconds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execSetFixedTimestepSeconds)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetFixedTimestepSeconds(Z_Param_InSeconds);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function SetFixedTimestepSeconds **************

// ********** Begin Class UNLTSimulationClockSubsystem Function SetInitialTimeOfDay ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetInitialTimeOfDay_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventSetInitialTimeOfDay_Parms
	{
		float Hours;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set initial time-of-day in hours [0, 24). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set initial time-of-day in hours [0, 24)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetInitialTimeOfDay constinit property declarations *******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Hours;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetInitialTimeOfDay constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetInitialTimeOfDay Property Definitions ******************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Hours = { "Hours", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventSetInitialTimeOfDay_Parms, Hours), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Hours,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetInitialTimeOfDay Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "SetInitialTimeOfDay", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventSetInitialTimeOfDay_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventSetInitialTimeOfDay_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetInitialTimeOfDay(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execSetInitialTimeOfDay)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Hours);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetInitialTimeOfDay(Z_Param_Hours);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function SetInitialTimeOfDay ******************

// ********** Begin Class UNLTSimulationClockSubsystem Function SetTimeScale ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetTimeScale_Statics
struct UHT_STATICS
{
	struct NLTSimulationClockSubsystem_eventSetTimeScale_Parms
	{
		float NewScale;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set time scale. 0.0 pauses the clock. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set time scale. 0.0 pauses the clock." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetTimeScale constinit property declarations **************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewScale;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetTimeScale constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetTimeScale Property Definitions *************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NewScale = { "NewScale", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationClockSubsystem_eventSetTimeScale_Parms, NewScale), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewScale,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetTimeScale Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "SetTimeScale", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationClockSubsystem_eventSetTimeScale_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationClockSubsystem_eventSetTimeScale_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetTimeScale(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execSetTimeScale)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewScale);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetTimeScale(Z_Param_NewScale);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function SetTimeScale *************************

// ********** Begin Class UNLTSimulationClockSubsystem Function Start ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_Start_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Start the clock. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Start the clock." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Start constinit property declarations *********************************
// ********** End Function Start constinit property declarations ***********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "Start", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_Start(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Start();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function Start ********************************

// ********** Begin Class UNLTSimulationClockSubsystem Function Stop *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationClockSubsystem_Stop_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Clock" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stop the clock (resets running state but preserves tick count). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop the clock (resets running state but preserves tick count)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Stop constinit property declarations **********************************
// ********** End Function Stop constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationClockSubsystem, nullptr, "Stop", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationClockSubsystem_Stop(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationClockSubsystem::execStop)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Stop();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationClockSubsystem Function Stop *********************************

// ********** Begin Class UNLTSimulationClockSubsystem *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTSimulationClockSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Authoritative simulation clock for environment-only mode.\n * Provides deterministic, fixed-timestep time advancement independent of render framerate.\n * Drives all environment subsystems (lighting, weather, room state) from a single time source.\n */" },
#endif
		{ "IncludePath", "Simulation/NLTSimulationClockSubsystem.h" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationClockSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Authoritative simulation clock for environment-only mode.\nProvides deterministic, fixed-timestep time advancement independent of render framerate.\nDrives all environment subsystems (lighting, weather, room state) from a single time source." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTSimulationClockSubsystem constinit property declarations *************
// ********** End Class UNLTSimulationClockSubsystem constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AdvanceTick"), .Pointer = &UNLTSimulationClockSubsystem::execAdvanceTick },
		{ .NameUTF8 = UTF8TEXT("AdvanceTicks"), .Pointer = &UNLTSimulationClockSubsystem::execAdvanceTicks },
		{ .NameUTF8 = UTF8TEXT("DeserializeClockState"), .Pointer = &UNLTSimulationClockSubsystem::execDeserializeClockState },
		{ .NameUTF8 = UTF8TEXT("GetCurrentTick"), .Pointer = &UNLTSimulationClockSubsystem::execGetCurrentTick },
		{ .NameUTF8 = UTF8TEXT("GetDaysElapsed"), .Pointer = &UNLTSimulationClockSubsystem::execGetDaysElapsed },
		{ .NameUTF8 = UTF8TEXT("GetFixedTimestepSeconds"), .Pointer = &UNLTSimulationClockSubsystem::execGetFixedTimestepSeconds },
		{ .NameUTF8 = UTF8TEXT("GetInitialTimeOfDay"), .Pointer = &UNLTSimulationClockSubsystem::execGetInitialTimeOfDay },
		{ .NameUTF8 = UTF8TEXT("GetTimeOfDayHours"), .Pointer = &UNLTSimulationClockSubsystem::execGetTimeOfDayHours },
		{ .NameUTF8 = UTF8TEXT("GetTimeScale"), .Pointer = &UNLTSimulationClockSubsystem::execGetTimeScale },
		{ .NameUTF8 = UTF8TEXT("GetWorldTimeSeconds"), .Pointer = &UNLTSimulationClockSubsystem::execGetWorldTimeSeconds },
		{ .NameUTF8 = UTF8TEXT("IsRunning"), .Pointer = &UNLTSimulationClockSubsystem::execIsRunning },
		{ .NameUTF8 = UTF8TEXT("ResetClock"), .Pointer = &UNLTSimulationClockSubsystem::execResetClock },
		{ .NameUTF8 = UTF8TEXT("SerializeClockState"), .Pointer = &UNLTSimulationClockSubsystem::execSerializeClockState },
		{ .NameUTF8 = UTF8TEXT("SetFixedTimestepSeconds"), .Pointer = &UNLTSimulationClockSubsystem::execSetFixedTimestepSeconds },
		{ .NameUTF8 = UTF8TEXT("SetInitialTimeOfDay"), .Pointer = &UNLTSimulationClockSubsystem::execSetInitialTimeOfDay },
		{ .NameUTF8 = UTF8TEXT("SetTimeScale"), .Pointer = &UNLTSimulationClockSubsystem::execSetTimeScale },
		{ .NameUTF8 = UTF8TEXT("Start"), .Pointer = &UNLTSimulationClockSubsystem::execStart },
		{ .NameUTF8 = UTF8TEXT("Stop"), .Pointer = &UNLTSimulationClockSubsystem::execStop },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_AdvanceTick, "AdvanceTick" }, // de3d7f38127994714f8da902084c9cbcabd55878
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_AdvanceTicks, "AdvanceTicks" }, // 6f6c6c54bb5179f280295f1e613be40ad7e3c3af
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_DeserializeClockState, "DeserializeClockState" }, // 1f29e2f7c9977dfe4bec6866d43c36d3c13df594
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetCurrentTick, "GetCurrentTick" }, // a1b0fec52a0a63dc7c7134a4b9490ba2010ed088
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetDaysElapsed, "GetDaysElapsed" }, // 62699f36af215b9c6a737ee8791c22916a1efb53
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetFixedTimestepSeconds, "GetFixedTimestepSeconds" }, // d672fee8a6ecda198addf788564c27724f9b3dd0
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetInitialTimeOfDay, "GetInitialTimeOfDay" }, // f7f852744fbd4190fdccb6d41e82b7fc54d49c10
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetTimeOfDayHours, "GetTimeOfDayHours" }, // e654b9543c3ebf8c483d64bd51e7138e103575a8
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetTimeScale, "GetTimeScale" }, // 3dcb9eabdcc35dfebdb5c3dcd2ae2d4c5c80f7c6
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_GetWorldTimeSeconds, "GetWorldTimeSeconds" }, // efccd576d92e32906685ab9bda88adb9d7b7a128
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_IsRunning, "IsRunning" }, // ac7db14259966c34c04392cdea05154a5bea729d
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_ResetClock, "ResetClock" }, // 886e4aae3bf6eacb38466180eccd4eb891ec41a0
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_SerializeClockState, "SerializeClockState" }, // 311fd91639fe19bc8bb933b8feebf0d697215033
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetFixedTimestepSeconds, "SetFixedTimestepSeconds" }, // c28d6d3d291215a0f5e2ebb4301c582c6eeaa005
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetInitialTimeOfDay, "SetInitialTimeOfDay" }, // a22ed29da3897f6d8fe898978adaa7d654816b4c
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_SetTimeScale, "SetTimeScale" }, // 3d411a31714f461c7b2bcfdd8ebfbedee8441263
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_Start, "Start" }, // 8754b2ed89443f5b548e838931b9b248714606e5
		{ &Z_Construct_UFunction_UNLTSimulationClockSubsystem_Stop, "Stop" }, // 0f1bcf4eb846670c3db77d0d5284a717c5954336
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTSimulationClockSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTSimulationClockSubsystem,
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
static void UNLTSimulationClockSubsystem_StaticRegisterNativesUNLTSimulationClockSubsystem()
{
	UClass* Class = UNLTSimulationClockSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTSimulationClockSubsystem;
UClass* Z_Construct_UClass_UNLTSimulationClockSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTSimulationClockSubsystem;
		if (!Z_Registration_Info_UClass_UNLTSimulationClockSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTSimulationClockSubsystem"),
				Z_Registration_Info_UClass_UNLTSimulationClockSubsystem.InnerSingleton,
				UNLTSimulationClockSubsystem_StaticRegisterNativesUNLTSimulationClockSubsystem,
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
		return Z_Registration_Info_UClass_UNLTSimulationClockSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTSimulationClockSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTSimulationClockSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTSimulationClockSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTSimulationClockSubsystem::UNLTSimulationClockSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTSimulationClockSubsystem);
UNLTSimulationClockSubsystem::~UNLTSimulationClockSubsystem() {}
// ********** End Class UNLTSimulationClockSubsystem ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTSimulationClockSubsystem, TEXT("UNLTSimulationClockSubsystem"), &Z_Registration_Info_UClass_UNLTSimulationClockSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTSimulationClockSubsystem), 1959172835U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h__Script_WorldEngine_6733ce3b6cbcab6966dba853a3f86c4310dc9947{
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
