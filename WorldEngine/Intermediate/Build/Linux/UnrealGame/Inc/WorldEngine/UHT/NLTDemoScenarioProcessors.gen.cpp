// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scenarios/Demo/NLTDemoScenarioProcessors.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTDemoScenarioProcessors() {}

// ********** Begin Cross Module References ********************************************************
MASSENTITY_API UClass* Z_Construct_UClass_UMassProcessor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioDecisionProcessor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioMovementProcessor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioNeedsProcessor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioDecisionProcessor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioMovementProcessor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioNeedsProcessor(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UNLTScenarioNeedsProcessor ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTScenarioNeedsProcessor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Grows each agent's need drives at fixed per-second rates using the fixed\n * simulation timestep (NLTDemoScenario::TickDeltaSeconds). Deterministic:\n * no wall-clock delta time, no random variation. Parallel-safe (fragment-local\n * writes only). Must run before the decision processor.\n */" },
#endif
		{ "IncludePath", "Scenarios/Demo/NLTDemoScenarioProcessors.h" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioProcessors.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Grows each agent's need drives at fixed per-second rates using the fixed\nsimulation timestep (NLTDemoScenario::TickDeltaSeconds). Deterministic:\nno wall-clock delta time, no random variation. Parallel-safe (fragment-local\nwrites only). Must run before the decision processor." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTScenarioNeedsProcessor constinit property declarations ***************
// ********** End Class UNLTScenarioNeedsProcessor constinit property declarations *****************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTScenarioNeedsProcessor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UMassProcessor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTScenarioNeedsProcessor,
	"Mass",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x400030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor;
UClass* Z_Construct_UClass_UNLTScenarioNeedsProcessor(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTScenarioNeedsProcessor;
		if (!Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTScenarioNeedsProcessor"),
				Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor.InnerSingleton,
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
		return Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTScenarioNeedsProcessor);
UNLTScenarioNeedsProcessor::~UNLTScenarioNeedsProcessor() {}
// ********** End Class UNLTScenarioNeedsProcessor *************************************************

// ********** Begin Class UNLTScenarioDecisionProcessor ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTScenarioDecisionProcessor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Deterministic decision-making pass. Every DecisionIntervalTicks an agent\n * re-evaluates its highest need and selects a target location:\n *  1. Gathers candidate world locations matching the need (TArray copy)\n *  2. Sorts candidates deterministically (score desc, distance asc, name asc)\n *  3. Falls back to a deterministic seeded wander target when no candidate exists\n * Writes Intent/TargetPosition into the shared agent fragments so the\n * visualizer and StateTree stay consistent.\n */" },
#endif
		{ "IncludePath", "Scenarios/Demo/NLTDemoScenarioProcessors.h" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioProcessors.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deterministic decision-making pass. Every DecisionIntervalTicks an agent\nre-evaluates its highest need and selects a target location:\n 1. Gathers candidate world locations matching the need (TArray copy)\n 2. Sorts candidates deterministically (score desc, distance asc, name asc)\n 3. Falls back to a deterministic seeded wander target when no candidate exists\nWrites Intent/TargetPosition into the shared agent fragments so the\nvisualizer and StateTree stay consistent." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTScenarioDecisionProcessor constinit property declarations ************
// ********** End Class UNLTScenarioDecisionProcessor constinit property declarations **************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTScenarioDecisionProcessor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UMassProcessor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTScenarioDecisionProcessor,
	"Mass",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x400030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor;
UClass* Z_Construct_UClass_UNLTScenarioDecisionProcessor(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTScenarioDecisionProcessor;
		if (!Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTScenarioDecisionProcessor"),
				Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor.InnerSingleton,
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
		return Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTScenarioDecisionProcessor);
UNLTScenarioDecisionProcessor::~UNLTScenarioDecisionProcessor() {}
// ********** End Class UNLTScenarioDecisionProcessor **********************************************

// ********** Begin Class UNLTScenarioMovementProcessor ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTScenarioMovementProcessor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Custom movement integration (no Chaos physics): closed-form step toward the\n * behavior target at the agent's configured speed over the fixed timestep.\n * Updates the shared location fragment (Position/Velocity/Heading/bIsMoving)\n * and updates behavior phase on arrival so decisions can re-evaluate immediately.\n * Parallel-safe.\n */" },
#endif
		{ "IncludePath", "Scenarios/Demo/NLTDemoScenarioProcessors.h" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioProcessors.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Custom movement integration (no Chaos physics): closed-form step toward the\nbehavior target at the agent's configured speed over the fixed timestep.\nUpdates the shared location fragment (Position/Velocity/Heading/bIsMoving)\nand updates behavior phase on arrival so decisions can re-evaluate immediately.\nParallel-safe." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTScenarioMovementProcessor constinit property declarations ************
// ********** End Class UNLTScenarioMovementProcessor constinit property declarations **************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTScenarioMovementProcessor>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UMassProcessor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTScenarioMovementProcessor,
	"Mass",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x400030A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTScenarioMovementProcessor;
UClass* Z_Construct_UClass_UNLTScenarioMovementProcessor(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTScenarioMovementProcessor;
		if (!Z_Registration_Info_UClass_UNLTScenarioMovementProcessor.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTScenarioMovementProcessor"),
				Z_Registration_Info_UClass_UNLTScenarioMovementProcessor.InnerSingleton,
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
		return Z_Registration_Info_UClass_UNLTScenarioMovementProcessor.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTScenarioMovementProcessor.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTScenarioMovementProcessor.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTScenarioMovementProcessor.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTScenarioMovementProcessor);
UNLTScenarioMovementProcessor::~UNLTScenarioMovementProcessor() {}
// ********** End Class UNLTScenarioMovementProcessor **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioProcessors_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTScenarioNeedsProcessor, TEXT("UNLTScenarioNeedsProcessor"), &Z_Registration_Info_UClass_UNLTScenarioNeedsProcessor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTScenarioNeedsProcessor), 2446189867U) },
		{ Z_Construct_UClass_UNLTScenarioDecisionProcessor, TEXT("UNLTScenarioDecisionProcessor"), &Z_Registration_Info_UClass_UNLTScenarioDecisionProcessor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTScenarioDecisionProcessor), 3508692206U) },
		{ Z_Construct_UClass_UNLTScenarioMovementProcessor, TEXT("UNLTScenarioMovementProcessor"), &Z_Registration_Info_UClass_UNLTScenarioMovementProcessor, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTScenarioMovementProcessor), 1958952748U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioProcessors_h__Script_WorldEngine_9491ffd71413067842dc8213cb8c055e33b9cc0b{
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
