// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/NLTTrainingEnvironment.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTTrainingEnvironment() {}

// ********** Begin Cross Module References ********************************************************
LEARNINGAGENTSTRAINING_API UClass* Z_Construct_UClass_ULearningAgentsTrainingEnvironment(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTTrainingEnvironment(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTTrainingEnvironment(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UNLTTrainingEnvironment **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTTrainingEnvironment_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Agents/NLTTrainingEnvironment.h" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingEnvironment.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTTrainingEnvironment constinit property declarations ******************
// ********** End Class UNLTTrainingEnvironment constinit property declarations ********************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTTrainingEnvironment>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ULearningAgentsTrainingEnvironment,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTTrainingEnvironment,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTTrainingEnvironment;
UClass* Z_Construct_UClass_UNLTTrainingEnvironment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTTrainingEnvironment;
		if (!Z_Registration_Info_UClass_UNLTTrainingEnvironment.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTTrainingEnvironment"),
				Z_Registration_Info_UClass_UNLTTrainingEnvironment.InnerSingleton,
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
		return Z_Registration_Info_UClass_UNLTTrainingEnvironment.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTTrainingEnvironment.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTTrainingEnvironment.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTTrainingEnvironment.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTTrainingEnvironment);
UNLTTrainingEnvironment::~UNLTTrainingEnvironment() {}
// ********** End Class UNLTTrainingEnvironment ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingEnvironment_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTTrainingEnvironment, TEXT("UNLTTrainingEnvironment"), &Z_Registration_Info_UClass_UNLTTrainingEnvironment, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTTrainingEnvironment), 3353207105U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingEnvironment_h__Script_WorldEngine_61b43313b1bc1a3bb7c0314c3187d092445deca1{
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
