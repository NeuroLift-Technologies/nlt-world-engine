// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/PostProcessVolumeActor.h"

#ifdef WORLDENGINE_PostProcessVolumeActor_generated_h
#error "PostProcessVolumeActor.generated.h already included, missing '#pragma once' in PostProcessVolumeActor.h"
#endif
#define WORLDENGINE_PostProcessVolumeActor_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class APostProcessVolumeActor **************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execApplySettings);


struct Z_Construct_UClass_APostProcessVolumeActor_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_APostProcessVolumeActor(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_APostProcessVolumeActor_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_APostProcessVolumeActor(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(APostProcessVolumeActor, AVolume, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_APostProcessVolumeActor) \
	DECLARE_SERIALIZER(APostProcessVolumeActor)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	APostProcessVolumeActor(APostProcessVolumeActor&&) = delete; \
	APostProcessVolumeActor(const APostProcessVolumeActor&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APostProcessVolumeActor); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APostProcessVolumeActor); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APostProcessVolumeActor) \
	NO_API virtual ~APostProcessVolumeActor();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_13_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class APostProcessVolumeActor;

// ********** End Class APostProcessVolumeActor ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_PostProcessVolumeActor_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
