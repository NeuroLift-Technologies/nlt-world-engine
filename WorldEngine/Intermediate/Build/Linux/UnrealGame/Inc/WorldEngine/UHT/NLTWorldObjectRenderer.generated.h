// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "World/NLTWorldObjectRenderer.h"

#ifdef WORLDENGINE_NLTWorldObjectRenderer_generated_h
#error "NLTWorldObjectRenderer.generated.h already included, missing '#pragma once' in NLTWorldObjectRenderer.h"
#endif
#define WORLDENGINE_NLTWorldObjectRenderer_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTWorldGenerationResult;

// ********** Begin Class ANLTWorldObjectRenderer **************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execClearWorld); \
	DECLARE_FUNCTION(execBuildFromWorld);


struct Z_Construct_UClass_ANLTWorldObjectRenderer_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTWorldObjectRenderer(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ANLTWorldObjectRenderer_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_ANLTWorldObjectRenderer(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ANLTWorldObjectRenderer, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_ANLTWorldObjectRenderer) \
	DECLARE_SERIALIZER(ANLTWorldObjectRenderer)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANLTWorldObjectRenderer(ANLTWorldObjectRenderer&&) = delete; \
	ANLTWorldObjectRenderer(const ANLTWorldObjectRenderer&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANLTWorldObjectRenderer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANLTWorldObjectRenderer); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANLTWorldObjectRenderer) \
	NO_API virtual ~ANLTWorldObjectRenderer();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_16_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANLTWorldObjectRenderer;

// ********** End Class ANLTWorldObjectRenderer ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTWorldObjectRenderer_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
