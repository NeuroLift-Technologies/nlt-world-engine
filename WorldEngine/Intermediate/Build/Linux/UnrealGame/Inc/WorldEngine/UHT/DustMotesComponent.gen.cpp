// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/DustMotesComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDustMotesComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UDustMotesComponent(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UDustMotesComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UDustMotesComponent Function GetDensity **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_GetDensity_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventGetDensity_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetDensity constinit property declarations ****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDensity constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDensity Property Definitions ***************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DustMotesComponent_eventGetDensity_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDensity Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "GetDensity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventGetDensity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventGetDensity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_GetDensity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execGetDensity)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetDensity();
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function GetDensity ************************************

// ********** Begin Class UDustMotesComponent Function GetVisibility *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_GetVisibility_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventGetVisibility_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetVisibility constinit property declarations *************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((DustMotesComponent_eventGetVisibility_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetVisibility constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetVisibility Property Definitions ************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DustMotesComponent_eventGetVisibility_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetVisibility Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "GetVisibility", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventGetVisibility_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventGetVisibility_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_GetVisibility(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execGetVisibility)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetVisibility();
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function GetVisibility *********************************

// ********** Begin Class UDustMotesComponent Function SetColorTint ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_SetColorTint_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventSetColorTint_Parms
	{
		FLinearColor Color;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the color tint of dust particles. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the color tint of dust particles." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetColorTint constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetColorTint constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetColorTint Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(DustMotesComponent_eventSetColorTint_Parms, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetColorTint Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "SetColorTint", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventSetColorTint_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventSetColorTint_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_SetColorTint(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execSetColorTint)
{
	P_GET_STRUCT_REF(FLinearColor,Z_Param_Out_Color);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetColorTint(Z_Param_Out_Color);
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function SetColorTint **********************************

// ********** Begin Class UDustMotesComponent Function SetDensity **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_SetDensity_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventSetDensity_Parms
	{
		float Density;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetDensity constinit property declarations ****************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Density;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetDensity constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetDensity Property Definitions ***************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Density = { "Density", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DustMotesComponent_eventSetDensity_Parms, Density), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Density,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetDensity Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "SetDensity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventSetDensity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventSetDensity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_SetDensity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execSetDensity)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Density);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDensity(Z_Param_Density);
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function SetDensity ************************************

// ********** Begin Class UDustMotesComponent Function SetDriftSpeed *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_SetDriftSpeed_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventSetDriftSpeed_Parms
	{
		float Speed;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the drift speed of dust particles. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the drift speed of dust particles." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetDriftSpeed constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Speed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetDriftSpeed constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetDriftSpeed Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DustMotesComponent_eventSetDriftSpeed_Parms, Speed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Speed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetDriftSpeed Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "SetDriftSpeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventSetDriftSpeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventSetDriftSpeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_SetDriftSpeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execSetDriftSpeed)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Speed);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetDriftSpeed(Z_Param_Speed);
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function SetDriftSpeed *********************************

// ********** Begin Class UDustMotesComponent Function SetParticleSystem ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_SetParticleSystem_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventSetParticleSystem_Parms
	{
		UParticleSystem* Template;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetParticleSystem constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Template;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetParticleSystem constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetParticleSystem Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Template = { "Template", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(DustMotesComponent_eventSetParticleSystem_Parms, Template), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Template,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetParticleSystem Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "SetParticleSystem", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventSetParticleSystem_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventSetParticleSystem_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_SetParticleSystem(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execSetParticleSystem)
{
	P_GET_OBJECT(UParticleSystem,Z_Param_Template);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetParticleSystem(Z_Param_Template);
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function SetParticleSystem *****************************

// ********** Begin Class UDustMotesComponent Function SetVisibility *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UDustMotesComponent_SetVisibility_Statics
struct UHT_STATICS
{
	struct DustMotesComponent_eventSetVisibility_Parms
	{
		bool bVisible;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetVisibility constinit property declarations *************************
	static void NewProp_bVisible_SetBit(void* Obj)
	{
		((DustMotesComponent_eventSetVisibility_Parms*)Obj)->bVisible = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVisible;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetVisibility constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetVisibility Property Definitions ************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bVisible = { "bVisible", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(DustMotesComponent_eventSetVisibility_Parms), &UHT_STATICS::NewProp_bVisible_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bVisible,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetVisibility Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UDustMotesComponent, nullptr, "SetVisibility", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DustMotesComponent_eventSetVisibility_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DustMotesComponent_eventSetVisibility_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UDustMotesComponent_SetVisibility(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UDustMotesComponent::execSetVisibility)
{
	P_GET_UBOOL(Z_Param_bVisible);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetVisibility(Z_Param_bVisible);
	P_NATIVE_END;
}
// ********** End Class UDustMotesComponent Function SetVisibility *********************************

// ********** Begin Class UDustMotesComponent ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UDustMotesComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Atmospheric dust motes \xe2\x80\x94 floating particles that drift through the scene.\n * Density and visibility respond to time-of-day and environment state.\n * Uses a soft round particle material for a natural look.\n */" },
#endif
		{ "IncludePath", "Simulation/DustMotesComponent.h" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Atmospheric dust motes \xe2\x80\x94 floating particles that drift through the scene.\nDensity and visibility respond to time-of-day and environment state.\nUses a soft round particle material for a natural look." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustDensity_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DriftSpeed_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ClampMax", "10.0" },
		{ "ClampMin", "0.0" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustColor_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VolumeSize_MetaData[] = {
		{ "Category", "Dust Motes" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsVisible_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustParticles_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustTemplate_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/DustMotesComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UDustMotesComponent constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DustDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DriftSpeed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DustColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VolumeSize;
	static void NewProp_bIsVisible_SetBit(void* Obj)
	{
		((UDustMotesComponent*)Obj)->bIsVisible = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsVisible;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DustParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DustTemplate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UDustMotesComponent constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetDensity"), .Pointer = &UDustMotesComponent::execGetDensity },
		{ .NameUTF8 = UTF8TEXT("GetVisibility"), .Pointer = &UDustMotesComponent::execGetVisibility },
		{ .NameUTF8 = UTF8TEXT("SetColorTint"), .Pointer = &UDustMotesComponent::execSetColorTint },
		{ .NameUTF8 = UTF8TEXT("SetDensity"), .Pointer = &UDustMotesComponent::execSetDensity },
		{ .NameUTF8 = UTF8TEXT("SetDriftSpeed"), .Pointer = &UDustMotesComponent::execSetDriftSpeed },
		{ .NameUTF8 = UTF8TEXT("SetParticleSystem"), .Pointer = &UDustMotesComponent::execSetParticleSystem },
		{ .NameUTF8 = UTF8TEXT("SetVisibility"), .Pointer = &UDustMotesComponent::execSetVisibility },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UDustMotesComponent_GetDensity, "GetDensity" }, // a56c857bf5411c2960293dc7000c7c904b985201
		{ &Z_Construct_UFunction_UDustMotesComponent_GetVisibility, "GetVisibility" }, // a4bf4f0cea5752fb80d9af661d14429d30d97cd4
		{ &Z_Construct_UFunction_UDustMotesComponent_SetColorTint, "SetColorTint" }, // 29d9d75a31039e8343f7304f7515992e35ad7347
		{ &Z_Construct_UFunction_UDustMotesComponent_SetDensity, "SetDensity" }, // 151fc22b2562b55b54e9d30cc56442c9cfc0eddc
		{ &Z_Construct_UFunction_UDustMotesComponent_SetDriftSpeed, "SetDriftSpeed" }, // aa0a9d344d08720a971222e9f854fe5b91019ac0
		{ &Z_Construct_UFunction_UDustMotesComponent_SetParticleSystem, "SetParticleSystem" }, // d7b4c510b0ba3ee5cf254c57597233e9f49a1582
		{ &Z_Construct_UFunction_UDustMotesComponent_SetVisibility, "SetVisibility" }, // d2edd3ba24da69d912dbfd5133017c2de37ae137
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UDustMotesComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UDustMotesComponent Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DustDensity = { "DustDensity", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDustMotesComponent, DustDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustDensity_MetaData), NewProp_DustDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DriftSpeed = { "DriftSpeed", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UDustMotesComponent, DriftSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DriftSpeed_MetaData), NewProp_DriftSpeed_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DustColor = { "DustColor", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDustMotesComponent, DustColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustColor_MetaData), NewProp_DustColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_VolumeSize = { "VolumeSize", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UDustMotesComponent, VolumeSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VolumeSize_MetaData), NewProp_VolumeSize_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIsVisible = { "bIsVisible", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UDustMotesComponent), &UHT_STATICS::NewProp_bIsVisible_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsVisible_MetaData), NewProp_bIsVisible_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DustParticles = { "DustParticles", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(UDustMotesComponent, DustParticles), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustParticles_MetaData), NewProp_DustParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DustTemplate = { "DustTemplate", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(UDustMotesComponent, DustTemplate), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustTemplate_MetaData), NewProp_DustTemplate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DriftSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VolumeSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIsVisible,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustTemplate,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UDustMotesComponent Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UDustMotesComponent,
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
static void UDustMotesComponent_StaticRegisterNativesUDustMotesComponent()
{
	UClass* Class = UDustMotesComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UDustMotesComponent;
UClass* Z_Construct_UClass_UDustMotesComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UDustMotesComponent;
		if (!Z_Registration_Info_UClass_UDustMotesComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DustMotesComponent"),
				Z_Registration_Info_UClass_UDustMotesComponent.InnerSingleton,
				UDustMotesComponent_StaticRegisterNativesUDustMotesComponent,
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
		return Z_Registration_Info_UClass_UDustMotesComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UDustMotesComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UDustMotesComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UDustMotesComponent.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UDustMotesComponent);
UDustMotesComponent::~UDustMotesComponent() {}
// ********** End Class UDustMotesComponent ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UDustMotesComponent, TEXT("UDustMotesComponent"), &Z_Registration_Info_UClass_UDustMotesComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UDustMotesComponent), 2714928701U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h__Script_WorldEngine_6c5897e08b3ea2b87f1c3411c1e3e3594a4e76f3{
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
