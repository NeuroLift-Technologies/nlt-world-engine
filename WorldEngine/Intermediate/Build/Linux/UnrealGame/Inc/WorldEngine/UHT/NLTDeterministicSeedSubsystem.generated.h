// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Simulation/NLTDeterministicSeedSubsystem.h"

#ifdef WORLDENGINE_NLTDeterministicSeedSubsystem_generated_h
#error "NLTDeterministicSeedSubsystem.generated.h already included, missing '#pragma once' in NLTDeterministicSeedSubsystem.h"
#endif
#define WORLDENGINE_NLTDeterministicSeedSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class ENLTSeedCategory : uint8;
struct FNLTRandomStream;

// ********** Begin Class UNLTDeterministicSeedSubsystem *******************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDeserializeSeedState); \
	DECLARE_FUNCTION(execSerializeSeedState); \
	DECLARE_FUNCTION(execGetDeterministicIndex); \
	DECLARE_FUNCTION(execGetDeterministicBool); \
	DECLARE_FUNCTION(execGetDeterministicInt); \
	DECLARE_FUNCTION(execGetDeterministicRange); \
	DECLARE_FUNCTION(execGetDeterministicFloat); \
	DECLARE_FUNCTION(execResetStream); \
	DECLARE_FUNCTION(execResetAllStreams); \
	DECLARE_FUNCTION(execGetCategoryRNGMutable); \
	DECLARE_FUNCTION(execGetCategoryRNG); \
	DECLARE_FUNCTION(execGetCategorySeed); \
	DECLARE_FUNCTION(execGetMasterSeed); \
	DECLARE_FUNCTION(execSetMasterSeed);


struct Z_Construct_UClass_UNLTDeterministicSeedSubsystem_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTDeterministicSeedSubsystem(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UNLTDeterministicSeedSubsystem_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UNLTDeterministicSeedSubsystem(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UNLTDeterministicSeedSubsystem, UWorldSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UNLTDeterministicSeedSubsystem) \
	DECLARE_SERIALIZER(UNLTDeterministicSeedSubsystem)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLTDeterministicSeedSubsystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UNLTDeterministicSeedSubsystem(UNLTDeterministicSeedSubsystem&&) = delete; \
	UNLTDeterministicSeedSubsystem(const UNLTDeterministicSeedSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLTDeterministicSeedSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLTDeterministicSeedSubsystem); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLTDeterministicSeedSubsystem) \
	NO_API virtual ~UNLTDeterministicSeedSubsystem();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_29_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UNLTDeterministicSeedSubsystem;

// ********** End Class UNLTDeterministicSeedSubsystem *********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h

// ********** Begin Enum ENLTSeedCategory **********************************************************
#define FOREACH_ENUM_ENLTSEEDCATEGORY(op) \
	op(ENLTSeedCategory::Dress) \
	op(ENLTSeedCategory::VFX) \
	op(ENLTSeedCategory::Ambient) \
	op(ENLTSeedCategory::Weather) \
	op(ENLTSeedCategory::Lighting) \
	op(ENLTSeedCategory::Props) \
	op(ENLTSeedCategory::Flora) 

enum class ENLTSeedCategory : uint8;
template<> struct TIsUEnumClass<ENLTSeedCategory> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTSeedCategory>();
// ********** End Enum ENLTSeedCategory ************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
