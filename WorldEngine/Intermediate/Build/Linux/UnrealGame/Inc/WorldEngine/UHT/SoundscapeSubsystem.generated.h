// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Audio/SoundscapeSubsystem.h"

#ifdef WORLDENGINE_SoundscapeSubsystem_generated_h
#error "SoundscapeSubsystem.generated.h already included, missing '#pragma once' in SoundscapeSubsystem.h"
#endif
#define WORLDENGINE_SoundscapeSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USoundscapeDataAsset;

// ********** Begin Class UNLTSoundscapeSubsystem **************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetOrigin); \
	DECLARE_FUNCTION(execGetStressLevel); \
	DECLARE_FUNCTION(execSetStressLevel); \
	DECLARE_FUNCTION(execIsActive); \
	DECLARE_FUNCTION(execUnmuteAll); \
	DECLARE_FUNCTION(execMuteAll); \
	DECLARE_FUNCTION(execDeactivate); \
	DECLARE_FUNCTION(execActivate); \
	DECLARE_FUNCTION(execSetSoundscapeAsset);


struct Z_Construct_UClass_UNLTSoundscapeSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSoundscapeSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTSoundscapeSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTSoundscapeSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTSoundscapeSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTSoundscapeSubsystem) \
	DECLARE_SERIALIZER(UNLTSoundscapeSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTSoundscapeSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTSoundscapeSubsystem(UNLTSoundscapeSubsystem&&) = delete; \
	UNLTSoundscapeSubsystem(const UNLTSoundscapeSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTSoundscapeSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTSoundscapeSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTSoundscapeSubsystem) \
	NO_API virtual ~UNLTSoundscapeSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_16_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTSoundscapeSubsystem;

// ********** End Class UNLTSoundscapeSubsystem ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
