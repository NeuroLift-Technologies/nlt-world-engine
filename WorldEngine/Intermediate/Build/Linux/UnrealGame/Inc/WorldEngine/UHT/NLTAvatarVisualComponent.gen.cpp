// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/NLTAvatarVisualComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTAvatarVisualComponent() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USkeletalMeshComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAvatarVisualComponent(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAvatarVisualComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UNLTAvatarVisualComponent Function SetEmissiveGlow ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAvatarVisualComponent_SetEmissiveGlow_Statics
struct UHT_STATICS
{
	struct NLTAvatarVisualComponent_eventSetEmissiveGlow_Parms
	{
		float Intensity;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the emissive glow intensity on the avatar material. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the emissive glow intensity on the avatar material." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetEmissiveGlow constinit property declarations ***********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Intensity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetEmissiveGlow constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetEmissiveGlow Property Definitions **********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Intensity = { "Intensity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAvatarVisualComponent_eventSetEmissiveGlow_Parms, Intensity), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Intensity,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetEmissiveGlow Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAvatarVisualComponent, nullptr, "SetEmissiveGlow", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAvatarVisualComponent_eventSetEmissiveGlow_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAvatarVisualComponent_eventSetEmissiveGlow_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAvatarVisualComponent_SetEmissiveGlow(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAvatarVisualComponent::execSetEmissiveGlow)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Intensity);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetEmissiveGlow(Z_Param_Intensity);
	P_NATIVE_END;
}
// ********** End Class UNLTAvatarVisualComponent Function SetEmissiveGlow *************************

// ********** Begin Class UNLTAvatarVisualComponent Function SetStatusRingColor ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAvatarVisualComponent_SetStatusRingColor_Statics
struct UHT_STATICS
{
	struct NLTAvatarVisualComponent_eventSetStatusRingColor_Parms
	{
		FLinearColor Color;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the status ring color (below the avatar). */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the status ring color (below the avatar)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetStatusRingColor constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetStatusRingColor constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetStatusRingColor Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAvatarVisualComponent_eventSetStatusRingColor_Parms, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetStatusRingColor Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAvatarVisualComponent, nullptr, "SetStatusRingColor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAvatarVisualComponent_eventSetStatusRingColor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAvatarVisualComponent_eventSetStatusRingColor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAvatarVisualComponent_SetStatusRingColor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAvatarVisualComponent::execSetStatusRingColor)
{
	P_GET_STRUCT_REF(FLinearColor,Z_Param_Out_Color);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetStatusRingColor(Z_Param_Out_Color);
	P_NATIVE_END;
}
// ********** End Class UNLTAvatarVisualComponent Function SetStatusRingColor **********************

// ********** Begin Class UNLTAvatarVisualComponent Function UpdateFromCognitiveState **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAvatarVisualComponent_UpdateFromCognitiveState_Statics
struct UHT_STATICS
{
	struct NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms
	{
		float Focus;
		float Stress;
		float CognitiveLoad;
		FName EmotionalState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Update visuals from cognitive state. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Update visuals from cognitive state." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateFromCognitiveState constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Focus;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stress;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CognitiveLoad;
	static const UECodeGen_Private::FNamePropertyParams NewProp_EmotionalState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdateFromCognitiveState constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdateFromCognitiveState Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Focus = { "Focus", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms, Focus), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Stress = { "Stress", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms, Stress), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CognitiveLoad = { "CognitiveLoad", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms, CognitiveLoad), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_EmotionalState = { "EmotionalState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms, EmotionalState), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Focus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stress,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitiveLoad,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmotionalState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function UpdateFromCognitiveState Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAvatarVisualComponent, nullptr, "UpdateFromCognitiveState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAvatarVisualComponent_eventUpdateFromCognitiveState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAvatarVisualComponent_UpdateFromCognitiveState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAvatarVisualComponent::execUpdateFromCognitiveState)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Focus);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Stress);
	P_GET_PROPERTY(FFloatProperty,Z_Param_CognitiveLoad);
	P_GET_PROPERTY(FNameProperty,Z_Param_EmotionalState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateFromCognitiveState(Z_Param_Focus,Z_Param_Stress,Z_Param_CognitiveLoad,Z_Param_EmotionalState);
	P_NATIVE_END;
}
// ********** End Class UNLTAvatarVisualComponent Function UpdateFromCognitiveState ****************

// ********** Begin Class UNLTAvatarVisualComponent ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTAvatarVisualComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Visual feedback component for Avatar characters.\n * Drives skeletal mesh material parameters, status ring color,\n * and ambient particles based on cognitive state.\n */" },
#endif
		{ "IncludePath", "Agents/NLTAvatarVisualComponent.h" },
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Visual feedback component for Avatar characters.\nDrives skeletal mesh material parameters, status ring color,\nand ambient particles based on cognitive state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressParticleTemplate_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Particle system for stress effect (red sparks). */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle system for stress effect (red sparks)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusParticleTemplate_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Particle system for focus effect (blue aura). */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle system for focus effect (blue aura)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurnoutParticleTemplate_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Particle system for burnout effect (dark smoke). */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Particle system for burnout effect (dark smoke)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusGlowColor_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Emissive glow color when focused. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emissive glow color when focused." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressGlowColor_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Emissive glow color when stressed. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emissive glow color when stressed." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurnoutGlowColor_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Emissive glow color when burned out. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Emissive glow color when burned out." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxGlowIntensity_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum emissive glow intensity. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum emissive glow intensity." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowStatusRing_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to show the status ring. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to show the status ring." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowParticles_MetaData[] = {
		{ "Category", "NLT|Avatar|Visual" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether to show ambient particles. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether to show ambient particles." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusRingMesh_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StatusRingMaterial_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvatarMaterialInstance_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressParticles_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusParticles_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurnoutParticles_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkeletalMesh_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTAvatarVisualComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTAvatarVisualComponent constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressParticleTemplate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusParticleTemplate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BurnoutParticleTemplate;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FocusGlowColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_StressGlowColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BurnoutGlowColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxGlowIntensity;
	static void NewProp_bShowStatusRing_SetBit(void* Obj)
	{
		((UNLTAvatarVisualComponent*)Obj)->bShowStatusRing = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowStatusRing;
	static void NewProp_bShowParticles_SetBit(void* Obj)
	{
		((UNLTAvatarVisualComponent*)Obj)->bShowParticles = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatusRingMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StatusRingMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AvatarMaterialInstance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BurnoutParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkeletalMesh;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNLTAvatarVisualComponent constinit property declarations ******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SetEmissiveGlow"), .Pointer = &UNLTAvatarVisualComponent::execSetEmissiveGlow },
		{ .NameUTF8 = UTF8TEXT("SetStatusRingColor"), .Pointer = &UNLTAvatarVisualComponent::execSetStatusRingColor },
		{ .NameUTF8 = UTF8TEXT("UpdateFromCognitiveState"), .Pointer = &UNLTAvatarVisualComponent::execUpdateFromCognitiveState },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTAvatarVisualComponent_SetEmissiveGlow, "SetEmissiveGlow" }, // d07d51437378623fba8254e1ca2660094957ef28
		{ &Z_Construct_UFunction_UNLTAvatarVisualComponent_SetStatusRingColor, "SetStatusRingColor" }, // 8c354081de36e4efd551228f09d7e14c50329ac1
		{ &Z_Construct_UFunction_UNLTAvatarVisualComponent_UpdateFromCognitiveState, "UpdateFromCognitiveState" }, // 9b31e5eb238613f9e4da685671bb4232107b2eea
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTAvatarVisualComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UNLTAvatarVisualComponent Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressParticleTemplate = { "StressParticleTemplate", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, StressParticleTemplate), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressParticleTemplate_MetaData), NewProp_StressParticleTemplate_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusParticleTemplate = { "FocusParticleTemplate", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, FocusParticleTemplate), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusParticleTemplate_MetaData), NewProp_FocusParticleTemplate_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BurnoutParticleTemplate = { "BurnoutParticleTemplate", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, BurnoutParticleTemplate), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurnoutParticleTemplate_MetaData), NewProp_BurnoutParticleTemplate_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FocusGlowColor = { "FocusGlowColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, FocusGlowColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusGlowColor_MetaData), NewProp_FocusGlowColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_StressGlowColor = { "StressGlowColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, StressGlowColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressGlowColor_MetaData), NewProp_StressGlowColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_BurnoutGlowColor = { "BurnoutGlowColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, BurnoutGlowColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurnoutGlowColor_MetaData), NewProp_BurnoutGlowColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxGlowIntensity = { "MaxGlowIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, MaxGlowIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxGlowIntensity_MetaData), NewProp_MaxGlowIntensity_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bShowStatusRing = { "bShowStatusRing", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTAvatarVisualComponent), &UHT_STATICS::NewProp_bShowStatusRing_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowStatusRing_MetaData), NewProp_bShowStatusRing_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bShowParticles = { "bShowParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTAvatarVisualComponent), &UHT_STATICS::NewProp_bShowParticles_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowParticles_MetaData), NewProp_bShowParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StatusRingMesh = { "StatusRingMesh", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, StatusRingMesh), Z_Construct_UClass_UStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusRingMesh_MetaData), NewProp_StatusRingMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StatusRingMaterial = { "StatusRingMaterial", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, StatusRingMaterial), Z_Construct_UClass_UMaterialInstanceDynamic, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StatusRingMaterial_MetaData), NewProp_StatusRingMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AvatarMaterialInstance = { "AvatarMaterialInstance", nullptr, (EPropertyFlags)0x0144000000000000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, AvatarMaterialInstance), Z_Construct_UClass_UMaterialInstanceDynamic, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvatarMaterialInstance_MetaData), NewProp_AvatarMaterialInstance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressParticles = { "StressParticles", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, StressParticles), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressParticles_MetaData), NewProp_StressParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusParticles = { "FocusParticles", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, FocusParticles), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusParticles_MetaData), NewProp_FocusParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BurnoutParticles = { "BurnoutParticles", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, BurnoutParticles), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurnoutParticles_MetaData), NewProp_BurnoutParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SkeletalMesh = { "SkeletalMesh", nullptr, (EPropertyFlags)0x0144000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAvatarVisualComponent, SkeletalMesh), Z_Construct_UClass_USkeletalMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkeletalMesh_MetaData), NewProp_SkeletalMesh_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressParticleTemplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusParticleTemplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BurnoutParticleTemplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusGlowColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressGlowColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BurnoutGlowColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxGlowIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bShowStatusRing,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bShowParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StatusRingMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StatusRingMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarMaterialInstance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BurnoutParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkeletalMesh,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UNLTAvatarVisualComponent Property Definitions *****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTAvatarVisualComponent,
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
static void UNLTAvatarVisualComponent_StaticRegisterNativesUNLTAvatarVisualComponent()
{
	UClass* Class = UNLTAvatarVisualComponent::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTAvatarVisualComponent;
UClass* Z_Construct_UClass_UNLTAvatarVisualComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTAvatarVisualComponent;
		if (!Z_Registration_Info_UClass_UNLTAvatarVisualComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTAvatarVisualComponent"),
				Z_Registration_Info_UClass_UNLTAvatarVisualComponent.InnerSingleton,
				UNLTAvatarVisualComponent_StaticRegisterNativesUNLTAvatarVisualComponent,
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
		return Z_Registration_Info_UClass_UNLTAvatarVisualComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTAvatarVisualComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTAvatarVisualComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTAvatarVisualComponent.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTAvatarVisualComponent);
UNLTAvatarVisualComponent::~UNLTAvatarVisualComponent() {}
// ********** End Class UNLTAvatarVisualComponent **************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTAvatarVisualComponent, TEXT("UNLTAvatarVisualComponent"), &Z_Registration_Info_UClass_UNLTAvatarVisualComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTAvatarVisualComponent), 1888996706U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h__Script_WorldEngine_c1c6595cf049a07e90440191269d33bddb571554{
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
