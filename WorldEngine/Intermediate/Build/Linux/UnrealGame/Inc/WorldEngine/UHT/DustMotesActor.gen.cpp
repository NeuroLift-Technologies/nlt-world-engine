// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/DustMotesActor.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDustMotesActor() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UParticleSystemComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ADustMotesActor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ADustMotesActor(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADustMotesActor **********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADustMotesActor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Simulation/DustMotesActor.h" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesActor.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustParticles_MetaData[] = {
		{ "Category", "Dust Motes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The dust motes particle system component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Simulation/DustMotesActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The dust motes particle system component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DustTemplate_MetaData[] = {
		{ "Category", "Dust Motes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The dust particle template - assigned from editor or content browser */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/DustMotesActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The dust particle template - assigned from editor or content browser" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bActive_MetaData[] = {
		{ "Category", "Dust Motes" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enable/disable the dust effect globally */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/DustMotesActor.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enable/disable the dust effect globally" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ADustMotesActor constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DustParticles;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DustTemplate;
	static void NewProp_bActive_SetBit(void* Obj)
	{
		((ADustMotesActor*)Obj)->bActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADustMotesActor constinit property declarations ****************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADustMotesActor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADustMotesActor Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DustParticles = { "DustParticles", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADustMotesActor, DustParticles), Z_Construct_UClass_UParticleSystemComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustParticles_MetaData), NewProp_DustParticles_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DustTemplate = { "DustTemplate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADustMotesActor, DustTemplate), Z_Construct_UClass_UParticleSystem, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DustTemplate_MetaData), NewProp_DustTemplate_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ADustMotesActor), &UHT_STATICS::NewProp_bActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bActive_MetaData), NewProp_bActive_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DustTemplate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADustMotesActor Property Definitions ***************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADustMotesActor,
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
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ADustMotesActor;
UClass* Z_Construct_UClass_ADustMotesActor(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADustMotesActor;
		if (!Z_Registration_Info_UClass_ADustMotesActor.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DustMotesActor"),
				Z_Registration_Info_UClass_ADustMotesActor.InnerSingleton,
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
		return Z_Registration_Info_UClass_ADustMotesActor.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADustMotesActor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADustMotesActor.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADustMotesActor.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADustMotesActor);
ADustMotesActor::~ADustMotesActor() {}
// ********** End Class ADustMotesActor ************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesActor_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADustMotesActor, TEXT("ADustMotesActor"), &Z_Registration_Info_UClass_ADustMotesActor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADustMotesActor), 2524190683U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesActor_h__Script_WorldEngine_0c05f141a5e189310c806cdf4a4cb7ef380eeeff{
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
