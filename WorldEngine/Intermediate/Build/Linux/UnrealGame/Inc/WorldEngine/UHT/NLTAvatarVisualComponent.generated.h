// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Agents/NLTAvatarVisualComponent.h"

#ifdef WORLDENGINE_NLTAvatarVisualComponent_generated_h
#error "NLTAvatarVisualComponent.generated.h already included, missing '#pragma once' in NLTAvatarVisualComponent.h"
#endif
#define WORLDENGINE_NLTAvatarVisualComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLinearColor;

// ********** Begin Class UNLTAvatarVisualComponent ************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetEmissiveGlow); \
	DECLARE_FUNCTION(execSetStatusRingColor); \
	DECLARE_FUNCTION(execUpdateFromCognitiveState);


struct Z_Construct_UClass_UNLTAvatarVisualComponent_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAvatarVisualComponent(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTAvatarVisualComponent_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTAvatarVisualComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTAvatarVisualComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTAvatarVisualComponent) \
	DECLARE_SERIALIZER(UNLTAvatarVisualComponent)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTAvatarVisualComponent(UNLTAvatarVisualComponent&&) = delete; \
	UNLTAvatarVisualComponent(const UNLTAvatarVisualComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTAvatarVisualComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTAvatarVisualComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNLTAvatarVisualComponent) \
	NO_API virtual ~UNLTAvatarVisualComponent();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_15_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h_18_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTAvatarVisualComponent;

// ********** End Class UNLTAvatarVisualComponent **************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAvatarVisualComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
