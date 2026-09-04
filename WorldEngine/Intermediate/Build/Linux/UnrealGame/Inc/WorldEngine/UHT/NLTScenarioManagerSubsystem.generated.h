// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Scenarios/Demo/NLTScenarioManagerSubsystem.h"

#ifdef WORLDENGINE_NLTScenarioManagerSubsystem_generated_h
#error "NLTScenarioManagerSubsystem.generated.h already included, missing '#pragma once' in NLTScenarioManagerSubsystem.h"
#endif
#define WORLDENGINE_NLTScenarioManagerSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UNLTEnvironmentVariationSubsystem;
class UScenarioDataAsset;
struct FNLTScenarioParams;

// ********** Begin ScriptStruct FNLTScenarioParams ************************************************
struct Z_Construct_UScriptStruct_FNLTScenarioParams_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioParams(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_21_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTScenarioParams_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTScenarioParams(ETypeConstructPhase::Inner); }


struct FNLTScenarioParams;
// ********** End ScriptStruct FNLTScenarioParams **************************************************

// ********** Begin Class UNLTScenarioManagerSubsystem *********************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetEnvironmentVariationSubsystem); \
	DECLARE_FUNCTION(execGetScenarioTick); \
	DECLARE_FUNCTION(execGetActiveParams); \
	DECLARE_FUNCTION(execIsScenarioActive); \
	DECLARE_FUNCTION(execStopScenario); \
	DECLARE_FUNCTION(execGetActiveScenario); \
	DECLARE_FUNCTION(execStartScenarioWithAsset); \
	DECLARE_FUNCTION(execStartScenario);


struct Z_Construct_UClass_UNLTScenarioManagerSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTScenarioManagerSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTScenarioManagerSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTScenarioManagerSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTScenarioManagerSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTScenarioManagerSubsystem) \
	DECLARE_SERIALIZER(UNLTScenarioManagerSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTScenarioManagerSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTScenarioManagerSubsystem(UNLTScenarioManagerSubsystem&&) = delete; \
	UNLTScenarioManagerSubsystem(const UNLTScenarioManagerSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTScenarioManagerSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTScenarioManagerSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTScenarioManagerSubsystem) \
	NO_API virtual ~UNLTScenarioManagerSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_49_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h_52_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTScenarioManagerSubsystem;

// ********** End Class UNLTScenarioManagerSubsystem ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTScenarioManagerSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
