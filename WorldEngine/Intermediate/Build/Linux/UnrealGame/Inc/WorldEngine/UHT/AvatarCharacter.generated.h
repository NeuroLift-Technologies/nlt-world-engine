// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Agents/AvatarCharacter.h"

#ifdef WORLDENGINE_AvatarCharacter_generated_h
#error "AvatarCharacter.generated.h already included, missing '#pragma once' in AvatarCharacter.h"
#endif
#define WORLDENGINE_AvatarCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AAvatarCharacter *********************************************************
struct Z_Construct_UClass_AAvatarCharacter_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_AAvatarCharacter(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h_34_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_AAvatarCharacter_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_AAvatarCharacter(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(AAvatarCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_AAvatarCharacter) \
	DECLARE_SERIALIZER(AAvatarCharacter)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h_34_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AAvatarCharacter(AAvatarCharacter&&) = delete; \
	AAvatarCharacter(const AAvatarCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AAvatarCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AAvatarCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AAvatarCharacter) \
	NO_API virtual ~AAvatarCharacter();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h_31_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h_34_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AAvatarCharacter;

// ********** End Class AAvatarCharacter ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarCharacter_h

// ********** Begin Enum ECharacterVisualState *****************************************************
#define FOREACH_ENUM_ECHARACTERVISUALSTATE(op) \
	op(ECharacterVisualState::Normal) \
	op(ECharacterVisualState::Focused) \
	op(ECharacterVisualState::Stressed) \
	op(ECharacterVisualState::Interacting) 

enum class ECharacterVisualState : uint8;
template<> struct TIsUEnumClass<ECharacterVisualState> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ECharacterVisualState>();
// ********** End Enum ECharacterVisualState *******************************************************

// ********** Begin Enum ECharacterTeam ************************************************************
#define FOREACH_ENUM_ECHARACTERTEAM(op) \
	op(ECharacterTeam::Neutral) \
	op(ECharacterTeam::TeamA) \
	op(ECharacterTeam::TeamB) \
	op(ECharacterTeam::TeamC) 

enum class ECharacterTeam : uint8;
template<> struct TIsUEnumClass<ECharacterTeam> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ECharacterTeam>();
// ********** End Enum ECharacterTeam **************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
