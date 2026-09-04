// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NLTEventBus.h"

#ifdef WORLDENGINE_NLTEventBus_generated_h
#error "NLTEventBus.generated.h already included, missing '#pragma once' in NLTEventBus.h"
#endif
#define WORLDENGINE_NLTEventBus_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ENLTSimulationEventType : uint8;
struct FNLTSimulationEvent;

// ********** Begin ScriptStruct FNLTSimulationEvent ***********************************************
struct Z_Construct_UScriptStruct_FNLTSimulationEvent_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSimulationEvent(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_48_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTSimulationEvent_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTSimulationEvent(ETypeConstructPhase::Inner); }


struct FNLTSimulationEvent;
// ********** End ScriptStruct FNLTSimulationEvent *************************************************

// ********** Begin Class UNLTEventBus *************************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetTotalEventCount); \
	DECLARE_FUNCTION(execGetEventsByType); \
	DECLARE_FUNCTION(execGetRecentEvents); \
	DECLARE_FUNCTION(execRaiseEnvironmentEvent); \
	DECLARE_FUNCTION(execRaiseSimpleEvent); \
	DECLARE_FUNCTION(execRaiseEvent);


struct Z_Construct_UClass_UNLTEventBus_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEventBus(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTEventBus_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTEventBus(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTEventBus, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTEventBus) \
	DECLARE_SERIALIZER(UNLTEventBus)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTEventBus(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTEventBus(UNLTEventBus&&) = delete; \
	UNLTEventBus(const UNLTEventBus&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTEventBus); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTEventBus); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTEventBus) \
	NO_API virtual ~UNLTEventBus();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_71_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h_74_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTEventBus;

// ********** End Class UNLTEventBus ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h

// ********** Begin Enum ENLTSimulationEventType ***************************************************
#define FOREACH_ENUM_ENLTSIMULATIONEVENTTYPE(op) \
	op(ENLTSimulationEventType::None) \
	op(ENLTSimulationEventType::Tick) \
	op(ENLTSimulationEventType::AgentCreated) \
	op(ENLTSimulationEventType::AgentDestroyed) \
	op(ENLTSimulationEventType::AgentSpawned) \
	op(ENLTSimulationEventType::AgentDespawned) \
	op(ENLTSimulationEventType::AgentMoved) \
	op(ENLTSimulationEventType::NeedChanged) \
	op(ENLTSimulationEventType::IntentChanged) \
	op(ENLTSimulationEventType::EmotionalShift) \
	op(ENLTSimulationEventType::FusionStart) \
	op(ENLTSimulationEventType::FusionComplete) \
	op(ENLTSimulationEventType::FusionFail) \
	op(ENLTSimulationEventType::StressSpike) \
	op(ENLTSimulationEventType::BurnoutDetected) \
	op(ENLTSimulationEventType::Breakthrough) \
	op(ENLTSimulationEventType::Distraction) \
	op(ENLTSimulationEventType::SocialInteraction) \
	op(ENLTSimulationEventType::TaskComplete) \
	op(ENLTSimulationEventType::SimulationReset) \
	op(ENLTSimulationEventType::ModeChanged) \
	op(ENLTSimulationEventType::EnvWeatherChanged) \
	op(ENLTSimulationEventType::EnvLightingChanged) \
	op(ENLTSimulationEventType::EnvTimeOfDayChanged) \
	op(ENLTSimulationEventType::EnvRoomStateChanged) \
	op(ENLTSimulationEventType::EnvAmbientSound) \
	op(ENLTSimulationEventType::EnvParticleEffect) \
	op(ENLTSimulationEventType::EnvFogChanged) \
	op(ENLTSimulationEventType::EnvWindChanged) 

enum class ENLTSimulationEventType : uint8;
template<> struct TIsUEnumClass<ENLTSimulationEventType> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTSimulationEventType>();
// ********** End Enum ENLTSimulationEventType *****************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
