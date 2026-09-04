// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "World/NLTSmartObjectWorldSubsystem.h"

#ifdef WORLDENGINE_NLTSmartObjectWorldSubsystem_generated_h
#error "NLTSmartObjectWorldSubsystem.generated.h already included, missing '#pragma once' in NLTSmartObjectWorldSubsystem.h"
#endif
#define WORLDENGINE_NLTSmartObjectWorldSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
enum class ENLTAgentNeed : uint8;
struct FNLTWorldLocation;

// ********** Begin ScriptStruct FNLTWorldLocation *************************************************
struct Z_Construct_UScriptStruct_FNLTWorldLocation_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldLocation(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_13_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTWorldLocation_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTWorldLocation(ETypeConstructPhase::Inner); }


struct FNLTWorldLocation;
// ********** End ScriptStruct FNLTWorldLocation ***************************************************

// ********** Begin Class UNLTSmartObjectWorldSubsystem ********************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetLocationCount); \
	DECLARE_FUNCTION(execFindBestLocationForAgent); \
	DECLARE_FUNCTION(execFindLocationsByNeed); \
	DECLARE_FUNCTION(execFindLocationsByType); \
	DECLARE_FUNCTION(execFindLocationsByActivity); \
	DECLARE_FUNCTION(execReleaseLocation); \
	DECLARE_FUNCTION(execReserveLocation); \
	DECLARE_FUNCTION(execUnregisterLocation); \
	DECLARE_FUNCTION(execRegisterLocation);


struct Z_Construct_UClass_UNLTSmartObjectWorldSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSmartObjectWorldSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTSmartObjectWorldSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTSmartObjectWorldSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTSmartObjectWorldSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTSmartObjectWorldSubsystem) \
	DECLARE_SERIALIZER(UNLTSmartObjectWorldSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTSmartObjectWorldSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTSmartObjectWorldSubsystem(UNLTSmartObjectWorldSubsystem&&) = delete; \
	UNLTSmartObjectWorldSubsystem(const UNLTSmartObjectWorldSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTSmartObjectWorldSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTSmartObjectWorldSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTSmartObjectWorldSubsystem) \
	NO_API virtual ~UNLTSmartObjectWorldSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_52_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h_55_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTSmartObjectWorldSubsystem;

// ********** End Class UNLTSmartObjectWorldSubsystem **********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
