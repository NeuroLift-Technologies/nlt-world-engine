// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Audio/SoundscapeDataAsset.h"

#ifdef WORLDENGINE_SoundscapeDataAsset_generated_h
#error "SoundscapeDataAsset.generated.h already included, missing '#pragma once' in SoundscapeDataAsset.h"
#endif
#define WORLDENGINE_SoundscapeDataAsset_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FSoundscapeBedLayer ***********************************************
struct Z_Construct_UScriptStruct_FSoundscapeBedLayer_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FSoundscapeBedLayer(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_17_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FSoundscapeBedLayer_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FSoundscapeBedLayer(ETypeConstructPhase::Inner); }


struct FSoundscapeBedLayer;
// ********** End ScriptStruct FSoundscapeBedLayer *************************************************

// ********** Begin Class USoundscapeDataAsset *****************************************************
struct Z_Construct_UClass_USoundscapeDataAsset_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_USoundscapeDataAsset(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_56_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_USoundscapeDataAsset_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_USoundscapeDataAsset(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(USoundscapeDataAsset, UPrimaryDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_USoundscapeDataAsset) \
	DECLARE_SERIALIZER(USoundscapeDataAsset)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_56_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USoundscapeDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	USoundscapeDataAsset(USoundscapeDataAsset&&) = delete; \
	USoundscapeDataAsset(const USoundscapeDataAsset&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USoundscapeDataAsset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USoundscapeDataAsset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USoundscapeDataAsset) \
	NO_API virtual ~USoundscapeDataAsset();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_53_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_56_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_56_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h_56_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class USoundscapeDataAsset;

// ********** End Class USoundscapeDataAsset *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
