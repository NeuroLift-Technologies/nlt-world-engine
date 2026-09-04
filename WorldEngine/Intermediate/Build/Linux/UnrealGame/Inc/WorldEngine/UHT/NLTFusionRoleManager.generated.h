// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Roles/NLTFusionRoleManager.h"

#ifdef WORLDENGINE_NLTFusionRoleManager_generated_h
#error "NLTFusionRoleManager.generated.h already included, missing '#pragma once' in NLTFusionRoleManager.h"
#endif
#define WORLDENGINE_NLTFusionRoleManager_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLTFusionPair;

// ********** Begin ScriptStruct FNLTFusionPair ****************************************************
struct Z_Construct_UScriptStruct_FNLTFusionPair_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTFusionPair(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_23_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTFusionPair_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTFusionPair(ETypeConstructPhase::Inner); }


struct FNLTFusionPair;
// ********** End ScriptStruct FNLTFusionPair ******************************************************

// ********** Begin ScriptStruct FNLTAdvocate ******************************************************
struct Z_Construct_UScriptStruct_FNLTAdvocate_Statics;
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAdvocate(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_50_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FNLTAdvocate_Statics; \
	UE_NODEBUG static UScriptStruct* StaticStruct() { return Z_Construct_UScriptStruct_FNLTAdvocate(ETypeConstructPhase::Inner); }


struct FNLTAdvocate;
// ********** End ScriptStruct FNLTAdvocate ********************************************************

// ********** Begin Class UNLTFusionRoleManager ****************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetAdvocateCount); \
	DECLARE_FUNCTION(execGetPairCount); \
	DECLARE_FUNCTION(execTick); \
	DECLARE_FUNCTION(execAssignPairToAdvocate); \
	DECLARE_FUNCTION(execCreateAdvocate); \
	DECLARE_FUNCTION(execGetPair); \
	DECLARE_FUNCTION(execDestroyPair); \
	DECLARE_FUNCTION(execCreatePair);


struct Z_Construct_UClass_UNLTFusionRoleManager_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTFusionRoleManager(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTFusionRoleManager_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTFusionRoleManager(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTFusionRoleManager, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTFusionRoleManager) \
	DECLARE_SERIALIZER(UNLTFusionRoleManager)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTFusionRoleManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTFusionRoleManager(UNLTFusionRoleManager&&) = delete; \
	UNLTFusionRoleManager(const UNLTFusionRoleManager&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTFusionRoleManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTFusionRoleManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTFusionRoleManager) \
	NO_API virtual ~UNLTFusionRoleManager();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_65_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h_68_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTFusionRoleManager;

// ********** End Class UNLTFusionRoleManager ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h

// ********** Begin Enum ENLTFusionRoleState *******************************************************
#define FOREACH_ENUM_ENLTFUSIONROLESTATE(op) \
	op(ENLTFusionRoleState::Inactive) \
	op(ENLTFusionRoleState::Active) \
	op(ENLTFusionRoleState::Coaching) \
	op(ENLTFusionRoleState::Monitoring) \
	op(ENLTFusionRoleState::Fused) 

enum class ENLTFusionRoleState : uint8;
template<> struct TIsUEnumClass<ENLTFusionRoleState> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTFusionRoleState>();
// ********** End Enum ENLTFusionRoleState *********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
