// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "World/NLTEnvironmentVariation.h"

#ifdef WORLDENGINE_NLTEnvironmentVariation_generated_h
#error "NLTEnvironmentVariation.generated.h already included, missing '#pragma once' in NLTEnvironmentVariation.h"
#endif
#define WORLDENGINE_NLTEnvironmentVariation_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTEnvironmentState;

// ********** Begin ScriptStruct FNLTEnvironmentState **********************************************
struct Z_Construct_UScriptStruct_FNLTEnvironmentState_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTEnvironmentState(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_19_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTEnvironmentState_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTEnvironmentState(ETypeConstructPhase::Inner); }


struct FNLTEnvironmentState;
// ********** End ScriptStruct FNLTEnvironmentState ************************************************

// ********** Begin Class UNLTEnvironmentVariationSubsystem ****************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetVariationCount); \
	DECLARE_FUNCTION(execGetActiveEnvironmentState); \
	DECLARE_FUNCTION(execApplyEnvironmentVariation); \
	DECLARE_FUNCTION(execGenerateEnvironmentVariation);


struct Z_Construct_UClass_UNLTEnvironmentVariationSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEnvironmentVariationSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTEnvironmentVariationSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTEnvironmentVariationSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTEnvironmentVariationSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTEnvironmentVariationSubsystem) \
	DECLARE_SERIALIZER(UNLTEnvironmentVariationSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTEnvironmentVariationSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTEnvironmentVariationSubsystem(UNLTEnvironmentVariationSubsystem&&) = delete; \
	UNLTEnvironmentVariationSubsystem(const UNLTEnvironmentVariationSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTEnvironmentVariationSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTEnvironmentVariationSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTEnvironmentVariationSubsystem) \
	NO_API virtual ~UNLTEnvironmentVariationSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_62_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h_65_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTEnvironmentVariationSubsystem;

// ********** End Class UNLTEnvironmentVariationSubsystem ******************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTEnvironmentVariation_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
