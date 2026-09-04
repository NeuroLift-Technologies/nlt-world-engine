// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Scenarios/UScenarioLibrary.h"

#ifdef WORLDENGINE_UScenarioLibrary_generated_h
#error "UScenarioLibrary.generated.h already included, missing '#pragma once' in UScenarioLibrary.h"
#endif
#define WORLDENGINE_UScenarioLibrary_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UScenarioDataAsset;
enum class EScenarioCategory : uint8;

// ********** Begin Class UScenarioLibrary *********************************************************
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execLoadAllScenariosFromDisk); \
	DECLARE_FUNCTION(execGetScenariosByCategory); \
	DECLARE_FUNCTION(execGetScenarioById); \
	DECLARE_FUNCTION(execGetAllScenarios);


struct Z_Construct_UClass_UScenarioLibrary_Statics;
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioLibrary(ETypeConstructPhase);

#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_UScenarioLibrary_Statics; \
	friend WORLDENGINE_API UClass* ::Z_Construct_UClass_UScenarioLibrary(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(UScenarioLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/WorldEngine"), Z_Construct_UClass_UScenarioLibrary) \
	DECLARE_SERIALIZER(UScenarioLibrary)


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UScenarioLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UScenarioLibrary(UScenarioLibrary&&) = delete; \
	UScenarioLibrary(const UScenarioLibrary&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UScenarioLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UScenarioLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UScenarioLibrary) \
	NO_API virtual ~UScenarioLibrary();


#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_12_PROLOG
#define FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_INCLASS_NO_PURE_DECLS \
	FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UScenarioLibrary;

// ********** End Class UScenarioLibrary ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
