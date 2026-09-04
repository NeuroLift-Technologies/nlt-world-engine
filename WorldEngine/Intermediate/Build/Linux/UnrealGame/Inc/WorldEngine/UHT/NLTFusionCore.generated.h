// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Core/NLTFusionCore.h"

#ifdef WORLDENGINE_NLTFusionCore_generated_h
#error "NLTFusionCore.generated.h already included, missing '#pragma once' in NLTFusionCore.h"
#endif
#define WORLDENGINE_NLTFusionCore_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "Templates/NoDestroy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTFusionCore_h

// ********** Begin Enum ENLTAgentRole *************************************************************
#define FOREACH_ENUM_ENLTAGENTROLE(op) \
	op(ENLTAgentRole::None) \
	op(ENLTAgentRole::Avatar) \
	op(ENLTAgentRole::Aide) \
	op(ENLTAgentRole::Advocate) 

enum class ENLTAgentRole : uint8;
template<> struct TIsUEnumClass<ENLTAgentRole> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTAgentRole>();
// ********** End Enum ENLTAgentRole ***************************************************************

// ********** Begin Enum ESimulationMode ***********************************************************
#define FOREACH_ENUM_ESIMULATIONMODE(op) \
	op(ESimulationMode::Realtime) \
	op(ESimulationMode::Paused) \
	op(ESimulationMode::FastForward) \
	op(ESimulationMode::SlowMotion) \
	op(ESimulationMode::Headless) \
	op(ESimulationMode::Replay) \
	op(ESimulationMode::DeterministicTest) 

enum class ESimulationMode : uint8;
template<> struct TIsUEnumClass<ESimulationMode> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ESimulationMode>();
// ********** End Enum ESimulationMode *************************************************************

// ********** Begin Enum ENLTAgentIntent ***********************************************************
#define FOREACH_ENUM_ENLTAGENTINTENT(op) \
	op(ENLTAgentIntent::None) \
	op(ENLTAgentIntent::Idle) \
	op(ENLTAgentIntent::FindQuietPlace) \
	op(ENLTAgentIntent::Work) \
	op(ENLTAgentIntent::Socialize) \
	op(ENLTAgentIntent::Rest) \
	op(ENLTAgentIntent::Study) \
	op(ENLTAgentIntent::MoveToLocation) \
	op(ENLTAgentIntent::Interact) \
	op(ENLTAgentIntent::Coached) \
	op(ENLTAgentIntent::Overwhelmed) \
	op(ENLTAgentIntent::Drifting) \
	op(ENLTAgentIntent::Hyperfocus) 

enum class ENLTAgentIntent : uint8;
template<> struct TIsUEnumClass<ENLTAgentIntent> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTAgentIntent>();
// ********** End Enum ENLTAgentIntent *************************************************************

// ********** Begin Enum ENLTAgentNeed *************************************************************
#define FOREACH_ENUM_ENLTAGENTNEED(op) \
	op(ENLTAgentNeed::None) \
	op(ENLTAgentNeed::Quiet) \
	op(ENLTAgentNeed::Rest) \
	op(ENLTAgentNeed::Social) \
	op(ENLTAgentNeed::Stimulation) \
	op(ENLTAgentNeed::Food) \
	op(ENLTAgentNeed::Movement) \
	op(ENLTAgentNeed::Privacy) 

enum class ENLTAgentNeed : uint8;
template<> struct TIsUEnumClass<ENLTAgentNeed> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTAgentNeed>();
// ********** End Enum ENLTAgentNeed ***************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
