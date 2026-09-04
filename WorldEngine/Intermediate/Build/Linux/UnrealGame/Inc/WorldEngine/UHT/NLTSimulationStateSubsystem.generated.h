// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NLTSimulationStateSubsystem.h"

#ifdef WORLDENGINE_NLTSimulationStateSubsystem_generated_h
#error "NLTSimulationStateSubsystem.generated.h already included, missing '#pragma once' in NLTSimulationStateSubsystem.h"
#endif
#define WORLDENGINE_NLTSimulationStateSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTAgentState;
struct FNLTRandomStream;
struct FNLTSimulationState;

// ********** Begin Class UNLTSimulationStateSubsystem *********************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetAllAgentStates); \
	DECLARE_FUNCTION(execRemoveAgentState); \
	DECLARE_FUNCTION(execGetAgentState); \
	DECLARE_FUNCTION(execSetAgentState); \
	DECLARE_FUNCTION(execSetSeed); \
	DECLARE_FUNCTION(execGetRNG); \
	DECLARE_FUNCTION(execGetRNGConst); \
	DECLARE_FUNCTION(execRestoreFromSnapshot); \
	DECLARE_FUNCTION(execCreateSnapshot); \
	DECLARE_FUNCTION(execResetState); \
	DECLARE_FUNCTION(execGetMutableState); \
	DECLARE_FUNCTION(execGetCurrentState);


struct Z_Construct_UClass_UNLTSimulationStateSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationStateSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTSimulationStateSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTSimulationStateSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTSimulationStateSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTSimulationStateSubsystem) \
	DECLARE_SERIALIZER(UNLTSimulationStateSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTSimulationStateSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTSimulationStateSubsystem(UNLTSimulationStateSubsystem&&) = delete; \
	UNLTSimulationStateSubsystem(const UNLTSimulationStateSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTSimulationStateSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTSimulationStateSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTSimulationStateSubsystem) \
	NO_API virtual ~UNLTSimulationStateSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_9_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTSimulationStateSubsystem;

// ********** End Class UNLTSimulationStateSubsystem ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationStateSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
