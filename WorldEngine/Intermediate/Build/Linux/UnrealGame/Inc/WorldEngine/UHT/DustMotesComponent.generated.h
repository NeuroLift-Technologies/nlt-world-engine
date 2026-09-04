// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/DustMotesComponent.h"

#ifdef WORLDENGINE_DustMotesComponent_generated_h
#error "DustMotesComponent.generated.h already included, missing '#pragma once' in DustMotesComponent.h"
#endif
#define WORLDENGINE_DustMotesComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UParticleSystem;
struct FLinearColor;

// ********** Begin Class UDustMotesComponent ******************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execSetColorTint); \
	DECLARE_FUNCTION(execSetDriftSpeed); \
	DECLARE_FUNCTION(execGetDensity); \
	DECLARE_FUNCTION(execGetVisibility); \
	DECLARE_FUNCTION(execSetParticleSystem); \
	DECLARE_FUNCTION(execSetDensity); \
	DECLARE_FUNCTION(execSetVisibility);


struct Z_Construct_UClass_UDustMotesComponent_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UDustMotesComponent(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UDustMotesComponent_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UDustMotesComponent(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UDustMotesComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UDustMotesComponent) \
	DECLARE_SERIALIZER(UDustMotesComponent)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UDustMotesComponent(UDustMotesComponent&&) = delete; \
	UDustMotesComponent(const UDustMotesComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UDustMotesComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UDustMotesComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UDustMotesComponent) \
	NO_API virtual ~UDustMotesComponent();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_14_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UDustMotesComponent;

// ********** End Class UDustMotesComponent ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_DustMotesComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
