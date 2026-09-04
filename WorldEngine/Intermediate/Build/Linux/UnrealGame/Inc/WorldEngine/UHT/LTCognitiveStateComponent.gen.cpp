// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/LTCognitiveStateComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeLTCognitiveStateComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ULTCognitiveStateComponent(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ULTCognitiveStateComponent(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ULTCognitiveStateComponent ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ULTCognitiveStateComponent_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Agents/LTCognitiveStateComponent.h" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Focus_MetaData[] = {
		{ "Category", "Cognitive" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Core cognitive dimensions\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Core cognitive dimensions" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CognitiveLoad_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stress_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Burnout_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Independence_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FusionReady_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuccessRate_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionalState_MetaData[] = {
		{ "Category", "Cognitive" },
		{ "ModuleRelativePath", "Public/Agents/LTCognitiveStateComponent.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ULTCognitiveStateComponent constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Focus;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CognitiveLoad;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stress;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Burnout;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Independence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FusionReady;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SuccessRate;
	static const UECodeGen_Private::FNamePropertyParams NewProp_EmotionalState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ULTCognitiveStateComponent constinit property declarations *****************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULTCognitiveStateComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ULTCognitiveStateComponent Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Focus = { "Focus", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, Focus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Focus_MetaData), NewProp_Focus_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CognitiveLoad = { "CognitiveLoad", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, CognitiveLoad), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CognitiveLoad_MetaData), NewProp_CognitiveLoad_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Stress = { "Stress", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, Stress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stress_MetaData), NewProp_Stress_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Burnout = { "Burnout", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, Burnout), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Burnout_MetaData), NewProp_Burnout_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Independence = { "Independence", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, Independence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Independence_MetaData), NewProp_Independence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FusionReady = { "FusionReady", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, FusionReady), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FusionReady_MetaData), NewProp_FusionReady_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SuccessRate = { "SuccessRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, SuccessRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuccessRate_MetaData), NewProp_SuccessRate_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_EmotionalState = { "EmotionalState", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ULTCognitiveStateComponent, EmotionalState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionalState_MetaData), NewProp_EmotionalState_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Focus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitiveLoad,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stress,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Burnout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Independence,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FusionReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SuccessRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmotionalState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ULTCognitiveStateComponent Property Definitions ****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UActorComponent,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ULTCognitiveStateComponent,
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
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ULTCognitiveStateComponent;
UClass* Z_Construct_UClass_ULTCognitiveStateComponent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ULTCognitiveStateComponent;
		if (!Z_Registration_Info_UClass_ULTCognitiveStateComponent.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("LTCognitiveStateComponent"),
				Z_Registration_Info_UClass_ULTCognitiveStateComponent.InnerSingleton,
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
		return Z_Registration_Info_UClass_ULTCognitiveStateComponent.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ULTCognitiveStateComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULTCognitiveStateComponent.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ULTCognitiveStateComponent.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ULTCognitiveStateComponent);
ULTCognitiveStateComponent::~ULTCognitiveStateComponent() {}
// ********** End Class ULTCognitiveStateComponent *************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_LTCognitiveStateComponent_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULTCognitiveStateComponent, TEXT("ULTCognitiveStateComponent"), &Z_Registration_Info_UClass_ULTCognitiveStateComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULTCognitiveStateComponent), 3665381141U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_LTCognitiveStateComponent_h__Script_WorldEngine_0ba6a2a9b1f9b81167dcc2738e197f904428c1a1{
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
