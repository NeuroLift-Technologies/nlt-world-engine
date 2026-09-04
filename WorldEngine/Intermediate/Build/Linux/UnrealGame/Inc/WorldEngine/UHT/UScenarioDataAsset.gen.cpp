// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scenarios/UScenarioDataAsset.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeUScenarioDataAsset() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorld(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_EScenarioCategory(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_EScenarioComplexity(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum EScenarioCategory *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_EScenarioCategory_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EScenarioCategory>()
{
	return Z_Construct_UEnum_WorldEngine_EScenarioCategory(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Academic.DisplayName", "Academic" },
		{ "Academic.Name", "EScenarioCategory::Academic" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scenario category (maps Python scenario definitions to UE DataAssets). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
		{ "Personal.DisplayName", "Personal" },
		{ "Personal.Name", "EScenarioCategory::Personal" },
		{ "Social.DisplayName", "Social" },
		{ "Social.Name", "EScenarioCategory::Social" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scenario category (maps Python scenario definitions to UE DataAssets)." },
#endif
		{ "Workplace.DisplayName", "Workplace" },
		{ "Workplace.Name", "EScenarioCategory::Workplace" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EScenarioCategory::Workplace", (int64)EScenarioCategory::Workplace },
		{ "EScenarioCategory::Personal", (int64)EScenarioCategory::Personal },
		{ "EScenarioCategory::Social", (int64)EScenarioCategory::Social },
		{ "EScenarioCategory::Academic", (int64)EScenarioCategory::Academic },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"EScenarioCategory",
	"EScenarioCategory",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EScenarioCategory;
UEnum* Z_Construct_UEnum_WorldEngine_EScenarioCategory(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EScenarioCategory.OuterSingleton)
		{
			ZRIE_EScenarioCategory.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_EScenarioCategory, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("EScenarioCategory"));
		}
		return ZRIE_EScenarioCategory.OuterSingleton;
	}
	if (!ZRIE_EScenarioCategory.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EScenarioCategory.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EScenarioCategory.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EScenarioCategory ***********************************************************

// ********** Begin Enum EScenarioComplexity *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_EScenarioComplexity_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<EScenarioComplexity>()
{
	return Z_Construct_UEnum_WorldEngine_EScenarioComplexity(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Scenario complexity tier. */" },
#endif
		{ "High.DisplayName", "High" },
		{ "High.Name", "EScenarioComplexity::High" },
		{ "Low.DisplayName", "Low" },
		{ "Low.Name", "EScenarioComplexity::Low" },
		{ "Medium.DisplayName", "Medium" },
		{ "Medium.Name", "EScenarioComplexity::Medium" },
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Scenario complexity tier." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EScenarioComplexity::Low", (int64)EScenarioComplexity::Low },
		{ "EScenarioComplexity::Medium", (int64)EScenarioComplexity::Medium },
		{ "EScenarioComplexity::High", (int64)EScenarioComplexity::High },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"EScenarioComplexity",
	"EScenarioComplexity",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_EScenarioComplexity;
UEnum* Z_Construct_UEnum_WorldEngine_EScenarioComplexity(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_EScenarioComplexity.OuterSingleton)
		{
			ZRIE_EScenarioComplexity.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_EScenarioComplexity, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("EScenarioComplexity"));
		}
		return ZRIE_EScenarioComplexity.OuterSingleton;
	}
	if (!ZRIE_EScenarioComplexity.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_EScenarioComplexity.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_EScenarioComplexity.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum EScenarioComplexity *********************************************************

// ********** Begin Class UScenarioDataAsset *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UScenarioDataAsset_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * PrimaryDataAsset representing a scenario definition for the NLT Fusion world engine.\n * Maps Python scenario neurolift-ai-fusion-org/src/simulation/environment/scenarios.py\n * to an editor-configurable UE 5.8 DataAsset.\n */" },
#endif
		{ "IncludePath", "Scenarios/UScenarioDataAsset.h" },
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "PrimaryDataAsset representing a scenario definition for the NLT Fusion world engine.\nMaps Python scenario neurolift-ai-fusion-org/src/simulation/environment/scenarios.py\nto an editor-configurable UE 5.8 DataAsset." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScenarioId_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unique identifier (e.g. \"workplace_deadline\", \"social_networking\"). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unique identifier (e.g. \"workplace_deadline\", \"social_networking\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Human-readable display name. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Human-readable display name." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Long-form description of the scenario. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
		{ "MultiLine", "TRUE" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Long-form description of the scenario." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Category bucket. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Category bucket." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DurationMinutes_MetaData[] = {
		{ "Category", "Scenario" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Expected duration in minutes. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Expected duration in minutes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Complexity_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Complexity tier. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Complexity tier." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Aversiveness_MetaData[] = {
		{ "Category", "Scenario" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Aversiveness factor (0 = pleasant, 1 = highly aversive). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Aversiveness factor (0 = pleasant, 1 = highly aversive)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CognitiveDemand_MetaData[] = {
		{ "Category", "Scenario" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Cognitive demand factor (0 = minimal, 1 = maximal). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Cognitive demand factor (0 = minimal, 1 = maximal)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseSuccessRate_MetaData[] = {
		{ "Category", "Scenario" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Base probability of successful completion (0-1). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base probability of successful completion (0-1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequiresSustainedFocus_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Whether this scenario requires sustained focus to complete. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Whether this scenario requires sustained focus to complete." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContextParams_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Context parameters (arbitrary key-value metadata). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Context parameters (arbitrary key-value metadata)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LevelReference_MetaData[] = {
		{ "Category", "Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Soft reference to the level/world to load for this scenario. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Soft reference to the level/world to load for this scenario." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UScenarioDataAsset constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ScenarioId;
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FTextPropertyParams NewProp_Description;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DurationMinutes;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Complexity_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Complexity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Aversiveness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CognitiveDemand;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseSuccessRate;
	static void NewProp_bRequiresSustainedFocus_SetBit(void* Obj)
	{
		((UScenarioDataAsset*)Obj)->bRequiresSustainedFocus = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequiresSustainedFocus;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ContextParams_ValueProp;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ContextParams_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ContextParams;
	static const UECodeGen_Private::FSoftObjectPropertyParams NewProp_LevelReference;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UScenarioDataAsset constinit property declarations *************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UScenarioDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UScenarioDataAsset Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ScenarioId = { "ScenarioId", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, ScenarioId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScenarioId_MetaData), NewProp_ScenarioId_MetaData) };
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, Category), Z_Construct_UEnum_WorldEngine_EScenarioCategory, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Category_MetaData), NewProp_Category_MetaData) }; // 433ccdc0e3c8bafbec82407eab2ec539992811ce
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DurationMinutes = { "DurationMinutes", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, DurationMinutes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DurationMinutes_MetaData), NewProp_DurationMinutes_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Complexity_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Complexity = { "Complexity", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, Complexity), Z_Construct_UEnum_WorldEngine_EScenarioComplexity, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Complexity_MetaData), NewProp_Complexity_MetaData) }; // a81fc4fd6007e567f67266033f325a575c0a8a6b
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Aversiveness = { "Aversiveness", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, Aversiveness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Aversiveness_MetaData), NewProp_Aversiveness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CognitiveDemand = { "CognitiveDemand", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, CognitiveDemand), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CognitiveDemand_MetaData), NewProp_CognitiveDemand_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BaseSuccessRate = { "BaseSuccessRate", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, BaseSuccessRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseSuccessRate_MetaData), NewProp_BaseSuccessRate_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRequiresSustainedFocus = { "bRequiresSustainedFocus", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UScenarioDataAsset), &UHT_STATICS::NewProp_bRequiresSustainedFocus_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequiresSustainedFocus_MetaData), NewProp_bRequiresSustainedFocus_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ContextParams_ValueProp = { "ContextParams", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ContextParams_Key_KeyProp = { "ContextParams_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams UHT_STATICS::NewProp_ContextParams = { "ContextParams", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Map, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, ContextParams), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContextParams_MetaData), NewProp_ContextParams_MetaData) };
const UECodeGen_Private::FSoftObjectPropertyParams UHT_STATICS::NewProp_LevelReference = { "LevelReference", nullptr, (EPropertyFlags)0x0014000000000015, UECodeGen_Private::EPropertyGenFlags::SoftObject, nullptr, nullptr, 1, STRUCT_OFFSET(UScenarioDataAsset, LevelReference), Z_Construct_UClass_UWorld, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LevelReference_MetaData), NewProp_LevelReference_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ScenarioId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DurationMinutes,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Complexity_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Complexity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Aversiveness,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitiveDemand,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BaseSuccessRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRequiresSustainedFocus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ContextParams_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ContextParams_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ContextParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LevelReference,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UScenarioDataAsset Property Definitions ************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UPrimaryDataAsset,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UScenarioDataAsset,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UScenarioDataAsset;
UClass* Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UScenarioDataAsset;
		if (!Z_Registration_Info_UClass_UScenarioDataAsset.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ScenarioDataAsset"),
				Z_Registration_Info_UClass_UScenarioDataAsset.InnerSingleton,
				nullptr,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_UScenarioDataAsset.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UScenarioDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UScenarioDataAsset.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UScenarioDataAsset.OuterSingleton;
}
#undef UHT_STATICS
UScenarioDataAsset::UScenarioDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UScenarioDataAsset);
UScenarioDataAsset::~UScenarioDataAsset() {}
// ********** End Class UScenarioDataAsset *********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_EScenarioCategory, TEXT("EScenarioCategory"), &ZRIE_EScenarioCategory, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1128058304U) },
		{ Z_Construct_UEnum_WorldEngine_EScenarioComplexity, TEXT("EScenarioComplexity"), &ZRIE_EScenarioComplexity, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2820654333U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UScenarioDataAsset, TEXT("UScenarioDataAsset"), &Z_Registration_Info_UClass_UScenarioDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UScenarioDataAsset), 65421637U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioDataAsset_h__Script_WorldEngine_8c63fb0bff07b558d979e6fadb860669d06a9e13{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
