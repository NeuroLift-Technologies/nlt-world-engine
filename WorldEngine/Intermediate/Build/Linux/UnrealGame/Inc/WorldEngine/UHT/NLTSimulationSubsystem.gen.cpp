// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/NLTSimulationSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTSimulationSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ESimulationMode(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationSubsystem(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationModeChanged__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationTick__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FOnSimulationTick *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_WorldEngine_OnSimulationTick__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_WorldEngine_eventOnSimulationTick_Parms
	{
		int32 SimulationTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnSimulationTick constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SimulationTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnSimulationTick constinit property declarations ***********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnSimulationTick Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SimulationTick = { "SimulationTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnSimulationTick_Parms, SimulationTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SimulationTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FOnSimulationTick Property Definitions **********************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine, nullptr, "OnSimulationTick__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_WorldEngine_eventOnSimulationTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_WorldEngine_eventOnSimulationTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationTick__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnSimulationTick *******************************************************

// ********** Begin Delegate FOnSimulationModeChanged **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_WorldEngine_OnSimulationModeChanged__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_WorldEngine_eventOnSimulationModeChanged_Parms
	{
		ESimulationMode NewMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnSimulationModeChanged constinit property declarations **************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnSimulationModeChanged constinit property declarations ****************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnSimulationModeChanged Property Definitions *************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_NewMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_NewMode = { "NewMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnSimulationModeChanged_Parms, NewMode), Z_Construct_UEnum_WorldEngine_ESimulationMode, METADATA_PARAMS(0, nullptr) }; // a8218c1e22a62a7382a9437a3e8095c11a0f2e41
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewMode,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FOnSimulationModeChanged Property Definitions ***************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine, nullptr, "OnSimulationModeChanged__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_WorldEngine_eventOnSimulationModeChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_WorldEngine_eventOnSimulationModeChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationModeChanged__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnSimulationModeChanged ************************************************

// ********** Begin Class UNLTSimulationSubsystem Function GetCurrentTick **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_GetCurrentTick_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventGetCurrentTick_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCurrentTick constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCurrentTick constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCurrentTick Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventGetCurrentTick_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCurrentTick Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "GetCurrentTick", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventGetCurrentTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventGetCurrentTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_GetCurrentTick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execGetCurrentTick)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCurrentTick();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function GetCurrentTick ****************************

// ********** Begin Class UNLTSimulationSubsystem Function GetMode *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_GetMode_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventGetMode_Parms
	{
		ESimulationMode ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetMode constinit property declarations *******************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMode constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMode Property Definitions ******************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventGetMode_Parms, ReturnValue), Z_Construct_UEnum_WorldEngine_ESimulationMode, METADATA_PARAMS(0, nullptr) }; // a8218c1e22a62a7382a9437a3e8095c11a0f2e41
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMode Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "GetMode", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventGetMode_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventGetMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_GetMode(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execGetMode)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ESimulationMode*)Z_Param__Result=P_THIS->GetMode();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function GetMode ***********************************

// ********** Begin Class UNLTSimulationSubsystem Function GetSimulationRate ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_GetSimulationRate_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventGetSimulationRate_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetSimulationRate constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSimulationRate constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSimulationRate Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventGetSimulationRate_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSimulationRate Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "GetSimulationRate", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventGetSimulationRate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventGetSimulationRate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_GetSimulationRate(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execGetSimulationRate)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetSimulationRate();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function GetSimulationRate *************************

// ********** Begin Class UNLTSimulationSubsystem Function GetSimulationTimeMinutes ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_GetSimulationTimeMinutes_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventGetSimulationTimeMinutes_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetSimulationTimeMinutes constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSimulationTimeMinutes constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSimulationTimeMinutes Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventGetSimulationTimeMinutes_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSimulationTimeMinutes Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "GetSimulationTimeMinutes", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventGetSimulationTimeMinutes_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventGetSimulationTimeMinutes_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_GetSimulationTimeMinutes(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execGetSimulationTimeMinutes)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetSimulationTimeMinutes();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function GetSimulationTimeMinutes ******************

// ********** Begin Class UNLTSimulationSubsystem Function IsRunning *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_IsRunning_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventIsRunning_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsRunning constinit property declarations *****************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSimulationSubsystem_eventIsRunning_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsRunning constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsRunning Property Definitions ****************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSimulationSubsystem_eventIsRunning_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsRunning Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "IsRunning", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventIsRunning_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventIsRunning_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_IsRunning(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execIsRunning)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsRunning();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function IsRunning *********************************

// ********** Begin Class UNLTSimulationSubsystem Function PauseSimulation *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_PauseSimulation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function PauseSimulation constinit property declarations ***********************
// ********** End Function PauseSimulation constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "PauseSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_PauseSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execPauseSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->PauseSimulation();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function PauseSimulation ***************************

// ********** Begin Class UNLTSimulationSubsystem Function ResumeSimulation ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_ResumeSimulation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResumeSimulation constinit property declarations **********************
// ********** End Function ResumeSimulation constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "ResumeSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_ResumeSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execResumeSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResumeSimulation();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function ResumeSimulation **************************

// ********** Begin Class UNLTSimulationSubsystem Function SetMode *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_SetMode_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventSetMode_Parms
	{
		ESimulationMode NewMode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetMode constinit property declarations *******************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_NewMode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_NewMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetMode constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetMode Property Definitions ******************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_NewMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_NewMode = { "NewMode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventSetMode_Parms, NewMode), Z_Construct_UEnum_WorldEngine_ESimulationMode, METADATA_PARAMS(0, nullptr) }; // a8218c1e22a62a7382a9437a3e8095c11a0f2e41
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewMode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewMode,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetMode Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "SetMode", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventSetMode_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventSetMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_SetMode(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execSetMode)
{
	P_GET_ENUM(ESimulationMode,Z_Param_NewMode);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMode(ESimulationMode(Z_Param_NewMode));
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function SetMode ***********************************

// ********** Begin Class UNLTSimulationSubsystem Function SetSimulationRate ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_SetSimulationRate_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventSetSimulationRate_Parms
	{
		float NewRate;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetSimulationRate constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NewRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetSimulationRate constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetSimulationRate Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NewRate = { "NewRate", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventSetSimulationRate_Parms, NewRate), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewRate,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetSimulationRate Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "SetSimulationRate", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventSetSimulationRate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventSetSimulationRate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_SetSimulationRate(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execSetSimulationRate)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_NewRate);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSimulationRate(Z_Param_NewRate);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function SetSimulationRate *************************

// ********** Begin Class UNLTSimulationSubsystem Function StartSimulation *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_StartSimulation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartSimulation constinit property declarations ***********************
// ********** End Function StartSimulation constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "StartSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_StartSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execStartSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartSimulation();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function StartSimulation ***************************

// ********** Begin Class UNLTSimulationSubsystem Function StepTick ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_StepTick_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StepTick constinit property declarations ******************************
// ********** End Function StepTick constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "StepTick", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_StepTick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execStepTick)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StepTick();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function StepTick **********************************

// ********** Begin Class UNLTSimulationSubsystem Function StepTicks *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_StepTicks_Statics
struct UHT_STATICS
{
	struct NLTSimulationSubsystem_eventStepTicks_Parms
	{
		int32 Count;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StepTicks constinit property declarations *****************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function StepTicks constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function StepTicks Property Definitions ****************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSimulationSubsystem_eventStepTicks_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Count,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function StepTicks Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "StepTicks", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSimulationSubsystem_eventStepTicks_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSimulationSubsystem_eventStepTicks_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_StepTicks(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execStepTicks)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StepTicks(Z_Param_Count);
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function StepTicks *********************************

// ********** Begin Class UNLTSimulationSubsystem Function StopSimulation **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSimulationSubsystem_StopSimulation_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StopSimulation constinit property declarations ************************
// ********** End Function StopSimulation constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSimulationSubsystem, nullptr, "StopSimulation", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSimulationSubsystem_StopSimulation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSimulationSubsystem::execStopSimulation)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StopSimulation();
	P_NATIVE_END;
}
// ********** End Class UNLTSimulationSubsystem Function StopSimulation ****************************

// ********** Begin Class UNLTSimulationSubsystem **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTSimulationSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Simulation/NLTSimulationSubsystem.h" },
		{ "ModuleRelativePath", "Public/Simulation/NLTSimulationSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTSimulationSubsystem constinit property declarations ******************
// ********** End Class UNLTSimulationSubsystem constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetCurrentTick"), .Pointer = &UNLTSimulationSubsystem::execGetCurrentTick },
		{ .NameUTF8 = UTF8TEXT("GetMode"), .Pointer = &UNLTSimulationSubsystem::execGetMode },
		{ .NameUTF8 = UTF8TEXT("GetSimulationRate"), .Pointer = &UNLTSimulationSubsystem::execGetSimulationRate },
		{ .NameUTF8 = UTF8TEXT("GetSimulationTimeMinutes"), .Pointer = &UNLTSimulationSubsystem::execGetSimulationTimeMinutes },
		{ .NameUTF8 = UTF8TEXT("IsRunning"), .Pointer = &UNLTSimulationSubsystem::execIsRunning },
		{ .NameUTF8 = UTF8TEXT("PauseSimulation"), .Pointer = &UNLTSimulationSubsystem::execPauseSimulation },
		{ .NameUTF8 = UTF8TEXT("ResumeSimulation"), .Pointer = &UNLTSimulationSubsystem::execResumeSimulation },
		{ .NameUTF8 = UTF8TEXT("SetMode"), .Pointer = &UNLTSimulationSubsystem::execSetMode },
		{ .NameUTF8 = UTF8TEXT("SetSimulationRate"), .Pointer = &UNLTSimulationSubsystem::execSetSimulationRate },
		{ .NameUTF8 = UTF8TEXT("StartSimulation"), .Pointer = &UNLTSimulationSubsystem::execStartSimulation },
		{ .NameUTF8 = UTF8TEXT("StepTick"), .Pointer = &UNLTSimulationSubsystem::execStepTick },
		{ .NameUTF8 = UTF8TEXT("StepTicks"), .Pointer = &UNLTSimulationSubsystem::execStepTicks },
		{ .NameUTF8 = UTF8TEXT("StopSimulation"), .Pointer = &UNLTSimulationSubsystem::execStopSimulation },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_GetCurrentTick, "GetCurrentTick" }, // f0c5fa8c3e74093c99353c53ec72177ffa3b0c98
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_GetMode, "GetMode" }, // 0680193ea01e4b7899b6140d6c65092b074f03c0
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_GetSimulationRate, "GetSimulationRate" }, // 7bd5a19e044521bdb6056570849b59779015afdf
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_GetSimulationTimeMinutes, "GetSimulationTimeMinutes" }, // e0df75beca40467a16e77967266a3cdd4f501813
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_IsRunning, "IsRunning" }, // c58b54659c51cfefb8ea79b76689ecbb0e4d139b
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_PauseSimulation, "PauseSimulation" }, // 3fc231ffc0976457899a4c4484710ff6c1b45f10
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_ResumeSimulation, "ResumeSimulation" }, // 31874859ca7e7ddf073bc91fe04beba0d49b917f
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_SetMode, "SetMode" }, // 41865271ff95ca60b76e9ca5ef901bce53acc7e2
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_SetSimulationRate, "SetSimulationRate" }, // edc08eeaad1474255523ca0f8bb2400b9ce66916
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_StartSimulation, "StartSimulation" }, // 42c4ebaf275b67baeeb238b2c7555b8efd44c35d
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_StepTick, "StepTick" }, // f7f921ed19dfd60ae106e3c4c1d460fc4cae38a2
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_StepTicks, "StepTicks" }, // f0c9fdc3671a602901f17c5b77d62630ac2e4d25
		{ &Z_Construct_UFunction_UNLTSimulationSubsystem_StopSimulation, "StopSimulation" }, // 0d83122f935f7c1539211f38fe00b2b1e7303f58
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTSimulationSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTSimulationSubsystem,
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
static void UNLTSimulationSubsystem_StaticRegisterNativesUNLTSimulationSubsystem()
{
	UClass* Class = UNLTSimulationSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTSimulationSubsystem;
UClass* Z_Construct_UClass_UNLTSimulationSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTSimulationSubsystem;
		if (!Z_Registration_Info_UClass_UNLTSimulationSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTSimulationSubsystem"),
				Z_Registration_Info_UClass_UNLTSimulationSubsystem.InnerSingleton,
				UNLTSimulationSubsystem_StaticRegisterNativesUNLTSimulationSubsystem,
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
		return Z_Registration_Info_UClass_UNLTSimulationSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTSimulationSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTSimulationSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTSimulationSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTSimulationSubsystem::UNLTSimulationSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTSimulationSubsystem);
UNLTSimulationSubsystem::~UNLTSimulationSubsystem() {}
// ********** End Class UNLTSimulationSubsystem ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTSimulationSubsystem, TEXT("UNLTSimulationSubsystem"), &Z_Registration_Info_UClass_UNLTSimulationSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTSimulationSubsystem), 153984574U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h__Script_WorldEngine_c7ead4ce11af0f1a32ae78caa35d17030646b1e7{
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
