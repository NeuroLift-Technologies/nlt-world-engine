// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Agents/NLTTrainingManager.h"

#ifdef WORLDENGINE_NLTTrainingManager_generated_h
#error "NLTTrainingManager.generated.h already included, missing '#pragma once' in NLTTrainingManager.h"
#endif
#define WORLDENGINE_NLTTrainingManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANLTTrainingManager ******************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetPairedAvatarId); \
	DECLARE_FUNCTION(execSetPairMapping);


struct Z_Construct_UClass_ANLTTrainingManager_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTTrainingManager(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ANLTTrainingManager_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_ANLTTrainingManager(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ANLTTrainingManager, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_ANLTTrainingManager) \
	DECLARE_SERIALIZER(ANLTTrainingManager)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANLTTrainingManager(ANLTTrainingManager&&) = delete; \
	ANLTTrainingManager(const ANLTTrainingManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANLTTrainingManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANLTTrainingManager); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANLTTrainingManager) \
	NO_API virtual ~ANLTTrainingManager();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_17_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANLTTrainingManager;

// ********** End Class ANLTTrainingManager ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
