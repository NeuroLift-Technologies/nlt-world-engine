// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Scenarios/Demo/NLTDemoScenarioFragments.h"

#ifdef WORLDENGINE_NLTDemoScenarioFragments_generated_h
#error "NLTDemoScenarioFragments.generated.h already included, missing '#pragma once' in NLTDemoScenarioFragments.h"
#endif
#define WORLDENGINE_NLTDemoScenarioFragments_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin ScriptStruct FNLTScenarioNeedsFragment *****************************************
struct Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioFragments_h_17_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment(ETypeConstructPhase::Inner); } \
	typedef FMassFragment Super;


struct FNLTScenarioNeedsFragment;
// ********** End ScriptStruct FNLTScenarioNeedsFragment *******************************************

// ********** Begin ScriptStruct FNLTScenarioConfigFragment ****************************************
struct Z_Construct_UScriptStruct_FNLTScenarioConfigFragment_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioConfigFragment(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioFragments_h_39_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTScenarioConfigFragment_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTScenarioConfigFragment(ETypeConstructPhase::Inner); } \
	typedef FMassFragment Super;


struct FNLTScenarioConfigFragment;
// ********** End ScriptStruct FNLTScenarioConfigFragment ******************************************

// ********** Begin ScriptStruct FNLTScenarioBehaviorFragment **************************************
struct Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioFragments_h_79_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment(ETypeConstructPhase::Inner); } \
	typedef FMassFragment Super;


struct FNLTScenarioBehaviorFragment;
// ********** End ScriptStruct FNLTScenarioBehaviorFragment ****************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioFragments_h

// ********** Begin Enum ENLTScenarioMovementPhase *************************************************
#define FOREACH_ENUM_ENLTSCENARIOMOVEMENTPHASE(op) \
	op(ENLTScenarioMovementPhase::Idle) \
	op(ENLTScenarioMovementPhase::Moving) \
	op(ENLTScenarioMovementPhase::Arrived) 

enum class ENLTScenarioMovementPhase : uint8;
template<> struct TIsUEnumClass<ENLTScenarioMovementPhase> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTScenarioMovementPhase>();
// ********** End Enum ENLTScenarioMovementPhase ***************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
