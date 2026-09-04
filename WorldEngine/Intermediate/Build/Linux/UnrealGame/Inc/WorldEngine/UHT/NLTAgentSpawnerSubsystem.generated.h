// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Agents/NLTAgentSpawnerSubsystem.h"

#ifdef WORLDENGINE_NLTAgentSpawnerSubsystem_generated_h
#error "NLTAgentSpawnerSubsystem.generated.h already included, missing '#pragma once' in NLTAgentSpawnerSubsystem.h"
#endif
#define WORLDENGINE_NLTAgentSpawnerSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTSpawnRequest;

// ********** Begin ScriptStruct FNLTSpawnRequest **************************************************
struct Z_Construct_UScriptStruct_FNLTSpawnRequest_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSpawnRequest(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_14_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTSpawnRequest_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTSpawnRequest(ETypeConstructPhase::Inner); }


struct FNLTSpawnRequest;
// ********** End ScriptStruct FNLTSpawnRequest ****************************************************

// ********** Begin Class UNLTAgentSpawnerSubsystem ************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetNeedGrowthMultiplier); \
	DECLARE_FUNCTION(execSetSpawnSeed); \
	DECLARE_FUNCTION(execGetAgentCount); \
	DECLARE_FUNCTION(execDespawnAllAgents); \
	DECLARE_FUNCTION(execSpawnAgentsByType); \
	DECLARE_FUNCTION(execSpawnAgents); \
	DECLARE_FUNCTION(execSpawnAgent);


struct Z_Construct_UClass_UNLTAgentSpawnerSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAgentSpawnerSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTAgentSpawnerSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTAgentSpawnerSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTAgentSpawnerSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTAgentSpawnerSubsystem) \
	DECLARE_SERIALIZER(UNLTAgentSpawnerSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTAgentSpawnerSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTAgentSpawnerSubsystem(UNLTAgentSpawnerSubsystem&&) = delete; \
	UNLTAgentSpawnerSubsystem(const UNLTAgentSpawnerSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTAgentSpawnerSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTAgentSpawnerSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTAgentSpawnerSubsystem) \
	NO_API virtual ~UNLTAgentSpawnerSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_29_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTAgentSpawnerSubsystem;

// ********** End Class UNLTAgentSpawnerSubsystem **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
