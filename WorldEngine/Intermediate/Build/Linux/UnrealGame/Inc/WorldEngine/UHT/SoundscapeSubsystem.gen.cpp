// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Audio/SoundscapeSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSoundscapeSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSoundscapeSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSoundscapeSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_USoundscapeDataAsset(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UNLTSoundscapeSubsystem Function Activate ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_Activate_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Activates the soundscape (occupied world). Fades in all beds. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Activates the soundscape (occupied world). Fades in all beds." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Activate constinit property declarations ******************************
// ********** End Function Activate constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "Activate", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_Activate(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execActivate)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Activate();
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function Activate **********************************

// ********** Begin Class UNLTSoundscapeSubsystem Function Deactivate ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_Deactivate_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deactivates the soundscape (dead world). Fades out all beds. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deactivates the soundscape (dead world). Fades out all beds." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Deactivate constinit property declarations ****************************
// ********** End Function Deactivate constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "Deactivate", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_Deactivate(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execDeactivate)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Deactivate();
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function Deactivate ********************************

// ********** Begin Class UNLTSoundscapeSubsystem Function GetStressLevel **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_GetStressLevel_Statics
struct UHT_STATICS
{
	struct NLTSoundscapeSubsystem_eventGetStressLevel_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns the current stress level. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns the current stress level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetStressLevel constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetStressLevel constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetStressLevel Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSoundscapeSubsystem_eventGetStressLevel_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetStressLevel Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "GetStressLevel", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSoundscapeSubsystem_eventGetStressLevel_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSoundscapeSubsystem_eventGetStressLevel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_GetStressLevel(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execGetStressLevel)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetStressLevel();
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function GetStressLevel ****************************

// ********** Begin Class UNLTSoundscapeSubsystem Function IsActive ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_IsActive_Statics
struct UHT_STATICS
{
	struct NLTSoundscapeSubsystem_eventIsActive_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** True if the soundscape is currently active (occupied world). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "True if the soundscape is currently active (occupied world)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function IsActive constinit property declarations ******************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSoundscapeSubsystem_eventIsActive_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function IsActive constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function IsActive Property Definitions *****************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSoundscapeSubsystem_eventIsActive_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function IsActive Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "IsActive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSoundscapeSubsystem_eventIsActive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSoundscapeSubsystem_eventIsActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_IsActive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execIsActive)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->IsActive();
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function IsActive **********************************

// ********** Begin Class UNLTSoundscapeSubsystem Function MuteAll *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_MuteAll_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Immediately mutes all beds (no fade). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Immediately mutes all beds (no fade)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function MuteAll constinit property declarations *******************************
// ********** End Function MuteAll constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "MuteAll", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_MuteAll(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execMuteAll)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->MuteAll();
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function MuteAll ***********************************

// ********** Begin Class UNLTSoundscapeSubsystem Function SetOrigin *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetOrigin_Statics
struct UHT_STATICS
{
	struct NLTSoundscapeSubsystem_eventSetOrigin_Parms
	{
		FVector InOrigin;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sets the world position of the soundscape origin. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the world position of the soundscape origin." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InOrigin_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetOrigin constinit property declarations *****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InOrigin;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetOrigin constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetOrigin Property Definitions ****************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InOrigin = { "InOrigin", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSoundscapeSubsystem_eventSetOrigin_Parms, InOrigin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InOrigin_MetaData), NewProp_InOrigin_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InOrigin,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetOrigin Property Definitions ******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "SetOrigin", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSoundscapeSubsystem_eventSetOrigin_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSoundscapeSubsystem_eventSetOrigin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetOrigin(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execSetOrigin)
{
	P_GET_STRUCT_REF(FVector,Z_Param_Out_InOrigin);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetOrigin(Z_Param_Out_InOrigin);
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function SetOrigin *********************************

// ********** Begin Class UNLTSoundscapeSubsystem Function SetSoundscapeAsset **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetSoundscapeAsset_Statics
struct UHT_STATICS
{
	struct NLTSoundscapeSubsystem_eventSetSoundscapeAsset_Parms
	{
		USoundscapeDataAsset* InAsset;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Assigns the soundscape data asset to use. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Assigns the soundscape data asset to use." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetSoundscapeAsset constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InAsset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetSoundscapeAsset constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetSoundscapeAsset Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InAsset = { "InAsset", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSoundscapeSubsystem_eventSetSoundscapeAsset_Parms, InAsset), Z_Construct_UClass_USoundscapeDataAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InAsset,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetSoundscapeAsset Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "SetSoundscapeAsset", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSoundscapeSubsystem_eventSetSoundscapeAsset_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSoundscapeSubsystem_eventSetSoundscapeAsset_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetSoundscapeAsset(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execSetSoundscapeAsset)
{
	P_GET_OBJECT(USoundscapeDataAsset,Z_Param_InAsset);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSoundscapeAsset(Z_Param_InAsset);
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function SetSoundscapeAsset ************************

// ********** Begin Class UNLTSoundscapeSubsystem Function SetStressLevel **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetStressLevel_Statics
struct UHT_STATICS
{
	struct NLTSoundscapeSubsystem_eventSetStressLevel_Parms
	{
		float InStress;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Updates the stress level (0..1) that drives volume/pitch modulation. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Updates the stress level (0..1) that drives volume/pitch modulation." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetStressLevel constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InStress;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetStressLevel constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetStressLevel Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InStress = { "InStress", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSoundscapeSubsystem_eventSetStressLevel_Parms, InStress), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InStress,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetStressLevel Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "SetStressLevel", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSoundscapeSubsystem_eventSetStressLevel_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSoundscapeSubsystem_eventSetStressLevel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetStressLevel(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execSetStressLevel)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InStress);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetStressLevel(Z_Param_InStress);
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function SetStressLevel ****************************

// ********** Begin Class UNLTSoundscapeSubsystem Function UnmuteAll *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSoundscapeSubsystem_UnmuteAll_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Immediately unmutes all beds (no fade). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Immediately unmutes all beds (no fade)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UnmuteAll constinit property declarations *****************************
// ********** End Function UnmuteAll constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSoundscapeSubsystem, nullptr, "UnmuteAll", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTSoundscapeSubsystem_UnmuteAll(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSoundscapeSubsystem::execUnmuteAll)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UnmuteAll();
	P_NATIVE_END;
}
// ********** End Class UNLTSoundscapeSubsystem Function UnmuteAll *********************************

// ********** Begin Class UNLTSoundscapeSubsystem **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTSoundscapeSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Manages ambient soundscape beds for a scenario level.\n * Ties audio volume/pitch to scenario stress level (0..1).\n * Mute = dead world (no scenario active). Unmute = occupied world.\n */" },
#endif
		{ "IncludePath", "Audio/SoundscapeSubsystem.h" },
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manages ambient soundscape beds for a scenario level.\nTies audio volume/pitch to scenario stress level (0..1).\nMute = dead world (no scenario active). Unmute = occupied world." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundscapeAsset_MetaData[] = {
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HVACComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FridgeComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClockComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MurmurComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Audio/SoundscapeSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTSoundscapeSubsystem constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SoundscapeAsset;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HVACComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FridgeComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ClockComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MurmurComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNLTSoundscapeSubsystem constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Activate"), .Pointer = &UNLTSoundscapeSubsystem::execActivate },
		{ .NameUTF8 = UTF8TEXT("Deactivate"), .Pointer = &UNLTSoundscapeSubsystem::execDeactivate },
		{ .NameUTF8 = UTF8TEXT("GetStressLevel"), .Pointer = &UNLTSoundscapeSubsystem::execGetStressLevel },
		{ .NameUTF8 = UTF8TEXT("IsActive"), .Pointer = &UNLTSoundscapeSubsystem::execIsActive },
		{ .NameUTF8 = UTF8TEXT("MuteAll"), .Pointer = &UNLTSoundscapeSubsystem::execMuteAll },
		{ .NameUTF8 = UTF8TEXT("SetOrigin"), .Pointer = &UNLTSoundscapeSubsystem::execSetOrigin },
		{ .NameUTF8 = UTF8TEXT("SetSoundscapeAsset"), .Pointer = &UNLTSoundscapeSubsystem::execSetSoundscapeAsset },
		{ .NameUTF8 = UTF8TEXT("SetStressLevel"), .Pointer = &UNLTSoundscapeSubsystem::execSetStressLevel },
		{ .NameUTF8 = UTF8TEXT("UnmuteAll"), .Pointer = &UNLTSoundscapeSubsystem::execUnmuteAll },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_Activate, "Activate" }, // 91f9e3226b6374ba38f50b2430a41534cefc3f36
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_Deactivate, "Deactivate" }, // 4b0c228ff6c6ab3162abc728d767cf5db6213117
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_GetStressLevel, "GetStressLevel" }, // 4b248e1d3f463b6596798adb3254e6adfdaaddce
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_IsActive, "IsActive" }, // c0e8b3154dee3b8666e44c58a9a1762614a121d0
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_MuteAll, "MuteAll" }, // 93eac620848929a8525b0b6964ba233aabb9b9e8
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetOrigin, "SetOrigin" }, // 7cc2c40e5c0f93598e4d18cd3e773c980ea5b1b1
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetSoundscapeAsset, "SetSoundscapeAsset" }, // 924fa63170bd5bff4bde5c2a6b6184c233da1b81
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_SetStressLevel, "SetStressLevel" }, // 55a874aa99f5ec2c4d61a233185fcb051492e1b0
		{ &Z_Construct_UFunction_UNLTSoundscapeSubsystem_UnmuteAll, "UnmuteAll" }, // 035b7248dd38d040c2cbabd3b4bd844ce9ca99e3
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTSoundscapeSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UNLTSoundscapeSubsystem Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SoundscapeAsset = { "SoundscapeAsset", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTSoundscapeSubsystem, SoundscapeAsset), Z_Construct_UClass_USoundscapeDataAsset, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundscapeAsset_MetaData), NewProp_SoundscapeAsset_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HVACComponent = { "HVACComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTSoundscapeSubsystem, HVACComponent), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HVACComponent_MetaData), NewProp_HVACComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FridgeComponent = { "FridgeComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTSoundscapeSubsystem, FridgeComponent), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FridgeComponent_MetaData), NewProp_FridgeComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ClockComponent = { "ClockComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTSoundscapeSubsystem, ClockComponent), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClockComponent_MetaData), NewProp_ClockComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MurmurComponent = { "MurmurComponent", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTSoundscapeSubsystem, MurmurComponent), Z_Construct_UClass_UAudioComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MurmurComponent_MetaData), NewProp_MurmurComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoundscapeAsset,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HVACComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FridgeComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClockComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MurmurComponent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UNLTSoundscapeSubsystem Property Definitions *******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTSoundscapeSubsystem,
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
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UNLTSoundscapeSubsystem_StaticRegisterNativesUNLTSoundscapeSubsystem()
{
	UClass* Class = UNLTSoundscapeSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTSoundscapeSubsystem;
UClass* Z_Construct_UClass_UNLTSoundscapeSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTSoundscapeSubsystem;
		if (!Z_Registration_Info_UClass_UNLTSoundscapeSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTSoundscapeSubsystem"),
				Z_Registration_Info_UClass_UNLTSoundscapeSubsystem.InnerSingleton,
				UNLTSoundscapeSubsystem_StaticRegisterNativesUNLTSoundscapeSubsystem,
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
		return Z_Registration_Info_UClass_UNLTSoundscapeSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTSoundscapeSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTSoundscapeSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTSoundscapeSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTSoundscapeSubsystem::UNLTSoundscapeSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTSoundscapeSubsystem);
UNLTSoundscapeSubsystem::~UNLTSoundscapeSubsystem() {}
// ********** End Class UNLTSoundscapeSubsystem ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTSoundscapeSubsystem, TEXT("UNLTSoundscapeSubsystem"), &Z_Registration_Info_UClass_UNLTSoundscapeSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTSoundscapeSubsystem), 95093094U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h__Script_WorldEngine_6efda08b136a0827cfecfd8034f2103e28cebba7{
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
