// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/NLTAtmosphereSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTAtmosphereSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAtmosphereSubsystem(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAtmosphereSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum ENLTTimeOfDayPhase ********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTTimeOfDayPhase>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Afternoon.DisplayName", "Afternoon" },
		{ "Afternoon.Name", "ENLTTimeOfDayPhase::Afternoon" },
		{ "BlueprintType", "true" },
		{ "Dawn.DisplayName", "Dawn" },
		{ "Dawn.Name", "ENLTTimeOfDayPhase::Dawn" },
		{ "Dusk.DisplayName", "Dusk" },
		{ "Dusk.Name", "ENLTTimeOfDayPhase::Dusk" },
		{ "Midday.DisplayName", "Midday" },
		{ "Midday.Name", "ENLTTimeOfDayPhase::Midday" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
		{ "Morning.DisplayName", "Morning" },
		{ "Morning.Name", "ENLTTimeOfDayPhase::Morning" },
		{ "Night.DisplayName", "Night" },
		{ "Night.Name", "ENLTTimeOfDayPhase::Night" },
		{ "Sunset.DisplayName", "Sunset" },
		{ "Sunset.Name", "ENLTTimeOfDayPhase::Sunset" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTTimeOfDayPhase::Dawn", (int64)ENLTTimeOfDayPhase::Dawn },
		{ "ENLTTimeOfDayPhase::Morning", (int64)ENLTTimeOfDayPhase::Morning },
		{ "ENLTTimeOfDayPhase::Midday", (int64)ENLTTimeOfDayPhase::Midday },
		{ "ENLTTimeOfDayPhase::Afternoon", (int64)ENLTTimeOfDayPhase::Afternoon },
		{ "ENLTTimeOfDayPhase::Sunset", (int64)ENLTTimeOfDayPhase::Sunset },
		{ "ENLTTimeOfDayPhase::Dusk", (int64)ENLTTimeOfDayPhase::Dusk },
		{ "ENLTTimeOfDayPhase::Night", (int64)ENLTTimeOfDayPhase::Night },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTTimeOfDayPhase",
	"ENLTTimeOfDayPhase",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTTimeOfDayPhase;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTTimeOfDayPhase.OuterSingleton)
		{
			ZRIE_ENLTTimeOfDayPhase.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTTimeOfDayPhase"));
		}
		return ZRIE_ENLTTimeOfDayPhase.OuterSingleton;
	}
	if (!ZRIE_ENLTTimeOfDayPhase.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTTimeOfDayPhase.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTTimeOfDayPhase.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTTimeOfDayPhase **********************************************************

// ********** Begin Class UNLTAtmosphereSubsystem Function AdvanceTimeOfDay ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_AdvanceTimeOfDay_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventAdvanceTimeOfDay_Parms
	{
		float DeltaHours;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AdvanceTimeOfDay constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaHours;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AdvanceTimeOfDay constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AdvanceTimeOfDay Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeltaHours = { "DeltaHours", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAtmosphereSubsystem_eventAdvanceTimeOfDay_Parms, DeltaHours), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeltaHours,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function AdvanceTimeOfDay Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "AdvanceTimeOfDay", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventAdvanceTimeOfDay_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventAdvanceTimeOfDay_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_AdvanceTimeOfDay(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execAdvanceTimeOfDay)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaHours);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AdvanceTimeOfDay(Z_Param_DeltaHours);
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function AdvanceTimeOfDay **************************

// ********** Begin Class UNLTAtmosphereSubsystem Function AreStarsVisible *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_AreStarsVisible_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventAreStarsVisible_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere|SkyDome" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AreStarsVisible constinit property declarations ***********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTAtmosphereSubsystem_eventAreStarsVisible_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AreStarsVisible constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AreStarsVisible Property Definitions **********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTAtmosphereSubsystem_eventAreStarsVisible_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function AreStarsVisible Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "AreStarsVisible", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventAreStarsVisible_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventAreStarsVisible_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_AreStarsVisible(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execAreStarsVisible)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->AreStarsVisible();
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function AreStarsVisible ***************************

// ********** Begin Class UNLTAtmosphereSubsystem Function GetDaylightFactor ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetDaylightFactor_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventGetDaylightFactor_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Utility ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Utility ===" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetDaylightFactor constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetDaylightFactor constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetDaylightFactor Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAtmosphereSubsystem_eventGetDaylightFactor_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetDaylightFactor Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "GetDaylightFactor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventGetDaylightFactor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventGetDaylightFactor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetDaylightFactor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execGetDaylightFactor)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetDaylightFactor();
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function GetDaylightFactor *************************

// ********** Begin Class UNLTAtmosphereSubsystem Function GetSunDirection *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetSunDirection_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventGetSunDirection_Parms
	{
		FVector ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetSunDirection constinit property declarations ***********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetSunDirection constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetSunDirection Property Definitions **********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAtmosphereSubsystem_eventGetSunDirection_Parms, ReturnValue), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetSunDirection Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "GetSunDirection", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventGetSunDirection_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventGetSunDirection_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetSunDirection(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execGetSunDirection)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVector*)Z_Param__Result=P_THIS->GetSunDirection();
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function GetSunDirection ***************************

// ********** Begin Class UNLTAtmosphereSubsystem Function GetTimeOfDayHours ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetTimeOfDayHours_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventGetTimeOfDayHours_Parms
	{
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Time-of-Day Control ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Time-of-Day Control ===" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetTimeOfDayHours constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTimeOfDayHours constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTimeOfDayHours Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAtmosphereSubsystem_eventGetTimeOfDayHours_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetTimeOfDayHours Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "GetTimeOfDayHours", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventGetTimeOfDayHours_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventGetTimeOfDayHours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetTimeOfDayHours(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execGetTimeOfDayHours)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->GetTimeOfDayHours();
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function GetTimeOfDayHours *************************

// ********** Begin Class UNLTAtmosphereSubsystem Function GetTimeOfDayPhase ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetTimeOfDayPhase_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventGetTimeOfDayPhase_Parms
	{
		ENLTTimeOfDayPhase ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetTimeOfDayPhase constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_ReturnValue_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTimeOfDayPhase constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTimeOfDayPhase Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_ReturnValue_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAtmosphereSubsystem_eventGetTimeOfDayPhase_Parms, ReturnValue), Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase, METADATA_PARAMS(0, nullptr) }; // 613c91d4658e799ee9bdbc3e7472b7997d245018
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetTimeOfDayPhase Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "GetTimeOfDayPhase", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventGetTimeOfDayPhase_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventGetTimeOfDayPhase_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetTimeOfDayPhase(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execGetTimeOfDayPhase)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ENLTTimeOfDayPhase*)Z_Param__Result=P_THIS->GetTimeOfDayPhase();
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function GetTimeOfDayPhase *************************

// ********** Begin Class UNLTAtmosphereSubsystem Function RefreshAtmosphere ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_RefreshAtmosphere_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RefreshAtmosphere constinit property declarations *********************
// ********** End Function RefreshAtmosphere constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "RefreshAtmosphere", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_RefreshAtmosphere(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execRefreshAtmosphere)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RefreshAtmosphere();
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function RefreshAtmosphere *************************

// ********** Begin Class UNLTAtmosphereSubsystem Function SetTimeOfDayHours ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAtmosphereSubsystem_SetTimeOfDayHours_Statics
struct UHT_STATICS
{
	struct NLTAtmosphereSubsystem_eventSetTimeOfDayHours_Parms
	{
		float InHours;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetTimeOfDayHours constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InHours;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetTimeOfDayHours constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetTimeOfDayHours Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InHours = { "InHours", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAtmosphereSubsystem_eventSetTimeOfDayHours_Parms, InHours), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InHours,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetTimeOfDayHours Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAtmosphereSubsystem, nullptr, "SetTimeOfDayHours", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAtmosphereSubsystem_eventSetTimeOfDayHours_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAtmosphereSubsystem_eventSetTimeOfDayHours_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAtmosphereSubsystem_SetTimeOfDayHours(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAtmosphereSubsystem::execSetTimeOfDayHours)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InHours);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetTimeOfDayHours(Z_Param_InHours);
	P_NATIVE_END;
}
// ********** End Class UNLTAtmosphereSubsystem Function SetTimeOfDayHours *************************

// ********** Begin Class UNLTAtmosphereSubsystem **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTAtmosphereSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Simulation/NLTAtmosphereSubsystem.h" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RealSecondsPerGameDay_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAutoAdvanceTime_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StartTimeOfDay_MetaData[] = {
		{ "Category", "NLT|Atmosphere" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunIntensityMidday_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sun" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Sun Light ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Sun Light ===" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunIntensityNight_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sun" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunColorMidday_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sun" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunColorDawn_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sun" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SunColorNight_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sun" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSunCastShadows_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sun" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyIntensityMidday_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sky" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Sky Light ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Sky Light ===" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyIntensityNight_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sky" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyColorDay_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sky" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyColorNight_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sky" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyColorDawn_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sky" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseRealTimeSkyCapture_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Sky" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogDensityDay_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Height Fog ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Height Fog ===" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogDensityNight_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogColorDawn_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogColorDay_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogColorNight_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogHeightFalloff_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogStartDistance_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFogEnabled_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Fog" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StarIntensity_MetaData[] = {
		{ "Category", "NLT|Atmosphere|SkyDome" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Sky Dome ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Sky Dome ===" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HorizonGlowIntensity_MetaData[] = {
		{ "Category", "NLT|Atmosphere|SkyDome" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SkyDomeMaterial_MetaData[] = {
		{ "Category", "NLT|Atmosphere|SkyDome" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorGradingStrength_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Color" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// === Color Grading ===\n" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "=== Color Grading ===" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarmTintStrength_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Color" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoolTintStrength_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Color" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MiddayContrast_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Color" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MiddaySaturation_MetaData[] = {
		{ "Category", "NLT|Atmosphere|Color" },
		{ "ModuleRelativePath", "Public/Simulation/NLTAtmosphereSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTAtmosphereSubsystem constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RealSecondsPerGameDay;
	static void NewProp_bAutoAdvanceTime_SetBit(void* Obj)
	{
		((UNLTAtmosphereSubsystem*)Obj)->bAutoAdvanceTime = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAutoAdvanceTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StartTimeOfDay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunIntensityMidday;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SunIntensityNight;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SunColorMidday;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SunColorDawn;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SunColorNight;
	static void NewProp_bSunCastShadows_SetBit(void* Obj)
	{
		((UNLTAtmosphereSubsystem*)Obj)->bSunCastShadows = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSunCastShadows;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SkyIntensityMidday;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SkyIntensityNight;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyColorDay;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyColorNight;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SkyColorDawn;
	static void NewProp_bUseRealTimeSkyCapture_SetBit(void* Obj)
	{
		((UNLTAtmosphereSubsystem*)Obj)->bUseRealTimeSkyCapture = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseRealTimeSkyCapture;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogDensityDay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogDensityNight;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FogColorDawn;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FogColorDay;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FogColorNight;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogHeightFalloff;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogStartDistance;
	static void NewProp_bFogEnabled_SetBit(void* Obj)
	{
		((UNLTAtmosphereSubsystem*)Obj)->bFogEnabled = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFogEnabled;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_StarIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_HorizonGlowIntensity;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SkyDomeMaterial;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ColorGradingStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WarmTintStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CoolTintStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MiddayContrast;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MiddaySaturation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UNLTAtmosphereSubsystem constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AdvanceTimeOfDay"), .Pointer = &UNLTAtmosphereSubsystem::execAdvanceTimeOfDay },
		{ .NameUTF8 = UTF8TEXT("AreStarsVisible"), .Pointer = &UNLTAtmosphereSubsystem::execAreStarsVisible },
		{ .NameUTF8 = UTF8TEXT("GetDaylightFactor"), .Pointer = &UNLTAtmosphereSubsystem::execGetDaylightFactor },
		{ .NameUTF8 = UTF8TEXT("GetSunDirection"), .Pointer = &UNLTAtmosphereSubsystem::execGetSunDirection },
		{ .NameUTF8 = UTF8TEXT("GetTimeOfDayHours"), .Pointer = &UNLTAtmosphereSubsystem::execGetTimeOfDayHours },
		{ .NameUTF8 = UTF8TEXT("GetTimeOfDayPhase"), .Pointer = &UNLTAtmosphereSubsystem::execGetTimeOfDayPhase },
		{ .NameUTF8 = UTF8TEXT("RefreshAtmosphere"), .Pointer = &UNLTAtmosphereSubsystem::execRefreshAtmosphere },
		{ .NameUTF8 = UTF8TEXT("SetTimeOfDayHours"), .Pointer = &UNLTAtmosphereSubsystem::execSetTimeOfDayHours },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_AdvanceTimeOfDay, "AdvanceTimeOfDay" }, // 15b162a02b14c314718dd5c3760b13033fc580b3
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_AreStarsVisible, "AreStarsVisible" }, // ec9d3081dc7249919db175632141a3c8c1220eba
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetDaylightFactor, "GetDaylightFactor" }, // d1715d29d8771ab612a3561a95752b55075ea201
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetSunDirection, "GetSunDirection" }, // a46ce0ef7b6ec8fcc8f3da43d789361add2801e9
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetTimeOfDayHours, "GetTimeOfDayHours" }, // ee988268c37f733419c1339465316dc3ab4cef1f
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_GetTimeOfDayPhase, "GetTimeOfDayPhase" }, // d825b804f5aef440efd742d6622b7aec870d8616
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_RefreshAtmosphere, "RefreshAtmosphere" }, // d445c073a6a02c1705a9ba3a93d70a5fdfb8d453
		{ &Z_Construct_UFunction_UNLTAtmosphereSubsystem_SetTimeOfDayHours, "SetTimeOfDayHours" }, // f3a2293d1b39bbf20af887d9680b0b9487814bab
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTAtmosphereSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UNLTAtmosphereSubsystem Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RealSecondsPerGameDay = { "RealSecondsPerGameDay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, RealSecondsPerGameDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RealSecondsPerGameDay_MetaData), NewProp_RealSecondsPerGameDay_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bAutoAdvanceTime = { "bAutoAdvanceTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTAtmosphereSubsystem), &UHT_STATICS::NewProp_bAutoAdvanceTime_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAutoAdvanceTime_MetaData), NewProp_bAutoAdvanceTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_StartTimeOfDay = { "StartTimeOfDay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, StartTimeOfDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StartTimeOfDay_MetaData), NewProp_StartTimeOfDay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SunIntensityMidday = { "SunIntensityMidday", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SunIntensityMidday), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunIntensityMidday_MetaData), NewProp_SunIntensityMidday_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SunIntensityNight = { "SunIntensityNight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SunIntensityNight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunIntensityNight_MetaData), NewProp_SunIntensityNight_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SunColorMidday = { "SunColorMidday", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SunColorMidday), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunColorMidday_MetaData), NewProp_SunColorMidday_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SunColorDawn = { "SunColorDawn", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SunColorDawn), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunColorDawn_MetaData), NewProp_SunColorDawn_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SunColorNight = { "SunColorNight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SunColorNight), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SunColorNight_MetaData), NewProp_SunColorNight_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bSunCastShadows = { "bSunCastShadows", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTAtmosphereSubsystem), &UHT_STATICS::NewProp_bSunCastShadows_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSunCastShadows_MetaData), NewProp_bSunCastShadows_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SkyIntensityMidday = { "SkyIntensityMidday", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SkyIntensityMidday), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyIntensityMidday_MetaData), NewProp_SkyIntensityMidday_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SkyIntensityNight = { "SkyIntensityNight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SkyIntensityNight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyIntensityNight_MetaData), NewProp_SkyIntensityNight_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SkyColorDay = { "SkyColorDay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SkyColorDay), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyColorDay_MetaData), NewProp_SkyColorDay_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SkyColorNight = { "SkyColorNight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SkyColorNight), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyColorNight_MetaData), NewProp_SkyColorNight_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SkyColorDawn = { "SkyColorDawn", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SkyColorDawn), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyColorDawn_MetaData), NewProp_SkyColorDawn_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bUseRealTimeSkyCapture = { "bUseRealTimeSkyCapture", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTAtmosphereSubsystem), &UHT_STATICS::NewProp_bUseRealTimeSkyCapture_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseRealTimeSkyCapture_MetaData), NewProp_bUseRealTimeSkyCapture_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FogDensityDay = { "FogDensityDay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogDensityDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogDensityDay_MetaData), NewProp_FogDensityDay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FogDensityNight = { "FogDensityNight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogDensityNight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogDensityNight_MetaData), NewProp_FogDensityNight_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FogColorDawn = { "FogColorDawn", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogColorDawn), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogColorDawn_MetaData), NewProp_FogColorDawn_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FogColorDay = { "FogColorDay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogColorDay), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogColorDay_MetaData), NewProp_FogColorDay_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FogColorNight = { "FogColorNight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogColorNight), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogColorNight_MetaData), NewProp_FogColorNight_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FogHeightFalloff = { "FogHeightFalloff", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogHeightFalloff), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogHeightFalloff_MetaData), NewProp_FogHeightFalloff_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FogStartDistance = { "FogStartDistance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, FogStartDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogStartDistance_MetaData), NewProp_FogStartDistance_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bFogEnabled = { "bFogEnabled", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(UNLTAtmosphereSubsystem), &UHT_STATICS::NewProp_bFogEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFogEnabled_MetaData), NewProp_bFogEnabled_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_StarIntensity = { "StarIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, StarIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StarIntensity_MetaData), NewProp_StarIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_HorizonGlowIntensity = { "HorizonGlowIntensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, HorizonGlowIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HorizonGlowIntensity_MetaData), NewProp_HorizonGlowIntensity_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SkyDomeMaterial = { "SkyDomeMaterial", nullptr, (EPropertyFlags)0x0114000000000005, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, SkyDomeMaterial), Z_Construct_UClass_UMaterialInterface, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SkyDomeMaterial_MetaData), NewProp_SkyDomeMaterial_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ColorGradingStrength = { "ColorGradingStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, ColorGradingStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorGradingStrength_MetaData), NewProp_ColorGradingStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WarmTintStrength = { "WarmTintStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, WarmTintStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarmTintStrength_MetaData), NewProp_WarmTintStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CoolTintStrength = { "CoolTintStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, CoolTintStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoolTintStrength_MetaData), NewProp_CoolTintStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MiddayContrast = { "MiddayContrast", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, MiddayContrast), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MiddayContrast_MetaData), NewProp_MiddayContrast_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MiddaySaturation = { "MiddaySaturation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(UNLTAtmosphereSubsystem, MiddaySaturation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MiddaySaturation_MetaData), NewProp_MiddaySaturation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RealSecondsPerGameDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bAutoAdvanceTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StartTimeOfDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SunIntensityMidday,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SunIntensityNight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SunColorMidday,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SunColorDawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SunColorNight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bSunCastShadows,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkyIntensityMidday,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkyIntensityNight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkyColorDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkyColorNight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkyColorDawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bUseRealTimeSkyCapture,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogDensityDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogDensityNight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogColorDawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogColorDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogColorNight,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogHeightFalloff,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogStartDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bFogEnabled,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StarIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HorizonGlowIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SkyDomeMaterial,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ColorGradingStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WarmTintStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CoolTintStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MiddayContrast,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MiddaySaturation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UNLTAtmosphereSubsystem Property Definitions *******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTAtmosphereSubsystem,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UNLTAtmosphereSubsystem_StaticRegisterNativesUNLTAtmosphereSubsystem()
{
	UClass* Class = UNLTAtmosphereSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTAtmosphereSubsystem;
UClass* Z_Construct_UClass_UNLTAtmosphereSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTAtmosphereSubsystem;
		if (!Z_Registration_Info_UClass_UNLTAtmosphereSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTAtmosphereSubsystem"),
				Z_Registration_Info_UClass_UNLTAtmosphereSubsystem.InnerSingleton,
				UNLTAtmosphereSubsystem_StaticRegisterNativesUNLTAtmosphereSubsystem,
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
		return Z_Registration_Info_UClass_UNLTAtmosphereSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTAtmosphereSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTAtmosphereSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTAtmosphereSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTAtmosphereSubsystem::UNLTAtmosphereSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTAtmosphereSubsystem);
UNLTAtmosphereSubsystem::~UNLTAtmosphereSubsystem() {}
// ********** End Class UNLTAtmosphereSubsystem ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ENLTTimeOfDayPhase, TEXT("ENLTTimeOfDayPhase"), &ZRIE_ENLTTimeOfDayPhase, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1631359444U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTAtmosphereSubsystem, TEXT("UNLTAtmosphereSubsystem"), &Z_Registration_Info_UClass_UNLTAtmosphereSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTAtmosphereSubsystem), 200331730U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTAtmosphereSubsystem_h__Script_WorldEngine_53e9c199b188af6791f7814dd85a44e2a0d53b94{
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
