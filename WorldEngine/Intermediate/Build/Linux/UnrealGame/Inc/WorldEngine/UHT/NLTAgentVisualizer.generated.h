// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NLTAgentVisualizer.h"

#ifdef WORLDENGINE_NLTAgentVisualizer_generated_h
#error "NLTAgentVisualizer.generated.h already included, missing '#pragma once' in NLTAgentVisualizer.h"
#endif
#define WORLDENGINE_NLTAgentVisualizer_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ANLTAgentVisualizer ******************************************************
struct Z_Construct_UClass_ANLTAgentVisualizer_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTAgentVisualizer(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h_38_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ANLTAgentVisualizer_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_ANLTAgentVisualizer(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ANLTAgentVisualizer, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_ANLTAgentVisualizer) \
	DECLARE_SERIALIZER(ANLTAgentVisualizer)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h_38_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ANLTAgentVisualizer(ANLTAgentVisualizer&&) = delete; \
	ANLTAgentVisualizer(const ANLTAgentVisualizer&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANLTAgentVisualizer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANLTAgentVisualizer); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ANLTAgentVisualizer) \
	NO_API virtual ~ANLTAgentVisualizer();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h_35_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h_38_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h_38_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h_38_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ANLTAgentVisualizer;

// ********** End Class ANLTAgentVisualizer ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_NLTAgentVisualizer_h

// ********** Begin Enum EMassAgentVisualState *****************************************************
#define FOREACH_ENUM_EMASSAGENTVISUALSTATE(op) \
	op(EMassAgentVisualState::Normal) \
	op(EMassAgentVisualState::Focused) \
	op(EMassAgentVisualState::Stressed) \
	op(EMassAgentVisualState::Interacting) 

enum class EMassAgentVisualState : uint8;
template<> struct TIsUEnumClass<EMassAgentVisualState> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMassAgentVisualState>();
// ********** End Enum EMassAgentVisualState *******************************************************

// ********** Begin Enum EMassAgentTeam ************************************************************
#define FOREACH_ENUM_EMASSAGENTTEAM(op) \
	op(EMassAgentTeam::Neutral) \
	op(EMassAgentTeam::TeamA) \
	op(EMassAgentTeam::TeamB) \
	op(EMassAgentTeam::TeamC) 

enum class EMassAgentTeam : uint8;
template<> struct TIsUEnumClass<EMassAgentTeam> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMassAgentTeam>();
// ********** End Enum EMassAgentTeam **************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
