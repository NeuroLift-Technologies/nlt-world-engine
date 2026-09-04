// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "World/NLTWorldGenerator.h"

#ifdef WORLDENGINE_NLTWorldGenerator_generated_h
#error "NLTWorldGenerator.generated.h already included, missing '#pragma once' in NLTWorldGenerator.h"
#endif
#define WORLDENGINE_NLTWorldGenerator_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTWorldGenerationParams;
struct FNLTWorldGenerationResult;

// ********** Begin ScriptStruct FNLTWorldGenerationParams *****************************************
struct Z_Construct_UScriptStruct_FNLTWorldGenerationParams_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationParams(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_13_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTWorldGenerationParams_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTWorldGenerationParams(ETypeConstructPhase::Inner); }


struct FNLTWorldGenerationParams;
// ********** End ScriptStruct FNLTWorldGenerationParams *******************************************

// ********** Begin ScriptStruct FNLTGeneratedDistrict *********************************************
struct Z_Construct_UScriptStruct_FNLTGeneratedDistrict_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTGeneratedDistrict(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_43_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTGeneratedDistrict_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTGeneratedDistrict(ETypeConstructPhase::Inner); }


struct FNLTGeneratedDistrict;
// ********** End ScriptStruct FNLTGeneratedDistrict ***********************************************

// ********** Begin ScriptStruct FNLTGeneratedBuilding *********************************************
struct Z_Construct_UScriptStruct_FNLTGeneratedBuilding_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTGeneratedBuilding(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_70_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTGeneratedBuilding_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTGeneratedBuilding(ETypeConstructPhase::Inner); }


struct FNLTGeneratedBuilding;
// ********** End ScriptStruct FNLTGeneratedBuilding ***********************************************

// ********** Begin ScriptStruct FNLTWorldGenerationResult *****************************************
struct Z_Construct_UScriptStruct_FNLTWorldGenerationResult_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldGenerationResult(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_85_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTWorldGenerationResult_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTWorldGenerationResult(ETypeConstructPhase::Inner); }


struct FNLTWorldGenerationResult;
// ********** End ScriptStruct FNLTWorldGenerationResult *******************************************

// ********** Begin Class UNLTWorldGeneratorSubsystem **********************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetGeneratedWorld); \
	DECLARE_FUNCTION(execIsWorldGenerated); \
	DECLARE_FUNCTION(execClearWorld); \
	DECLARE_FUNCTION(execGenerateWorld);


struct Z_Construct_UClass_UNLTWorldGeneratorSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWorldGeneratorSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTWorldGeneratorSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTWorldGeneratorSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTWorldGeneratorSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTWorldGeneratorSubsystem) \
	DECLARE_SERIALIZER(UNLTWorldGeneratorSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTWorldGeneratorSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTWorldGeneratorSubsystem(UNLTWorldGeneratorSubsystem&&) = delete; \
	UNLTWorldGeneratorSubsystem(const UNLTWorldGeneratorSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTWorldGeneratorSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTWorldGeneratorSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTWorldGeneratorSubsystem) \
	NO_API virtual ~UNLTWorldGeneratorSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_97_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h_100_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTWorldGeneratorSubsystem;

// ********** End Class UNLTWorldGeneratorSubsystem ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldGenerator_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
