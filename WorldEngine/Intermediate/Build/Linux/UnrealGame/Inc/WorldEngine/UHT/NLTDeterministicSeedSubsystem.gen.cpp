// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/NLTDeterministicSeedSubsystem.h"
#include "Core/NLTSimulationState.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTDeterministicSeedSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTSeedCategory(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTDeterministicSeedSubsystem(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTRandomStream(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTDeterministicSeedSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum ENLTSeedCategory **********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTSeedCategory_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTSeedCategory>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTSeedCategory(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Ambient.Comment", "// Visual effects (particles, lighting)\n" },
		{ "Ambient.DisplayName", "Ambient" },
		{ "Ambient.Name", "ENLTSeedCategory::Ambient" },
		{ "Ambient.ToolTip", "Visual effects (particles, lighting)" },
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Categories of deterministic RNG streams for environment-only mode. */" },
#endif
		{ "Dress.DisplayName", "Dress" },
		{ "Dress.Name", "ENLTSeedCategory::Dress" },
		{ "Flora.Comment", "// Prop placement variations\n" },
		{ "Flora.DisplayName", "Flora" },
		{ "Flora.Name", "ENLTSeedCategory::Flora" },
		{ "Flora.ToolTip", "Prop placement variations" },
		{ "Lighting.Comment", "// Weather pattern variations\n" },
		{ "Lighting.DisplayName", "Lighting" },
		{ "Lighting.Name", "ENLTSeedCategory::Lighting" },
		{ "Lighting.ToolTip", "Weather pattern variations" },
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
		{ "Props.Comment", "// Lighting variations\n" },
		{ "Props.DisplayName", "Props" },
		{ "Props.Name", "ENLTSeedCategory::Props" },
		{ "Props.ToolTip", "Lighting variations" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Categories of deterministic RNG streams for environment-only mode." },
#endif
		{ "VFX.Comment", "// Character appearance/outfit variations\n" },
		{ "VFX.DisplayName", "VFX" },
		{ "VFX.Name", "ENLTSeedCategory::VFX" },
		{ "VFX.ToolTip", "Character appearance/outfit variations" },
		{ "Weather.Comment", "// Ambient environment variations\n" },
		{ "Weather.DisplayName", "Weather" },
		{ "Weather.Name", "ENLTSeedCategory::Weather" },
		{ "Weather.ToolTip", "Ambient environment variations" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTSeedCategory::Dress", (int64)ENLTSeedCategory::Dress },
		{ "ENLTSeedCategory::VFX", (int64)ENLTSeedCategory::VFX },
		{ "ENLTSeedCategory::Ambient", (int64)ENLTSeedCategory::Ambient },
		{ "ENLTSeedCategory::Weather", (int64)ENLTSeedCategory::Weather },
		{ "ENLTSeedCategory::Lighting", (int64)ENLTSeedCategory::Lighting },
		{ "ENLTSeedCategory::Props", (int64)ENLTSeedCategory::Props },
		{ "ENLTSeedCategory::Flora", (int64)ENLTSeedCategory::Flora },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTSeedCategory",
	"ENLTSeedCategory",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTSeedCategory;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTSeedCategory(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTSeedCategory.OuterSingleton)
		{
			ZRIE_ENLTSeedCategory.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTSeedCategory"));
		}
		return ZRIE_ENLTSeedCategory.OuterSingleton;
	}
	if (!ZRIE_ENLTSeedCategory.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTSeedCategory.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTSeedCategory.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTSeedCategory ************************************************************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function DeserializeSeedState *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_DeserializeSeedState_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventDeserializeSeedState_Parms
	{
		TArray<uint8> InData;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deserialize and restore seed state. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deserialize and restore seed state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DeserializeSeedState constinit property declarations ******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_InData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InData;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTDeterministicSeedSubsystem_eventDeserializeSeedState_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeserializeSeedState constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeserializeSeedState Property Definitions *****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_InData_Inner = { "InData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_InData = { "InData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventDeserializeSeedState_Parms, InData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InData_MetaData), NewProp_InData_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTDeterministicSeedSubsystem_eventDeserializeSeedState_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeserializeSeedState Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "DeserializeSeedState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventDeserializeSeedState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventDeserializeSeedState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_DeserializeSeedState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execDeserializeSeedState)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_InData);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DeserializeSeedState(Z_Param_Out_InData);
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function DeserializeSeedState ***************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetCategoryRNG *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategoryRNG_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetCategoryRNG_Parms
	{
		ENLTSeedCategory Category;
		FNLTRandomStream ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the RNG stream for a specific category (const access). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the RNG stream for a specific category (const access)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetCategoryRNG constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCategoryRNG constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCategoryRNG Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetCategoryRNG_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetCategoryRNG_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTRandomStream, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReturnValue_MetaData), NewProp_ReturnValue_MetaData) }; // a08a84f563486ccbb5a77664f5a1b7a394e9672d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCategoryRNG Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetCategoryRNG", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetCategoryRNG_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetCategoryRNG_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategoryRNG(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetCategoryRNG)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTRandomStream*)Z_Param__Result=P_THIS->GetCategoryRNG(ENLTSeedCategory(Z_Param_Category));
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetCategoryRNG *********************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetCategoryRNGMutable ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategoryRNGMutable_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetCategoryRNGMutable_Parms
	{
		ENLTSeedCategory Category;
		FNLTRandomStream ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the RNG stream for a specific category (mutable access). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the RNG stream for a specific category (mutable access)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetCategoryRNGMutable constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCategoryRNGMutable constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCategoryRNGMutable Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetCategoryRNGMutable_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetCategoryRNGMutable_Parms, ReturnValue), Z_Construct_UScriptStruct_FNLTRandomStream, METADATA_PARAMS(0, nullptr) }; // a08a84f563486ccbb5a77664f5a1b7a394e9672d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCategoryRNGMutable Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetCategoryRNGMutable", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetCategoryRNGMutable_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetCategoryRNGMutable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategoryRNGMutable(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetCategoryRNGMutable)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FNLTRandomStream*)Z_Param__Result=P_THIS->GetCategoryRNGMutable(ENLTSeedCategory(Z_Param_Category));
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetCategoryRNGMutable **************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetCategorySeed ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategorySeed_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetCategorySeed_Parms
	{
		ENLTSeedCategory Category;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the seed for a specific category. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the seed for a specific category." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetCategorySeed constinit property declarations ***********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetCategorySeed constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetCategorySeed Property Definitions **********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetCategorySeed_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetCategorySeed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetCategorySeed Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetCategorySeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetCategorySeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetCategorySeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategorySeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetCategorySeed)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetCategorySeed(ENLTSeedCategory(Z_Param_Category));
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetCategorySeed ********************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetDeterministicBool *************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicBool_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetDeterministicBool_Parms
	{
		ENLTSeedCategory Category;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get a deterministic bool for a category (50/50). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a deterministic bool for a category (50/50)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDeterministicBool constinit property declarations ******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTDeterministicSeedSubsystem_eventGetDeterministicBool_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDeterministicBool constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDeterministicBool Property Definitions *****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicBool_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTDeterministicSeedSubsystem_eventGetDeterministicBool_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDeterministicBool Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetDeterministicBool", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicBool_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicBool_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicBool(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetDeterministicBool)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetDeterministicBool(ENLTSeedCategory(Z_Param_Category));
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetDeterministicBool ***************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetDeterministicFloat ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicFloat_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetDeterministicFloat_Parms
	{
		ENLTSeedCategory Category;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get a deterministic float [0,1) for a category (advances that stream). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a deterministic float [0,1) for a category (advances that stream)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDeterministicFloat constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDeterministicFloat constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDeterministicFloat Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicFloat_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicFloat_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDeterministicFloat Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetDeterministicFloat", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicFloat_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicFloat_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicFloat(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetDeterministicFloat)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetDeterministicFloat(ENLTSeedCategory(Z_Param_Category));
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetDeterministicFloat **************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetDeterministicIndex ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicIndex_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetDeterministicIndex_Parms
	{
		ENLTSeedCategory Category;
		int32 ArraySize;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get a deterministic index into an array for a category. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a deterministic index into an array for a category." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDeterministicIndex constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ArraySize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDeterministicIndex constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDeterministicIndex Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicIndex_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ArraySize = { "ArraySize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicIndex_Parms, ArraySize), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicIndex_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArraySize,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDeterministicIndex Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetDeterministicIndex", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicIndex_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicIndex_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicIndex(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetDeterministicIndex)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_GET_PROPERTY(FIntProperty,Z_Param_ArraySize);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetDeterministicIndex(ENLTSeedCategory(Z_Param_Category),Z_Param_ArraySize);
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetDeterministicIndex **************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetDeterministicInt **************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicInt_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms
	{
		ENLTSeedCategory Category;
		int32 Min;
		int32 Max;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get a deterministic int in [Min, Max] for a category. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a deterministic int in [Min, Max] for a category." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDeterministicInt constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Min;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Max;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDeterministicInt constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDeterministicInt Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms, Min), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms, Max), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Min,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Max,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDeterministicInt Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetDeterministicInt", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicInt_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicInt(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetDeterministicInt)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_GET_PROPERTY(FIntProperty,Z_Param_Min);
	P_GET_PROPERTY(FIntProperty,Z_Param_Max);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetDeterministicInt(ENLTSeedCategory(Z_Param_Category),Z_Param_Min,Z_Param_Max);
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetDeterministicInt ****************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetDeterministicRange ************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicRange_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms
	{
		ENLTSeedCategory Category;
		float Min;
		float Max;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get a deterministic float in [Min, Max) for a category. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a deterministic float in [Min, Max) for a category." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDeterministicRange constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Min;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Max;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDeterministicRange constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDeterministicRange Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms, Min), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms, Max), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Min,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Max,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDeterministicRange Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetDeterministicRange", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetDeterministicRange_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicRange(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetDeterministicRange)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Min);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Max);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetDeterministicRange(ENLTSeedCategory(Z_Param_Category),Z_Param_Min,Z_Param_Max);
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetDeterministicRange **************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function GetMasterSeed ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetMasterSeed_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventGetMasterSeed_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the current master seed. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the current master seed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetMasterSeed constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetMasterSeed constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetMasterSeed Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventGetMasterSeed_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetMasterSeed Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "GetMasterSeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetMasterSeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventGetMasterSeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetMasterSeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execGetMasterSeed)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetMasterSeed();
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function GetMasterSeed **********************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function ResetAllStreams ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_ResetAllStreams_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Reset all category streams to their initial derived seeds. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reset all category streams to their initial derived seeds." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetAllStreams constinit property declarations ***********************
// ********** End Function ResetAllStreams constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "ResetAllStreams", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_ResetAllStreams(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execResetAllStreams)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetAllStreams();
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function ResetAllStreams ********************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function ResetStream **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_ResetStream_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventResetStream_Parms
	{
		ENLTSeedCategory Category;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Reset a single category stream to its derived seed. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Reset a single category stream to its derived seed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetStream constinit property declarations ***************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Category_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Category;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ResetStream constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ResetStream Property Definitions **************************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Category_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventResetStream_Parms, Category), Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, METADATA_PARAMS(0, nullptr) }; // 50370be78b7ba57045ec110ca68904c416f2dd9a
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Category,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ResetStream Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "ResetStream", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventResetStream_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventResetStream_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_ResetStream(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execResetStream)
{
	P_GET_ENUM(ENLTSeedCategory,Z_Param_Category);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetStream(ENLTSeedCategory(Z_Param_Category));
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function ResetStream ************************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function SerializeSeedState ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_SerializeSeedState_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventSerializeSeedState_Parms
	{
		TArray<uint8> OutData;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Serialize seed state for persistence. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Serialize seed state for persistence." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SerializeSeedState constinit property declarations ********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_OutData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SerializeSeedState constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SerializeSeedState Property Definitions *******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_OutData_Inner = { "OutData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutData = { "OutData", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventSerializeSeedState_Parms, OutData), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SerializeSeedState Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "SerializeSeedState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventSerializeSeedState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventSerializeSeedState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_SerializeSeedState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execSerializeSeedState)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_OutData);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SerializeSeedState(Z_Param_Out_OutData);
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function SerializeSeedState *****************

// ********** Begin Class UNLTDeterministicSeedSubsystem Function SetMasterSeed ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_SetMasterSeed_Statics
struct UHT_STATICS
{
	struct NLTDeterministicSeedSubsystem_eventSetMasterSeed_Parms
	{
		int32 InMasterSeed;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Seed" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set the master seed. Derives all category seeds from it. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set the master seed. Derives all category seeds from it." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetMasterSeed constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_InMasterSeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetMasterSeed constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetMasterSeed Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_InMasterSeed = { "InMasterSeed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTDeterministicSeedSubsystem_eventSetMasterSeed_Parms, InMasterSeed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InMasterSeed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetMasterSeed Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTDeterministicSeedSubsystem, nullptr, "SetMasterSeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTDeterministicSeedSubsystem_eventSetMasterSeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTDeterministicSeedSubsystem_eventSetMasterSeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_SetMasterSeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTDeterministicSeedSubsystem::execSetMasterSeed)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_InMasterSeed);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetMasterSeed(Z_Param_InMasterSeed);
	P_NATIVE_END;
}
// ********** End Class UNLTDeterministicSeedSubsystem Function SetMasterSeed **********************

// ********** Begin Class UNLTDeterministicSeedSubsystem *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTDeterministicSeedSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Deterministic seed management for environment-only mode.\n * Provides separate RNG streams per visual category (dress, VFX, etc.)\n * so that environment variations are reproducible from a single master seed.\n */" },
#endif
		{ "IncludePath", "Simulation/NLTDeterministicSeedSubsystem.h" },
		{ "ModuleRelativePath", "Public/Simulation/NLTDeterministicSeedSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deterministic seed management for environment-only mode.\nProvides separate RNG streams per visual category (dress, VFX, etc.)\nso that environment variations are reproducible from a single master seed." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTDeterministicSeedSubsystem constinit property declarations ***********
// ********** End Class UNLTDeterministicSeedSubsystem constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DeserializeSeedState"), .Pointer = &UNLTDeterministicSeedSubsystem::execDeserializeSeedState },
		{ .NameUTF8 = UTF8TEXT("GetCategoryRNG"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetCategoryRNG },
		{ .NameUTF8 = UTF8TEXT("GetCategoryRNGMutable"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetCategoryRNGMutable },
		{ .NameUTF8 = UTF8TEXT("GetCategorySeed"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetCategorySeed },
		{ .NameUTF8 = UTF8TEXT("GetDeterministicBool"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetDeterministicBool },
		{ .NameUTF8 = UTF8TEXT("GetDeterministicFloat"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetDeterministicFloat },
		{ .NameUTF8 = UTF8TEXT("GetDeterministicIndex"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetDeterministicIndex },
		{ .NameUTF8 = UTF8TEXT("GetDeterministicInt"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetDeterministicInt },
		{ .NameUTF8 = UTF8TEXT("GetDeterministicRange"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetDeterministicRange },
		{ .NameUTF8 = UTF8TEXT("GetMasterSeed"), .Pointer = &UNLTDeterministicSeedSubsystem::execGetMasterSeed },
		{ .NameUTF8 = UTF8TEXT("ResetAllStreams"), .Pointer = &UNLTDeterministicSeedSubsystem::execResetAllStreams },
		{ .NameUTF8 = UTF8TEXT("ResetStream"), .Pointer = &UNLTDeterministicSeedSubsystem::execResetStream },
		{ .NameUTF8 = UTF8TEXT("SerializeSeedState"), .Pointer = &UNLTDeterministicSeedSubsystem::execSerializeSeedState },
		{ .NameUTF8 = UTF8TEXT("SetMasterSeed"), .Pointer = &UNLTDeterministicSeedSubsystem::execSetMasterSeed },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_DeserializeSeedState, "DeserializeSeedState" }, // b1b28cae813dd5f00c00dbb538f235e02d72a4e2
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategoryRNG, "GetCategoryRNG" }, // 997d5e2e3fabb0e9e6dcef3ca8b35aecc0f0e049
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategoryRNGMutable, "GetCategoryRNGMutable" }, // a1ef00973ddc17e2a387460c26e229a3502a0058
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetCategorySeed, "GetCategorySeed" }, // c6246c28b757b9a3d089ce57c7ac3a08343eaf9e
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicBool, "GetDeterministicBool" }, // a80d09c2326d51907b6b4597429eb6950a5cc724
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicFloat, "GetDeterministicFloat" }, // 30105386428cd8ff0e51cc3c2b6d6f2af3911997
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicIndex, "GetDeterministicIndex" }, // f67d9835394fef2d135d3b64660c7abafc2e9dd0
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicInt, "GetDeterministicInt" }, // 6e2fde84828e8d43230161ee748813fb37b33442
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetDeterministicRange, "GetDeterministicRange" }, // 77bf12b2fca7a6a5320cd7574286ef5aed4ac561
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_GetMasterSeed, "GetMasterSeed" }, // da313f804a542b2a95a84c8594a728af6e2b9375
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_ResetAllStreams, "ResetAllStreams" }, // d6223f72612672786838154d03a99b4e97afc2b6
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_ResetStream, "ResetStream" }, // b531452a59197e950fe0b37328f89574e7946c86
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_SerializeSeedState, "SerializeSeedState" }, // ed9940fc4052cb59faa789c88fbba8cfee5c850f
		{ &Z_Construct_UFunction_UNLTDeterministicSeedSubsystem_SetMasterSeed, "SetMasterSeed" }, // c995849366c7a80ea134fe02a8fc2f90b41c793c
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTDeterministicSeedSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTDeterministicSeedSubsystem,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UNLTDeterministicSeedSubsystem_StaticRegisterNativesUNLTDeterministicSeedSubsystem()
{
	UClass* Class = UNLTDeterministicSeedSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem;
UClass* Z_Construct_UClass_UNLTDeterministicSeedSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTDeterministicSeedSubsystem;
		if (!Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTDeterministicSeedSubsystem"),
				Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem.InnerSingleton,
				UNLTDeterministicSeedSubsystem_StaticRegisterNativesUNLTDeterministicSeedSubsystem,
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
		return Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTDeterministicSeedSubsystem::UNLTDeterministicSeedSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTDeterministicSeedSubsystem);
UNLTDeterministicSeedSubsystem::~UNLTDeterministicSeedSubsystem() {}
// ********** End Class UNLTDeterministicSeedSubsystem *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ENLTSeedCategory, TEXT("ENLTSeedCategory"), &ZRIE_ENLTSeedCategory, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1345784807U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTDeterministicSeedSubsystem, TEXT("UNLTDeterministicSeedSubsystem"), &Z_Registration_Info_UClass_UNLTDeterministicSeedSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTDeterministicSeedSubsystem), 1445336699U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTDeterministicSeedSubsystem_h__Script_WorldEngine_648641ba4854202cb4a17f5bfda371c36082fb4a{
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
