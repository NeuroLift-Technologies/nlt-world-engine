// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/NLTEpisodeManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTEpisodeManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEpisodeManager(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEpisodeManager(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FOnEpisodeComplete ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnEpisodeComplete constinit property declarations ********************
// ********** End Delegate FOnEpisodeComplete constinit property declarations **********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEpisodeManager, nullptr, "OnEpisodeComplete__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnEpisodeComplete ******************************************************

// ********** Begin Class UNLTEpisodeManager Function CheckCognitiveCompletion *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEpisodeManager_CheckCognitiveCompletion_Statics
struct UHT_STATICS
{
	struct NLTEpisodeManager_eventCheckCognitiveCompletion_Parms
	{
		float Independence;
		float Burnout;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Episode" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Check cognitive-based completion\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Check cognitive-based completion" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CheckCognitiveCompletion constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Independence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Burnout;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CheckCognitiveCompletion constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CheckCognitiveCompletion Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Independence = { "Independence", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEpisodeManager_eventCheckCognitiveCompletion_Parms, Independence), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Burnout = { "Burnout", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEpisodeManager_eventCheckCognitiveCompletion_Parms, Burnout), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Independence,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Burnout,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function CheckCognitiveCompletion Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEpisodeManager, nullptr, "CheckCognitiveCompletion", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEpisodeManager_eventCheckCognitiveCompletion_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEpisodeManager_eventCheckCognitiveCompletion_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEpisodeManager_CheckCognitiveCompletion(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEpisodeManager::execCheckCognitiveCompletion)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Independence);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Burnout);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckCognitiveCompletion(Z_Param_Independence,Z_Param_Burnout);
	P_NATIVE_END;
}
// ********** End Class UNLTEpisodeManager Function CheckCognitiveCompletion ***********************

// ********** Begin Class UNLTEpisodeManager Function EndEpisode ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEpisodeManager_EndEpisode_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function EndEpisode constinit property declarations ****************************
// ********** End Function EndEpisode constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEpisodeManager, nullptr, "EndEpisode", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTEpisodeManager_EndEpisode(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEpisodeManager::execEndEpisode)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->EndEpisode();
	P_NATIVE_END;
}
// ********** End Class UNLTEpisodeManager Function EndEpisode *************************************

// ********** Begin Class UNLTEpisodeManager Function IsEpisodeComplete ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEpisodeManager_IsEpisodeComplete_Statics
struct UHT_STATICS
{
	struct NLTEpisodeManager_eventIsEpisodeComplete_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function IsEpisodeComplete constinit property declarations *********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTEpisodeManager_eventIsEpisodeComplete_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsEpisodeComplete constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsEpisodeComplete Property Definitions ********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTEpisodeManager_eventIsEpisodeComplete_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsEpisodeComplete Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEpisodeManager, nullptr, "IsEpisodeComplete", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEpisodeManager_eventIsEpisodeComplete_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEpisodeManager_eventIsEpisodeComplete_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEpisodeManager_IsEpisodeComplete(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEpisodeManager::execIsEpisodeComplete)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsEpisodeComplete();
	P_NATIVE_END;
}
// ********** End Class UNLTEpisodeManager Function IsEpisodeComplete ******************************

// ********** Begin Class UNLTEpisodeManager Function ResetEpisode *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEpisodeManager_ResetEpisode_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ResetEpisode constinit property declarations **************************
// ********** End Function ResetEpisode constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEpisodeManager, nullptr, "ResetEpisode", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTEpisodeManager_ResetEpisode(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEpisodeManager::execResetEpisode)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetEpisode();
	P_NATIVE_END;
}
// ********** End Class UNLTEpisodeManager Function ResetEpisode ***********************************

// ********** Begin Class UNLTEpisodeManager Function StartEpisode *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEpisodeManager_StartEpisode_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function StartEpisode constinit property declarations **************************
// ********** End Function StartEpisode constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEpisodeManager, nullptr, "StartEpisode", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTEpisodeManager_StartEpisode(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEpisodeManager::execStartEpisode)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->StartEpisode();
	P_NATIVE_END;
}
// ********** End Class UNLTEpisodeManager Function StartEpisode ***********************************

// ********** Begin Class UNLTEpisodeManager *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTEpisodeManager_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Agents/NLTEpisodeManager.h" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxEpisodeSteps_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StepInterval_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentStep_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEpisodeActive_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnEpisodeComplete_MetaData[] = {
		{ "Category", "Episode" },
		{ "ModuleRelativePath", "Public/Agents/NLTEpisodeManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTEpisodeManager constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxEpisodeSteps;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StepInterval;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentStep;
	static void NewProp_bEpisodeActive_SetBit(void* Obj)
	{
		((UNLTEpisodeManager*)Obj)->bEpisodeActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEpisodeActive;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnEpisodeComplete;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNLTEpisodeManager constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CheckCognitiveCompletion"), .Pointer = &UNLTEpisodeManager::execCheckCognitiveCompletion },
		{ .NameUTF8 = UTF8TEXT("EndEpisode"), .Pointer = &UNLTEpisodeManager::execEndEpisode },
		{ .NameUTF8 = UTF8TEXT("IsEpisodeComplete"), .Pointer = &UNLTEpisodeManager::execIsEpisodeComplete },
		{ .NameUTF8 = UTF8TEXT("ResetEpisode"), .Pointer = &UNLTEpisodeManager::execResetEpisode },
		{ .NameUTF8 = UTF8TEXT("StartEpisode"), .Pointer = &UNLTEpisodeManager::execStartEpisode },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTEpisodeManager_CheckCognitiveCompletion, "CheckCognitiveCompletion" }, // 7719c54a72543e5760e0110ef1d4835f8e7b1221
		{ &Z_Construct_UFunction_UNLTEpisodeManager_EndEpisode, "EndEpisode" }, // 0537b0f954dd1ee25efed4500c7c203379a1b9fe
		{ &Z_Construct_UFunction_UNLTEpisodeManager_IsEpisodeComplete, "IsEpisodeComplete" }, // 419c6884dac4a60bd615fbcee9588f868581e12e
		{ &Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature, "OnEpisodeComplete__DelegateSignature" }, // 5fb417a9db32e911916c2d26d02cda7bd577272e
		{ &Z_Construct_UFunction_UNLTEpisodeManager_ResetEpisode, "ResetEpisode" }, // d2778d3295a69faab7bb681c64010575b7bc471f
		{ &Z_Construct_UFunction_UNLTEpisodeManager_StartEpisode, "StartEpisode" }, // 6c5f146424964e65e7dc60db3a0513b7d15cb3d2
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTEpisodeManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UNLTEpisodeManager Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxEpisodeSteps = { "MaxEpisodeSteps", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTEpisodeManager, MaxEpisodeSteps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxEpisodeSteps_MetaData), NewProp_MaxEpisodeSteps_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_StepInterval = { "StepInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTEpisodeManager, StepInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StepInterval_MetaData), NewProp_StepInterval_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentStep = { "CurrentStep", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTEpisodeManager, CurrentStep), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentStep_MetaData), NewProp_CurrentStep_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEpisodeActive = { "bEpisodeActive", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTEpisodeManager), &UHT_STATICS::NewProp_bEpisodeActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEpisodeActive_MetaData), NewProp_bEpisodeActive_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnEpisodeComplete = { "OnEpisodeComplete", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTEpisodeManager, OnEpisodeComplete), Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnEpisodeComplete_MetaData), NewProp_OnEpisodeComplete_MetaData) }; // 5fb417a9db32e911916c2d26d02cda7bd577272e
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxEpisodeSteps,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StepInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentStep,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEpisodeActive,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnEpisodeComplete,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UNLTEpisodeManager Property Definitions ************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTEpisodeManager,
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
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UNLTEpisodeManager_StaticRegisterNativesUNLTEpisodeManager()
{
	UClass* Class = UNLTEpisodeManager::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTEpisodeManager;
UClass* Z_Construct_UClass_UNLTEpisodeManager(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTEpisodeManager;
		if (!Z_Registration_Info_UClass_UNLTEpisodeManager.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTEpisodeManager"),
				Z_Registration_Info_UClass_UNLTEpisodeManager.InnerSingleton,
				UNLTEpisodeManager_StaticRegisterNativesUNLTEpisodeManager,
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
		return Z_Registration_Info_UClass_UNLTEpisodeManager.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTEpisodeManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTEpisodeManager.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTEpisodeManager.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTEpisodeManager);
UNLTEpisodeManager::~UNLTEpisodeManager() {}
// ********** End Class UNLTEpisodeManager *********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTEpisodeManager, TEXT("UNLTEpisodeManager"), &Z_Registration_Info_UClass_UNLTEpisodeManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTEpisodeManager), 3272716570U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h__Script_WorldEngine_8831cd3ad90011c9e165908467f21fd0b7f5f393{
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
