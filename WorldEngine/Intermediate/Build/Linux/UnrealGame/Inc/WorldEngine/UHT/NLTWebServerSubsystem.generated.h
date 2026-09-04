// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NLTWebServerSubsystem.h"

#ifdef WORLDENGINE_NLTWebServerSubsystem_generated_h
#error "NLTWebServerSubsystem.generated.h already included, missing '#pragma once' in NLTWebServerSubsystem.h"
#endif
#define WORLDENGINE_NLTWebServerSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UNLTWebServerSubsystem ***************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetPort); \
	DECLARE_FUNCTION(execIsRunning); \
	DECLARE_FUNCTION(execStopServer); \
	DECLARE_FUNCTION(execStartServer);


struct Z_Construct_UClass_UNLTWebServerSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTWebServerSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTWebServerSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTWebServerSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTWebServerSubsystem, UEngineSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTWebServerSubsystem) \
	DECLARE_SERIALIZER(UNLTWebServerSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTWebServerSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTWebServerSubsystem(UNLTWebServerSubsystem&&) = delete; \
	UNLTWebServerSubsystem(const UNLTWebServerSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTWebServerSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTWebServerSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTWebServerSubsystem) \
	NO_API virtual ~UNLTWebServerSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_18_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTWebServerSubsystem;

// ********** End Class UNLTWebServerSubsystem *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_NLTWebServerSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
