// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WorldEngine/NLTAgentVisualizer.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTAgentVisualizer() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UHierarchicalInstancedStaticMeshComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UPostProcessComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UStaticMesh(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_EMassAgentTeam(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_EMassAgentVisualState(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTAgentVisualizer(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTAgentVisualizer(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EMassAgentVisualState *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_EMassAgentVisualState_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMassAgentVisualState>()
{
	return Z_Construct_UEnum_WorldEngine_EMassAgentVisualState(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Visual state for mass agents\n" },
#endif
		{ "Focused.DisplayName", "Focused" },
		{ "Focused.Name", "EMassAgentVisualState::Focused" },
		{ "Interacting.DisplayName", "Interacting" },
		{ "Interacting.Name", "EMassAgentVisualState::Interacting" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
		{ "Normal.DisplayName", "Normal" },
		{ "Normal.Name", "EMassAgentVisualState::Normal" },
		{ "Stressed.DisplayName", "Stressed" },
		{ "Stressed.Name", "EMassAgentVisualState::Stressed" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Visual state for mass agents" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMassAgentVisualState::Normal", (int64)EMassAgentVisualState::Normal },
		{ "EMassAgentVisualState::Focused", (int64)EMassAgentVisualState::Focused },
		{ "EMassAgentVisualState::Stressed", (int64)EMassAgentVisualState::Stressed },
		{ "EMassAgentVisualState::Interacting", (int64)EMassAgentVisualState::Interacting },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"EMassAgentVisualState",
	"EMassAgentVisualState",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EMassAgentVisualState;
UEnum* Z_Construct_UEnum_WorldEngine_EMassAgentVisualState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EMassAgentVisualState.OuterSingleton)
		{
			ZRIE_EMassAgentVisualState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_EMassAgentVisualState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("EMassAgentVisualState"));
		}
		return ZRIE_EMassAgentVisualState.OuterSingleton;
	}
	if (!ZRIE_EMassAgentVisualState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EMassAgentVisualState.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EMassAgentVisualState.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EMassAgentVisualState *******************************************************

// ********** Begin Enum EMassAgentTeam ************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_EMassAgentTeam_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMassAgentTeam>()
{
	return Z_Construct_UEnum_WorldEngine_EMassAgentTeam(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Team identification for mass agents\n" },
#endif
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
		{ "Neutral.DisplayName", "Neutral" },
		{ "Neutral.Name", "EMassAgentTeam::Neutral" },
		{ "TeamA.DisplayName", "Team A" },
		{ "TeamA.Name", "EMassAgentTeam::TeamA" },
		{ "TeamB.DisplayName", "Team B" },
		{ "TeamB.Name", "EMassAgentTeam::TeamB" },
		{ "TeamC.DisplayName", "Team C" },
		{ "TeamC.Name", "EMassAgentTeam::TeamC" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Team identification for mass agents" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMassAgentTeam::Neutral", (int64)EMassAgentTeam::Neutral },
		{ "EMassAgentTeam::TeamA", (int64)EMassAgentTeam::TeamA },
		{ "EMassAgentTeam::TeamB", (int64)EMassAgentTeam::TeamB },
		{ "EMassAgentTeam::TeamC", (int64)EMassAgentTeam::TeamC },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"EMassAgentTeam",
	"EMassAgentTeam",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EMassAgentTeam;
UEnum* Z_Construct_UEnum_WorldEngine_EMassAgentTeam(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EMassAgentTeam.OuterSingleton)
		{
			ZRIE_EMassAgentTeam.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_EMassAgentTeam, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("EMassAgentTeam"));
		}
		return ZRIE_EMassAgentTeam.OuterSingleton;
	}
	if (!ZRIE_EMassAgentTeam.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EMassAgentTeam.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EMassAgentTeam.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EMassAgentTeam **************************************************************

// ********** Begin Class ANLTAgentVisualizer ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ANLTAgentVisualizer_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "NLTAgentVisualizer.h" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentMesh_MetaData[] = {
		{ "Category", "Visualization|Mesh" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============== Mesh & Materials ==============\n" },
#endif
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "============== Mesh & Materials ==============" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentMaterial_MetaData[] = {
		{ "Category", "Visualization|Materials" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressedMaterial_MetaData[] = {
		{ "Category", "Visualization|Materials" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusedMaterial_MetaData[] = {
		{ "Category", "Visualization|Materials" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentScale_MetaData[] = {
		{ "Category", "Visualization" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressParticles_MetaData[] = {
		{ "Category", "Visualization|Particles" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============== Particle Systems ==============\n" },
#endif
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "============== Particle Systems ==============" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusAuraParticles_MetaData[] = {
		{ "Category", "Visualization|Particles" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowDebugText_MetaData[] = {
		{ "Category", "Visualization" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============== Visualization Settings ==============\n" },
#endif
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "============== Visualization Settings ==============" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseTeamColors_MetaData[] = {
		{ "Category", "Visualization" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowStressEffects_MetaData[] = {
		{ "Category", "Visualization" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShowFocusEffects_MetaData[] = {
		{ "Category", "Visualization" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressThresholdForEffects_MetaData[] = {
		{ "Category", "Visualization" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusThresholdForEffects_MetaData[] = {
		{ "Category", "Visualization" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HISMComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressParticleComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusAuraParticleComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PostProcessComponent_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "NLTAgentVisualizer.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ANLTAgentVisualizer constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AgentMesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AgentMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressedMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusedMaterial;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AgentScale;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusAuraParticles;
	static void NewProp_bShowDebugText_SetBit(void* Obj)
	{
		((ANLTAgentVisualizer*)Obj)->bShowDebugText = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowDebugText;
	static void NewProp_bUseTeamColors_SetBit(void* Obj)
	{
		((ANLTAgentVisualizer*)Obj)->bUseTeamColors = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseTeamColors;
	static void NewProp_bShowStressEffects_SetBit(void* Obj)
	{
		((ANLTAgentVisualizer*)Obj)->bShowStressEffects = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowStressEffects;
	static void NewProp_bShowFocusEffects_SetBit(void* Obj)
	{
		((ANLTAgentVisualizer*)Obj)->bShowFocusEffects = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShowFocusEffects;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StressThresholdForEffects;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FocusThresholdForEffects;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HISMComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressParticleComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusAuraParticleComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PostProcessComponent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ANLTAgentVisualizer constinit property declarations ************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANLTAgentVisualizer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ANLTAgentVisualizer Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AgentMesh = { "AgentMesh", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, AgentMesh), Z_Construct_UClass_UStaticMesh, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentMesh_MetaData), NewProp_AgentMesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AgentMaterial = { "AgentMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, AgentMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentMaterial_MetaData), NewProp_AgentMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressedMaterial = { "StressedMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, StressedMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressedMaterial_MetaData), NewProp_StressedMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusedMaterial = { "FocusedMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, FocusedMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusedMaterial_MetaData), NewProp_FocusedMaterial_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AgentScale = { "AgentScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, AgentScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentScale_MetaData), NewProp_AgentScale_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressParticles = { "StressParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, StressParticles), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressParticles_MetaData), NewProp_StressParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusAuraParticles = { "FocusAuraParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, FocusAuraParticles), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusAuraParticles_MetaData), NewProp_FocusAuraParticles_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bShowDebugText = { "bShowDebugText", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTAgentVisualizer), &UHT_STATICS::NewProp_bShowDebugText_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowDebugText_MetaData), NewProp_bShowDebugText_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bUseTeamColors = { "bUseTeamColors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTAgentVisualizer), &UHT_STATICS::NewProp_bUseTeamColors_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseTeamColors_MetaData), NewProp_bUseTeamColors_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bShowStressEffects = { "bShowStressEffects", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTAgentVisualizer), &UHT_STATICS::NewProp_bShowStressEffects_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowStressEffects_MetaData), NewProp_bShowStressEffects_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bShowFocusEffects = { "bShowFocusEffects", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTAgentVisualizer), &UHT_STATICS::NewProp_bShowFocusEffects_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShowFocusEffects_MetaData), NewProp_bShowFocusEffects_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_StressThresholdForEffects = { "StressThresholdForEffects", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, StressThresholdForEffects), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressThresholdForEffects_MetaData), NewProp_StressThresholdForEffects_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FocusThresholdForEffects = { "FocusThresholdForEffects", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, FocusThresholdForEffects), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusThresholdForEffects_MetaData), NewProp_FocusThresholdForEffects_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HISMComponent = { "HISMComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, HISMComponent), Z_Construct_UClass_UHierarchicalInstancedStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HISMComponent_MetaData), NewProp_HISMComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressParticleComponent = { "StressParticleComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, StressParticleComponent), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressParticleComponent_MetaData), NewProp_StressParticleComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusAuraParticleComponent = { "FocusAuraParticleComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, FocusAuraParticleComponent), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusAuraParticleComponent_MetaData), NewProp_FocusAuraParticleComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PostProcessComponent = { "PostProcessComponent", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTAgentVisualizer, PostProcessComponent), Z_Construct_UClass_UPostProcessComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PostProcessComponent_MetaData), NewProp_PostProcessComponent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentMesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressedMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusedMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusAuraParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bShowDebugText,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bUseTeamColors,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bShowStressEffects,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bShowFocusEffects,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressThresholdForEffects,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusThresholdForEffects,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HISMComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressParticleComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusAuraParticleComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PostProcessComponent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ANLTAgentVisualizer Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ANLTAgentVisualizer,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x008000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ANLTAgentVisualizer;
UClass* Z_Construct_UClass_ANLTAgentVisualizer(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ANLTAgentVisualizer;
		if (!Z_Registration_Info_UClass_ANLTAgentVisualizer.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTAgentVisualizer"),
				Z_Registration_Info_UClass_ANLTAgentVisualizer.InnerSingleton,
				nullptr,
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
		return Z_Registration_Info_UClass_ANLTAgentVisualizer.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ANLTAgentVisualizer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANLTAgentVisualizer.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ANLTAgentVisualizer.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ANLTAgentVisualizer);
ANLTAgentVisualizer::~ANLTAgentVisualizer() {}
// ********** End Class ANLTAgentVisualizer ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_EMassAgentVisualState, TEXT("EMassAgentVisualState"), &ZRIE_EMassAgentVisualState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4258324174U) },
		{ Z_Construct_UEnum_WorldEngine_EMassAgentTeam, TEXT("EMassAgentTeam"), &ZRIE_EMassAgentTeam, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2285948381U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANLTAgentVisualizer, TEXT("ANLTAgentVisualizer"), &Z_Registration_Info_UClass_ANLTAgentVisualizer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANLTAgentVisualizer), 2621767138U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h__Script_WorldEngine_b97615b8c9bff5e948877a2a800c892c791cda1f{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
