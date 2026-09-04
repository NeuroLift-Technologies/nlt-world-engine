// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scenarios/NLTDemoGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTDemoGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTDemoGameMode(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTDemoGameMode(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ANLTDemoGameMode *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ANLTDemoGameMode_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Demo game mode for NLT Fusion scenario simulation.\n * On BeginPlay, loads a default scenario and starts the simulation.\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Scenarios/NLTDemoGameMode.h" },
		{ "ModuleRelativePath", "Public/Scenarios/NLTDemoGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Demo game mode for NLT Fusion scenario simulation.\nOn BeginPlay, loads a default scenario and starts the simulation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultScenarioId_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Default scenario to load on startup. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/NLTDemoGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Default scenario to load on startup." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ANLTDemoGameMode constinit property declarations *************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_DefaultScenarioId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ANLTDemoGameMode constinit property declarations ***************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANLTDemoGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ANLTDemoGameMode Property Definitions ************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DefaultScenarioId = { "DefaultScenarioId", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTDemoGameMode, DefaultScenarioId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultScenarioId_MetaData), NewProp_DefaultScenarioId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultScenarioId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ANLTDemoGameMode Property Definitions **************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AGameModeBase,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ANLTDemoGameMode,
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
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ANLTDemoGameMode;
UClass* Z_Construct_UClass_ANLTDemoGameMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ANLTDemoGameMode;
		if (!Z_Registration_Info_UClass_ANLTDemoGameMode.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTDemoGameMode"),
				Z_Registration_Info_UClass_ANLTDemoGameMode.InnerSingleton,
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
		return Z_Registration_Info_UClass_ANLTDemoGameMode.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ANLTDemoGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANLTDemoGameMode.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ANLTDemoGameMode.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ANLTDemoGameMode);
ANLTDemoGameMode::~ANLTDemoGameMode() {}
// ********** End Class ANLTDemoGameMode ***********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_NLTDemoGameMode_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANLTDemoGameMode, TEXT("ANLTDemoGameMode"), &Z_Registration_Info_UClass_ANLTDemoGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANLTDemoGameMode), 4013333590U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_NLTDemoGameMode_h__Script_WorldEngine_c402e1461daf3e8296e62978b9c3da390a95503a{
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
