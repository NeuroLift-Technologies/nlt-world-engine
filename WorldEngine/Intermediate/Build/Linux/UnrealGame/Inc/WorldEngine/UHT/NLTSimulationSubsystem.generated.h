// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/NLTSimulationSubsystem.h"

#ifdef WORLDENGINE_NLTSimulationSubsystem_generated_h
#error "NLTSimulationSubsystem.generated.h already included, missing '#pragma once' in NLTSimulationSubsystem.h"
#endif
#define WORLDENGINE_NLTSimulationSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ESimulationMode : uint8;

// ********** Begin Class UNLTSimulationSubsystem **************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetSimulationRate); \
	DECLARE_FUNCTION(execSetSimulationRate); \
	DECLARE_FUNCTION(execSetMode); \
	DECLARE_FUNCTION(execGetMode); \
	DECLARE_FUNCTION(execGetSimulationTimeMinutes); \
	DECLARE_FUNCTION(execGetCurrentTick); \
	DECLARE_FUNCTION(execStepTicks); \
	DECLARE_FUNCTION(execStepTick); \
	DECLARE_FUNCTION(execIsRunning); \
	DECLARE_FUNCTION(execResumeSimulation); \
	DECLARE_FUNCTION(execPauseSimulation); \
	DECLARE_FUNCTION(execStopSimulation); \
	DECLARE_FUNCTION(execStartSimulation);


struct Z_Construct_UClass_UNLTSimulationSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTSimulationSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTSimulationSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTSimulationSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTSimulationSubsystem) \
	DECLARE_SERIALIZER(UNLTSimulationSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTSimulationSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTSimulationSubsystem(UNLTSimulationSubsystem&&) = delete; \
	UNLTSimulationSubsystem(const UNLTSimulationSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTSimulationSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTSimulationSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTSimulationSubsystem) \
	NO_API virtual ~UNLTSimulationSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_11_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTSimulationSubsystem;

// ********** End Class UNLTSimulationSubsystem ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
