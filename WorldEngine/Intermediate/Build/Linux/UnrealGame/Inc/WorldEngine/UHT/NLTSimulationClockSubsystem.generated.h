// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/NLTSimulationClockSubsystem.h"

#ifdef WORLDENGINE_NLTSimulationClockSubsystem_generated_h
#error "NLTSimulationClockSubsystem.generated.h already included, missing '#pragma once' in NLTSimulationClockSubsystem.h"
#endif
#define WORLDENGINE_NLTSimulationClockSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UNLTSimulationClockSubsystem *********************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDeserializeClockState); \
	DECLARE_FUNCTION(execSerializeClockState); \
	DECLARE_FUNCTION(execGetDaysElapsed); \
	DECLARE_FUNCTION(execGetInitialTimeOfDay); \
	DECLARE_FUNCTION(execSetInitialTimeOfDay); \
	DECLARE_FUNCTION(execResetClock); \
	DECLARE_FUNCTION(execStop); \
	DECLARE_FUNCTION(execStart); \
	DECLARE_FUNCTION(execIsRunning); \
	DECLARE_FUNCTION(execSetTimeScale); \
	DECLARE_FUNCTION(execGetTimeScale); \
	DECLARE_FUNCTION(execSetFixedTimestepSeconds); \
	DECLARE_FUNCTION(execGetFixedTimestepSeconds); \
	DECLARE_FUNCTION(execGetTimeOfDayHours); \
	DECLARE_FUNCTION(execGetWorldTimeSeconds); \
	DECLARE_FUNCTION(execGetCurrentTick); \
	DECLARE_FUNCTION(execAdvanceTicks); \
	DECLARE_FUNCTION(execAdvanceTick);


struct Z_Construct_UClass_UNLTSimulationClockSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSimulationClockSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTSimulationClockSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTSimulationClockSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTSimulationClockSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTSimulationClockSubsystem) \
	DECLARE_SERIALIZER(UNLTSimulationClockSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTSimulationClockSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTSimulationClockSubsystem(UNLTSimulationClockSubsystem&&) = delete; \
	UNLTSimulationClockSubsystem(const UNLTSimulationClockSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTSimulationClockSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTSimulationClockSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTSimulationClockSubsystem) \
	NO_API virtual ~UNLTSimulationClockSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_17_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTSimulationClockSubsystem;

// ********** End Class UNLTSimulationClockSubsystem ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTSimulationClockSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
