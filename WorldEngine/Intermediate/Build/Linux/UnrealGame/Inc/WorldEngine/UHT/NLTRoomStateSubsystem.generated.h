// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/NLTRoomStateSubsystem.h"

#ifdef WORLDENGINE_NLTRoomStateSubsystem_generated_h
#error "NLTRoomStateSubsystem.generated.h already included, missing '#pragma once' in NLTRoomStateSubsystem.h"
#endif
#define WORLDENGINE_NLTRoomStateSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FLinearColor;
struct FNLRoomState;

// ********** Begin ScriptStruct FNLRoomState ******************************************************
struct Z_Construct_UScriptStruct_FNLRoomState_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLRoomState(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_17_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLRoomState_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLRoomState(ETypeConstructPhase::Inner); }


struct FNLRoomState;
// ********** End ScriptStruct FNLRoomState ********************************************************

// ********** Begin Class UNLTRoomStateSubsystem ***************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetRoomCount); \
	DECLARE_FUNCTION(execDeserializeRoomStates); \
	DECLARE_FUNCTION(execSerializeRoomStates); \
	DECLARE_FUNCTION(execSetRoomFogDensity); \
	DECLARE_FUNCTION(execSetRoomAmbientColor); \
	DECLARE_FUNCTION(execSetRoomWeather); \
	DECLARE_FUNCTION(execSetRoomActivity); \
	DECLARE_FUNCTION(execSetRoomTemperature); \
	DECLARE_FUNCTION(execSetRoomNoise); \
	DECLARE_FUNCTION(execSetRoomLighting); \
	DECLARE_FUNCTION(execRestoreAllRoomStates); \
	DECLARE_FUNCTION(execGetAllRoomStates); \
	DECLARE_FUNCTION(execGetAllRoomIds); \
	DECLARE_FUNCTION(execGetRoomState); \
	DECLARE_FUNCTION(execUpdateRoomState); \
	DECLARE_FUNCTION(execUnregisterRoom); \
	DECLARE_FUNCTION(execRegisterRoom);


struct Z_Construct_UClass_UNLTRoomStateSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTRoomStateSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTRoomStateSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTRoomStateSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTRoomStateSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTRoomStateSubsystem) \
	DECLARE_SERIALIZER(UNLTRoomStateSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTRoomStateSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTRoomStateSubsystem(UNLTRoomStateSubsystem&&) = delete; \
	UNLTRoomStateSubsystem(const UNLTRoomStateSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTRoomStateSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTRoomStateSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTRoomStateSubsystem) \
	NO_API virtual ~UNLTRoomStateSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_63_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h_66_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTRoomStateSubsystem;

// ********** End Class UNLTRoomStateSubsystem *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
