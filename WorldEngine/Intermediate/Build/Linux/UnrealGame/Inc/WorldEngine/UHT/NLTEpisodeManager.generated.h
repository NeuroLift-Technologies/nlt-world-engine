// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Agents/NLTEpisodeManager.h"

#ifdef WORLDENGINE_NLTEpisodeManager_generated_h
#error "NLTEpisodeManager.generated.h already included, missing '#pragma once' in NLTEpisodeManager.h"
#endif
#define WORLDENGINE_NLTEpisodeManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UNLTEpisodeManager *******************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCheckCognitiveCompletion); \
	DECLARE_FUNCTION(execIsEpisodeComplete); \
	DECLARE_FUNCTION(execResetEpisode); \
	DECLARE_FUNCTION(execEndEpisode); \
	DECLARE_FUNCTION(execStartEpisode);


struct Z_Construct_UClass_UNLTEpisodeManager_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEpisodeManager(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTEpisodeManager_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTEpisodeManager(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTEpisodeManager, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTEpisodeManager) \
	DECLARE_SERIALIZER(UNLTEpisodeManager)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTEpisodeManager(UNLTEpisodeManager&&) = delete; \
	UNLTEpisodeManager(const UNLTEpisodeManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTEpisodeManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTEpisodeManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNLTEpisodeManager) \
	NO_API virtual ~UNLTEpisodeManager();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_8_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTEpisodeManager;

// ********** End Class UNLTEpisodeManager *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTEpisodeManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
