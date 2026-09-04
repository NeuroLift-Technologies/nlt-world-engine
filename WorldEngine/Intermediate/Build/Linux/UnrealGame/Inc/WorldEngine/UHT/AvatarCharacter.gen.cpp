// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/AvatarCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeAvatarCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UMaterialInstanceDynamic(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UPostProcessComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_AAvatarCharacter(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ECharacterTeam(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ECharacterVisualState(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_AAvatarCharacter(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ULTCognitiveStateComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum ECharacterVisualState *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ECharacterVisualState_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ECharacterVisualState>()
{
	return Z_Construct_UEnum_WorldEngine_ECharacterVisualState(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Visual state for character\n" },
#endif
		{ "Focused.DisplayName", "Focused" },
		{ "Focused.Name", "ECharacterVisualState::Focused" },
		{ "Interacting.DisplayName", "Interacting" },
		{ "Interacting.Name", "ECharacterVisualState::Interacting" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
		{ "Normal.DisplayName", "Normal" },
		{ "Normal.Name", "ECharacterVisualState::Normal" },
		{ "Stressed.DisplayName", "Stressed" },
		{ "Stressed.Name", "ECharacterVisualState::Stressed" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Visual state for character" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECharacterVisualState::Normal", (int64)ECharacterVisualState::Normal },
		{ "ECharacterVisualState::Focused", (int64)ECharacterVisualState::Focused },
		{ "ECharacterVisualState::Stressed", (int64)ECharacterVisualState::Stressed },
		{ "ECharacterVisualState::Interacting", (int64)ECharacterVisualState::Interacting },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ECharacterVisualState",
	"ECharacterVisualState",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ECharacterVisualState;
UEnum* Z_Construct_UEnum_WorldEngine_ECharacterVisualState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ECharacterVisualState.OuterSingleton)
		{
			ZRIE_ECharacterVisualState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ECharacterVisualState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ECharacterVisualState"));
		}
		return ZRIE_ECharacterVisualState.OuterSingleton;
	}
	if (!ZRIE_ECharacterVisualState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ECharacterVisualState.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ECharacterVisualState.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ECharacterVisualState *******************************************************

// ********** Begin Enum ECharacterTeam ************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ECharacterTeam_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ECharacterTeam>()
{
	return Z_Construct_UEnum_WorldEngine_ECharacterTeam(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Team identification\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
		{ "Neutral.DisplayName", "Neutral" },
		{ "Neutral.Name", "ECharacterTeam::Neutral" },
		{ "TeamA.DisplayName", "Team A" },
		{ "TeamA.Name", "ECharacterTeam::TeamA" },
		{ "TeamB.DisplayName", "Team B" },
		{ "TeamB.Name", "ECharacterTeam::TeamB" },
		{ "TeamC.DisplayName", "Team C" },
		{ "TeamC.Name", "ECharacterTeam::TeamC" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Team identification" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ECharacterTeam::Neutral", (int64)ECharacterTeam::Neutral },
		{ "ECharacterTeam::TeamA", (int64)ECharacterTeam::TeamA },
		{ "ECharacterTeam::TeamB", (int64)ECharacterTeam::TeamB },
		{ "ECharacterTeam::TeamC", (int64)ECharacterTeam::TeamC },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ECharacterTeam",
	"ECharacterTeam",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ECharacterTeam;
UEnum* Z_Construct_UEnum_WorldEngine_ECharacterTeam(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ECharacterTeam.OuterSingleton)
		{
			ZRIE_ECharacterTeam.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ECharacterTeam, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ECharacterTeam"));
		}
		return ZRIE_ECharacterTeam.OuterSingleton;
	}
	if (!ZRIE_ECharacterTeam.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ECharacterTeam.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ECharacterTeam.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ECharacterTeam **************************************************************

// ********** Begin Class AAvatarCharacter *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AAvatarCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Agents/AvatarCharacter.h" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WanderRadius_MetaData[] = {
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============== AI Properties ==============\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "============== AI Properties ==============" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaitTimeMin_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaitTimeMax_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionRange_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Team_MetaData[] = {
		{ "Category", "Visual|Team" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Team identification\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Team identification" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BodyMaterial_MetaData[] = {
		{ "Category", "Visual|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Material overrides for different body parts\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Material overrides for different body parts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HeadMaterial_MetaData[] = {
		{ "Category", "Visual|Materials" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LimbsMaterial_MetaData[] = {
		{ "Category", "Visual|Materials" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DynamicBodyMaterial_MetaData[] = {
		{ "Category", "Visual|Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Dynamic material instances\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Dynamic material instances" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DynamicHeadMaterial_MetaData[] = {
		{ "Category", "Visual|Materials" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressParticles_MetaData[] = {
		{ "Category", "Visual|Particles" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Stress particles (appears when stressed)\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stress particles (appears when stressed)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressParticleComponent_MetaData[] = {
		{ "Category", "Visual|Particles" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusAuraParticles_MetaData[] = {
		{ "Category", "Visual|Particles" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Focus aura (appears when focused)\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Focus aura (appears when focused)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusAuraComponent_MetaData[] = {
		{ "Category", "Visual|Particles" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionParticles_MetaData[] = {
		{ "Category", "Visual|Particles" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Interaction particles\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Interaction particles" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionParticleComponent_MetaData[] = {
		{ "Category", "Visual|Particles" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PostProcessComponent_MetaData[] = {
		{ "Category", "Visual|PostProcessing" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Character-specific post processing component\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character-specific post processing component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentVisualState_MetaData[] = {
		{ "Category", "Visual|State" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============== Visual State ==============\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "============== Visual State ==============" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StressThresholdForParticles_MetaData[] = {
		{ "Category", "Visual|State" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FocusThresholdForAura_MetaData[] = {
		{ "Category", "Visual|State" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CognitiveState_MetaData[] = {
		{ "Category", "Cognitive" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// ============== Cognitive State ==============\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/AvatarCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "============== Cognitive State ==============" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AAvatarCharacter constinit property declarations *************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WanderRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaitTimeMin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaitTimeMax;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InteractionRange;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Team_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Team;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BodyMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_HeadMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LimbsMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DynamicBodyMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DynamicHeadMaterial;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StressParticleComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusAuraParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FocusAuraComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractionParticleComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PostProcessComponent;
	static const UECodeGen_Private::FBytePropertyParams NewProp_CurrentVisualState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_CurrentVisualState;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StressThresholdForParticles;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FocusThresholdForAura;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CognitiveState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AAvatarCharacter constinit property declarations ***************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAvatarCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AAvatarCharacter Property Definitions ************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WanderRadius = { "WanderRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, WanderRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WanderRadius_MetaData), NewProp_WanderRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WaitTimeMin = { "WaitTimeMin", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, WaitTimeMin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaitTimeMin_MetaData), NewProp_WaitTimeMin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WaitTimeMax = { "WaitTimeMax", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, WaitTimeMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaitTimeMax_MetaData), NewProp_WaitTimeMax_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InteractionRange = { "InteractionRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, InteractionRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionRange_MetaData), NewProp_InteractionRange_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Team_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Team = { "Team", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, Team), Z_Construct_UEnum_WorldEngine_ECharacterTeam, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Team_MetaData), NewProp_Team_MetaData) }; // b34dd92faf1995298e921de2a33afb14eeb9a455
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BodyMaterial = { "BodyMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, BodyMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BodyMaterial_MetaData), NewProp_BodyMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_HeadMaterial = { "HeadMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, HeadMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HeadMaterial_MetaData), NewProp_HeadMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LimbsMaterial = { "LimbsMaterial", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, LimbsMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LimbsMaterial_MetaData), NewProp_LimbsMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DynamicBodyMaterial = { "DynamicBodyMaterial", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, DynamicBodyMaterial), Z_Construct_UClass_UMaterialInstanceDynamic, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DynamicBodyMaterial_MetaData), NewProp_DynamicBodyMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DynamicHeadMaterial = { "DynamicHeadMaterial", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, DynamicHeadMaterial), Z_Construct_UClass_UMaterialInstanceDynamic, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DynamicHeadMaterial_MetaData), NewProp_DynamicHeadMaterial_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressParticles = { "StressParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, StressParticles), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressParticles_MetaData), NewProp_StressParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StressParticleComponent = { "StressParticleComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, StressParticleComponent), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressParticleComponent_MetaData), NewProp_StressParticleComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusAuraParticles = { "FocusAuraParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, FocusAuraParticles), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusAuraParticles_MetaData), NewProp_FocusAuraParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FocusAuraComponent = { "FocusAuraComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, FocusAuraComponent), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusAuraComponent_MetaData), NewProp_FocusAuraComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InteractionParticles = { "InteractionParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, InteractionParticles), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionParticles_MetaData), NewProp_InteractionParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InteractionParticleComponent = { "InteractionParticleComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, InteractionParticleComponent), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionParticleComponent_MetaData), NewProp_InteractionParticleComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PostProcessComponent = { "PostProcessComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, PostProcessComponent), Z_Construct_UClass_UPostProcessComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PostProcessComponent_MetaData), NewProp_PostProcessComponent_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_CurrentVisualState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_CurrentVisualState = { "CurrentVisualState", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, CurrentVisualState), Z_Construct_UEnum_WorldEngine_ECharacterVisualState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentVisualState_MetaData), NewProp_CurrentVisualState_MetaData) }; // 99f0a7e61da16a927fd2106456e5c8869ba7f0eb
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_StressThresholdForParticles = { "StressThresholdForParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, StressThresholdForParticles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StressThresholdForParticles_MetaData), NewProp_StressThresholdForParticles_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FocusThresholdForAura = { "FocusThresholdForAura", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, FocusThresholdForAura), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FocusThresholdForAura_MetaData), NewProp_FocusThresholdForAura_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CognitiveState = { "CognitiveState", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarCharacter, CognitiveState), Z_Construct_UClass_ULTCognitiveStateComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CognitiveState_MetaData), NewProp_CognitiveState_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WanderRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WaitTimeMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WaitTimeMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InteractionRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Team_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Team,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BodyMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HeadMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LimbsMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DynamicBodyMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DynamicHeadMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressParticleComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusAuraParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusAuraComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InteractionParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InteractionParticleComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PostProcessComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentVisualState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentVisualState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StressThresholdForParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FocusThresholdForAura,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitiveState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AAvatarCharacter Property Definitions **************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AAvatarCharacter,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_AAvatarCharacter;
UClass* Z_Construct_UClass_AAvatarCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AAvatarCharacter;
		if (!Z_Registration_Info_UClass_AAvatarCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("AvatarCharacter"),
				Z_Registration_Info_UClass_AAvatarCharacter.InnerSingleton,
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
		return Z_Registration_Info_UClass_AAvatarCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AAvatarCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAvatarCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AAvatarCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AAvatarCharacter);
AAvatarCharacter::~AAvatarCharacter() {}
// ********** End Class AAvatarCharacter ***********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ECharacterVisualState, TEXT("ECharacterVisualState"), &ZRIE_ECharacterVisualState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2582685670U) },
		{ Z_Construct_UEnum_WorldEngine_ECharacterTeam, TEXT("ECharacterTeam"), &ZRIE_ECharacterTeam, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3008223535U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAvatarCharacter, TEXT("AAvatarCharacter"), &Z_Registration_Info_UClass_AAvatarCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAvatarCharacter), 1206628097U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h__Script_WorldEngine_a547d0724e4cab5876dc8a995f2acf7e01adb0c8{
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
