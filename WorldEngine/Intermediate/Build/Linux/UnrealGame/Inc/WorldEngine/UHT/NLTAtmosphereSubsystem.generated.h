// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/NLTAtmosphereSubsystem.h"

#ifdef WORLDENGINE_NLTAtmosphereSubsystem_generated_h
#error "NLTAtmosphereSubsystem.generated.h already included, missing '#pragma once' in NLTAtmosphereSubsystem.h"
#endif
#define WORLDENGINE_NLTAtmosphereSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ENLTTimeOfDayPhase : uint8;

// ********** Begin Class UNLTAtmosphereSubsystem **************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execRefreshAtmosphere); \
	DECLARE_FUNCTION(execGetSunDirection); \
	DECLARE_FUNCTION(execGetDaylightFactor); \
	DECLARE_FUNCTION(execAreStarsVisible); \
	DECLARE_FUNCTION(execGetTimeOfDayPhase); \
	DECLARE_FUNCTION(execAdvanceTimeOfDay); \
	DECLARE_FUNCTION(execSetTimeOfDayHours); \
	DECLARE_FUNCTION(execGetTimeOfDayHours);


struct Z_Construct_UClass_UNLTAtmosphereSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAtmosphereSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTAtmosphereSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTAtmosphereSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTAtmosphereSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTAtmosphereSubsystem) \
	DECLARE_SERIALIZER(UNLTAtmosphereSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTAtmosphereSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTAtmosphereSubsystem(UNLTAtmosphereSubsystem&&) = delete; \
	UNLTAtmosphereSubsystem(const UNLTAtmosphereSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTAtmosphereSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTAtmosphereSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTAtmosphereSubsystem) \
	NO_API virtual ~UNLTAtmosphereSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_26_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTAtmosphereSubsystem;

// ********** End Class UNLTAtmosphereSubsystem ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h

// ********** Begin Enum ENLTTimeOfDayPhase ********************************************************
#define FOREACH_ENUM_ENLTTIMEOFDAYPHASE(op) \
	op(ENLTTimeOfDayPhase::Dawn) \
	op(ENLTTimeOfDayPhase::Morning) \
	op(ENLTTimeOfDayPhase::Midday) \
	op(ENLTTimeOfDayPhase::Afternoon) \
	op(ENLTTimeOfDayPhase::Sunset) \
	op(ENLTTimeOfDayPhase::Dusk) \
	op(ENLTTimeOfDayPhase::Night) 

enum class ENLTTimeOfDayPhase : uint8;
template<> struct TIsUEnumClass<ENLTTimeOfDayPhase> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTTimeOfDayPhase>();
// ********** End Enum ENLTTimeOfDayPhase **********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
