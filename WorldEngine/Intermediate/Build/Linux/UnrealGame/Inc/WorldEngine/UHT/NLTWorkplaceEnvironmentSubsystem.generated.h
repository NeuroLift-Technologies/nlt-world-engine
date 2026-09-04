// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/NLTWorkplaceEnvironmentSubsystem.h"

#ifdef WORLDENGINE_NLTWorkplaceEnvironmentSubsystem_generated_h
#error "NLTWorkplaceEnvironmentSubsystem.generated.h already included, missing '#pragma once' in NLTWorkplaceEnvironmentSubsystem.h"
#endif
#define WORLDENGINE_NLTWorkplaceEnvironmentSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UNLTWorkplaceEnvironmentSubsystem ****************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execHandleAuthoritativeTick); \
	DECLARE_FUNCTION(execGetScenarioId); \
	DECLARE_FUNCTION(execGetMasterSeed); \
	DECLARE_FUNCTION(execDeserializeEnvironmentState); \
	DECLARE_FUNCTION(execSerializeEnvironmentState); \
	DECLARE_FUNCTION(execStepEnvironmentSimulation); \
	DECLARE_FUNCTION(execIsRunning); \
	DECLARE_FUNCTION(execStopEnvironmentSimulation); \
	DECLARE_FUNCTION(execStartEnvironmentSimulation); \
	DECLARE_FUNCTION(execConfigureEnvironment);


struct Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTWorkplaceEnvironmentSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTWorkplaceEnvironmentSubsystem) \
	DECLARE_SERIALIZER(UNLTWorkplaceEnvironmentSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTWorkplaceEnvironmentSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTWorkplaceEnvironmentSubsystem(UNLTWorkplaceEnvironmentSubsystem&&) = delete; \
	UNLTWorkplaceEnvironmentSubsystem(const UNLTWorkplaceEnvironmentSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTWorkplaceEnvironmentSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTWorkplaceEnvironmentSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTWorkplaceEnvironmentSubsystem) \
	NO_API virtual ~UNLTWorkplaceEnvironmentSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_41_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h_44_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTWorkplaceEnvironmentSubsystem;

// ********** End Class UNLTWorkplaceEnvironmentSubsystem ******************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTWorkplaceEnvironmentSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
