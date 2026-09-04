// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Scenarios/UScenarioDataAsset.h"

#ifdef WORLDENGINE_UScenarioDataAsset_generated_h
#error "UScenarioDataAsset.generated.h already included, missing '#pragma once' in UScenarioDataAsset.h"
#endif
#define WORLDENGINE_UScenarioDataAsset_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "Templates/IsUEnumClass.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UScenarioDataAsset *******************************************************
struct Z_Construct_UClass_UScenarioDataAsset_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h_35_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UScenarioDataAsset_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UScenarioDataAsset, UPrimaryDataAsset, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UScenarioDataAsset) \
	DECLARE_SERIALIZER(UScenarioDataAsset)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h_35_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UScenarioDataAsset(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UScenarioDataAsset(UScenarioDataAsset&&) = delete; \
	UScenarioDataAsset(const UScenarioDataAsset&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UScenarioDataAsset); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UScenarioDataAsset); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UScenarioDataAsset) \
	NO_API virtual ~UScenarioDataAsset();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h_32_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h_35_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h_35_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h_35_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UScenarioDataAsset;

// ********** End Class UScenarioDataAsset *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h

// ********** Begin Enum EScenarioCategory *********************************************************
#define FOREACH_ENUM_ESCENARIOCATEGORY(op) \
	op(EScenarioCategory::Workplace) \
	op(EScenarioCategory::Personal) \
	op(EScenarioCategory::Social) \
	op(EScenarioCategory::Academic) 

enum class EScenarioCategory : uint8;
template<> struct TIsUEnumClass<EScenarioCategory> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EScenarioCategory>();
// ********** End Enum EScenarioCategory ***********************************************************

// ********** Begin Enum EScenarioComplexity *******************************************************
#define FOREACH_ENUM_ESCENARIOCOMPLEXITY(op) \
	op(EScenarioComplexity::Low) \
	op(EScenarioComplexity::Medium) \
	op(EScenarioComplexity::High) 

enum class EScenarioComplexity : uint8;
template<> struct TIsUEnumClass<EScenarioComplexity> { enum { Value = true }; };
template<> UE_NODEBUG WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EScenarioComplexity>();
// ********** End Enum EScenarioComplexity *********************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
