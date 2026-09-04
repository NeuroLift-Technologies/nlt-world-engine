// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Scaling/NLTPopulationScaler.h"

#ifdef WORLDENGINE_NLTPopulationScaler_generated_h
#error "NLTPopulationScaler.generated.h already included, missing '#pragma once' in NLTPopulationScaler.h"
#endif
#define WORLDENGINE_NLTPopulationScaler_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTScaleMetrics;

// ********** Begin ScriptStruct FNLTScaleMetrics **************************************************
struct Z_Construct_UScriptStruct_FNLTScaleMetrics_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScaleMetrics(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_13_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTScaleMetrics_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTScaleMetrics(ETypeConstructPhase::Inner); }


struct FNLTScaleMetrics;
// ********** End ScriptStruct FNLTScaleMetrics ****************************************************

// ********** Begin Class UNLTPopulationScaler *****************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execIsBenchmarking); \
	DECLARE_FUNCTION(execGetCurrentMetrics); \
	DECLARE_FUNCTION(execScalePopulation); \
	DECLARE_FUNCTION(execStopBenchmark); \
	DECLARE_FUNCTION(execStartBenchmark);


struct Z_Construct_UClass_UNLTPopulationScaler_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTPopulationScaler(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTPopulationScaler_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTPopulationScaler(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTPopulationScaler, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTPopulationScaler) \
	DECLARE_SERIALIZER(UNLTPopulationScaler)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTPopulationScaler(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTPopulationScaler(UNLTPopulationScaler&&) = delete; \
	UNLTPopulationScaler(const UNLTPopulationScaler&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTPopulationScaler); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTPopulationScaler); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTPopulationScaler) \
	NO_API virtual ~UNLTPopulationScaler();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_43_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h_46_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTPopulationScaler;

// ********** End Class UNLTPopulationScaler *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scaling_NLTPopulationScaler_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
