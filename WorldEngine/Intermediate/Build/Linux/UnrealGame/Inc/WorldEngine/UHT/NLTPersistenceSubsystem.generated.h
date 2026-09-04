// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Persistence/NLTPersistenceSubsystem.h"

#ifdef WORLDENGINE_NLTPersistenceSubsystem_generated_h
#error "NLTPersistenceSubsystem.generated.h already included, missing '#pragma once' in NLTPersistenceSubsystem.h"
#endif
#define WORLDENGINE_NLTPersistenceSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FNLTSavedGame *****************************************************
struct Z_Construct_UScriptStruct_FNLTSavedGame_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSavedGame(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_13_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTSavedGame_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTSavedGame(ETypeConstructPhase::Inner); }


struct FNLTSavedGame;
// ********** End ScriptStruct FNLTSavedGame *******************************************************

// ********** Begin Class UNLTPersistenceSubsystem *************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetAllSaveSlots); \
	DECLARE_FUNCTION(execDeleteSaveGame); \
	DECLARE_FUNCTION(execDoesSaveGameExist); \
	DECLARE_FUNCTION(execLoadGame); \
	DECLARE_FUNCTION(execSaveGame);


struct Z_Construct_UClass_UNLTPersistenceSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTPersistenceSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTPersistenceSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTPersistenceSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTPersistenceSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTPersistenceSubsystem) \
	DECLARE_SERIALIZER(UNLTPersistenceSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTPersistenceSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTPersistenceSubsystem(UNLTPersistenceSubsystem&&) = delete; \
	UNLTPersistenceSubsystem(const UNLTPersistenceSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTPersistenceSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTPersistenceSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTPersistenceSubsystem) \
	NO_API virtual ~UNLTPersistenceSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_34_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h_37_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTPersistenceSubsystem;

// ********** End Class UNLTPersistenceSubsystem ***************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
