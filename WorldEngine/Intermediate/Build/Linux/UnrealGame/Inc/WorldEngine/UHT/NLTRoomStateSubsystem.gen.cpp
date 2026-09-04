// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Simulation/NLTRoomStateSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTRoomStateSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLRoomState(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTRoomStateSubsystem(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnRoomStateChanged__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTRoomStateSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLRoomState ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLRoomState_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLRoomState>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLRoomState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Represents a room's dynamic state at a point in time.\n * Persisted so environment-only mode can restore exact room conditions.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Represents a room's dynamic state at a point in time.\nPersisted so environment-only mode can restore exact room conditions." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RoomId_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemperatureCelsius_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LightingLevel_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseLevel_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Occupancy_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveActivity_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WeatherState_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeOfDayState_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AmbientColor_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FogDensity_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastUpdateTick_MetaData[] = {
		{ "Category", "NLT|RoomState" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLRoomState constinit property declarations **********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TemperatureCelsius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LightingLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Occupancy;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ActiveActivity;
	static const UECodeGen_Private::FNamePropertyParams NewProp_WeatherState;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TimeOfDayState;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AmbientColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogDensity;
	static const UECodeGen_Private::FIntPropertyParams NewProp_LastUpdateTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLRoomState constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLRoomState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLRoomState Property Definitions *********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, RoomId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RoomId_MetaData), NewProp_RoomId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TemperatureCelsius = { "TemperatureCelsius", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, TemperatureCelsius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemperatureCelsius_MetaData), NewProp_TemperatureCelsius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LightingLevel = { "LightingLevel", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, LightingLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LightingLevel_MetaData), NewProp_LightingLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseLevel = { "NoiseLevel", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, NoiseLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseLevel_MetaData), NewProp_NoiseLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Occupancy = { "Occupancy", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, Occupancy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Occupancy_MetaData), NewProp_Occupancy_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ActiveActivity = { "ActiveActivity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, ActiveActivity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveActivity_MetaData), NewProp_ActiveActivity_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_WeatherState = { "WeatherState", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, WeatherState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WeatherState_MetaData), NewProp_WeatherState_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TimeOfDayState = { "TimeOfDayState", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, TimeOfDayState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeOfDayState_MetaData), NewProp_TimeOfDayState_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_AmbientColor = { "AmbientColor", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, AmbientColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AmbientColor_MetaData), NewProp_AmbientColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FogDensity = { "FogDensity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, FogDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FogDensity_MetaData), NewProp_FogDensity_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_LastUpdateTick = { "LastUpdateTick", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLRoomState, LastUpdateTick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastUpdateTick_MetaData), NewProp_LastUpdateTick_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TemperatureCelsius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LightingLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Occupancy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveActivity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WeatherState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TimeOfDayState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AmbientColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LastUpdateTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLRoomState Property Definitions ***********************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLRoomState",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLRoomState>(),
	alignof(FNLRoomState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLRoomState;
UScriptStruct* Z_Construct_UScriptStruct_FNLRoomState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLRoomState.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLRoomState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLRoomState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLRoomState"));
		}
		return Z_Registration_Info_UScriptStruct_FNLRoomState.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLRoomState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLRoomState.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLRoomState.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLRoomState ********************************************************

// ********** Begin Delegate FOnRoomStateChanged ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_WorldEngine_OnRoomStateChanged__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_WorldEngine_eventOnRoomStateChanged_Parms
	{
		FName RoomId;
		FNLRoomState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnRoomStateChanged constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnRoomStateChanged constinit property declarations *********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnRoomStateChanged Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnRoomStateChanged_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnRoomStateChanged_Parms, NewState), Z_Construct_UScriptStruct_FNLRoomState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewState_MetaData), NewProp_NewState_MetaData) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FOnRoomStateChanged Property Definitions ********************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine, nullptr, "OnRoomStateChanged__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_WorldEngine_eventOnRoomStateChanged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_WorldEngine_eventOnRoomStateChanged_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnRoomStateChanged__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnRoomStateChanged *****************************************************

// ********** Begin Class UNLTRoomStateSubsystem Function DeserializeRoomStates ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_DeserializeRoomStates_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventDeserializeRoomStates_Parms
	{
		TArray<uint8> InData;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deserialize and restore all room states. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deserialize and restore all room states." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InData_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DeserializeRoomStates constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_InData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InData;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTRoomStateSubsystem_eventDeserializeRoomStates_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeserializeRoomStates constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeserializeRoomStates Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_InData_Inner = { "InData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_InData = { "InData", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventDeserializeRoomStates_Parms, InData), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InData_MetaData), NewProp_InData_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTRoomStateSubsystem_eventDeserializeRoomStates_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InData,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeserializeRoomStates Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "DeserializeRoomStates", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventDeserializeRoomStates_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventDeserializeRoomStates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_DeserializeRoomStates(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execDeserializeRoomStates)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_InData);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DeserializeRoomStates(Z_Param_Out_InData);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function DeserializeRoomStates **********************

// ********** Begin Class UNLTRoomStateSubsystem Function GetAllRoomIds ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_GetAllRoomIds_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventGetAllRoomIds_Parms
	{
		TArray<FName> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get all registered room IDs. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get all registered room IDs." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllRoomIds constinit property declarations *************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllRoomIds constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllRoomIds Property Definitions ************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventGetAllRoomIds_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllRoomIds Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "GetAllRoomIds", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventGetAllRoomIds_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventGetAllRoomIds_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_GetAllRoomIds(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execGetAllRoomIds)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FName>*)Z_Param__Result=P_THIS->GetAllRoomIds();
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function GetAllRoomIds ******************************

// ********** Begin Class UNLTRoomStateSubsystem Function GetAllRoomStates *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_GetAllRoomStates_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventGetAllRoomStates_Parms
	{
		TArray<FNLRoomState> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get all room states (for bulk serialization). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get all room states (for bulk serialization)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllRoomStates constinit property declarations **********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllRoomStates constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllRoomStates Property Definitions *********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLRoomState, METADATA_PARAMS(0, nullptr) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventGetAllRoomStates_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllRoomStates Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "GetAllRoomStates", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventGetAllRoomStates_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventGetAllRoomStates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_GetAllRoomStates(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execGetAllRoomStates)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FNLRoomState>*)Z_Param__Result=P_THIS->GetAllRoomStates();
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function GetAllRoomStates ***************************

// ********** Begin Class UNLTRoomStateSubsystem Function GetRoomCount *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_GetRoomCount_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventGetRoomCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the number of registered rooms. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the number of registered rooms." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetRoomCount constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRoomCount constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRoomCount Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventGetRoomCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRoomCount Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "GetRoomCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventGetRoomCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventGetRoomCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_GetRoomCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execGetRoomCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetRoomCount();
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function GetRoomCount *******************************

// ********** Begin Class UNLTRoomStateSubsystem Function GetRoomState *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_GetRoomState_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventGetRoomState_Parms
	{
		FName RoomId;
		FNLRoomState OutState;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get a room's current state (returns false if not found). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a room's current state (returns false if not found)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetRoomState constinit property declarations **************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutState;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTRoomStateSubsystem_eventGetRoomState_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRoomState constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRoomState Property Definitions *************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventGetRoomState_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutState = { "OutState", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventGetRoomState_Parms, OutState), Z_Construct_UScriptStruct_FNLRoomState, METADATA_PARAMS(0, nullptr) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTRoomStateSubsystem_eventGetRoomState_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRoomState Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "GetRoomState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventGetRoomState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventGetRoomState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_GetRoomState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execGetRoomState)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_STRUCT_REF(FNLRoomState,Z_Param_Out_OutState);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetRoomState(Z_Param_RoomId,Z_Param_Out_OutState);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function GetRoomState *******************************

// ********** Begin Class UNLTRoomStateSubsystem Function RegisterRoom *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_RegisterRoom_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventRegisterRoom_Parms
	{
		FNLRoomState InitialState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Register a room with initial state. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Register a room with initial state." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RegisterRoom constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InitialState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RegisterRoom constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RegisterRoom Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InitialState = { "InitialState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventRegisterRoom_Parms, InitialState), Z_Construct_UScriptStruct_FNLRoomState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialState_MetaData), NewProp_InitialState_MetaData) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InitialState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RegisterRoom Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "RegisterRoom", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventRegisterRoom_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventRegisterRoom_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_RegisterRoom(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execRegisterRoom)
{
	P_GET_STRUCT_REF(FNLRoomState,Z_Param_Out_InitialState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegisterRoom(Z_Param_Out_InitialState);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function RegisterRoom *******************************

// ********** Begin Class UNLTRoomStateSubsystem Function RestoreAllRoomStates *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_RestoreAllRoomStates_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventRestoreAllRoomStates_Parms
	{
		TArray<FNLRoomState> InStates;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Restore all room states from a bulk set. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Restore all room states from a bulk set." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InStates_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RestoreAllRoomStates constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_InStates_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_InStates;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RestoreAllRoomStates constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RestoreAllRoomStates Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_InStates_Inner = { "InStates", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLRoomState, METADATA_PARAMS(0, nullptr) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_InStates = { "InStates", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventRestoreAllRoomStates_Parms, InStates), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InStates_MetaData), NewProp_InStates_MetaData) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InStates_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InStates,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RestoreAllRoomStates Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "RestoreAllRoomStates", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventRestoreAllRoomStates_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventRestoreAllRoomStates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_RestoreAllRoomStates(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execRestoreAllRoomStates)
{
	P_GET_TARRAY_REF(FNLRoomState,Z_Param_Out_InStates);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RestoreAllRoomStates(Z_Param_Out_InStates);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function RestoreAllRoomStates ***********************

// ********** Begin Class UNLTRoomStateSubsystem Function SerializeRoomStates **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SerializeRoomStates_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSerializeRoomStates_Parms
	{
		TArray<uint8> OutData;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Serialize all room states for persistence. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Serialize all room states for persistence." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SerializeRoomStates constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_OutData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SerializeRoomStates constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SerializeRoomStates Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_OutData_Inner = { "OutData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutData = { "OutData", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSerializeRoomStates_Parms, OutData), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutData,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SerializeRoomStates Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SerializeRoomStates", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSerializeRoomStates_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSerializeRoomStates_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SerializeRoomStates(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSerializeRoomStates)
{
	P_GET_TARRAY_REF(uint8,Z_Param_Out_OutData);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SerializeRoomStates(Z_Param_Out_OutData);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SerializeRoomStates ************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomActivity **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomActivity_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomActivity_Parms
	{
		FName RoomId;
		FName Activity;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's active activity. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's active activity." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomActivity constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_Activity;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomActivity constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomActivity Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomActivity_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_Activity = { "Activity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomActivity_Parms, Activity), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomActivity_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Activity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomActivity Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomActivity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomActivity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomActivity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomActivity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomActivity)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FNameProperty,Z_Param_Activity);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomActivity(Z_Param_RoomId,Z_Param_Activity,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomActivity ****************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomAmbientColor **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomAmbientColor_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomAmbientColor_Parms
	{
		FName RoomId;
		FLinearColor Color;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's ambient color. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's ambient color." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomAmbientColor constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomAmbientColor constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomAmbientColor Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomAmbientColor_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomAmbientColor_Parms, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomAmbientColor_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomAmbientColor Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomAmbientColor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomAmbientColor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomAmbientColor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomAmbientColor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomAmbientColor)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_STRUCT(FLinearColor,Z_Param_Color);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomAmbientColor(Z_Param_RoomId,Z_Param_Color,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomAmbientColor ************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomFogDensity ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomFogDensity_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomFogDensity_Parms
	{
		FName RoomId;
		float FogDensity;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's fog density. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's fog density." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomFogDensity constinit property declarations *********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FogDensity;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomFogDensity constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomFogDensity Property Definitions ********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomFogDensity_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FogDensity = { "FogDensity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomFogDensity_Parms, FogDensity), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomFogDensity_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FogDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomFogDensity Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomFogDensity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomFogDensity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomFogDensity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomFogDensity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomFogDensity)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FFloatProperty,Z_Param_FogDensity);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomFogDensity(Z_Param_RoomId,Z_Param_FogDensity,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomFogDensity **************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomLighting **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomLighting_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomLighting_Parms
	{
		FName RoomId;
		float LightingLevel;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's lighting level. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's lighting level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomLighting constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LightingLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomLighting constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomLighting Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomLighting_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LightingLevel = { "LightingLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomLighting_Parms, LightingLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomLighting_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LightingLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomLighting Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomLighting", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomLighting_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomLighting_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomLighting(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomLighting)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FFloatProperty,Z_Param_LightingLevel);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomLighting(Z_Param_RoomId,Z_Param_LightingLevel,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomLighting ****************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomNoise *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomNoise_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomNoise_Parms
	{
		FName RoomId;
		float NoiseLevel;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's noise level. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's noise level." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomNoise constinit property declarations **************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseLevel;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomNoise constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomNoise Property Definitions *************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomNoise_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseLevel = { "NoiseLevel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomNoise_Parms, NoiseLevel), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomNoise_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomNoise Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomNoise", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomNoise_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomNoise_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomNoise(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomNoise)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FFloatProperty,Z_Param_NoiseLevel);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomNoise(Z_Param_RoomId,Z_Param_NoiseLevel,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomNoise *******************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomTemperature ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomTemperature_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomTemperature_Parms
	{
		FName RoomId;
		float TemperatureC;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's temperature. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's temperature." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomTemperature constinit property declarations ********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TemperatureC;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomTemperature constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomTemperature Property Definitions *******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomTemperature_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TemperatureC = { "TemperatureC", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomTemperature_Parms, TemperatureC), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomTemperature_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TemperatureC,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomTemperature Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomTemperature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomTemperature_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomTemperature_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomTemperature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomTemperature)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FFloatProperty,Z_Param_TemperatureC);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomTemperature(Z_Param_RoomId,Z_Param_TemperatureC,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomTemperature *************************

// ********** Begin Class UNLTRoomStateSubsystem Function SetRoomWeather ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomWeather_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventSetRoomWeather_Parms
	{
		FName RoomId;
		FName WeatherState;
		int32 CurrentTick;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Set a room's weather state. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Set a room's weather state." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetRoomWeather constinit property declarations ************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_WeatherState;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentTick;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetRoomWeather constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetRoomWeather Property Definitions ***********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomWeather_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_WeatherState = { "WeatherState", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomWeather_Parms, WeatherState), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentTick = { "CurrentTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventSetRoomWeather_Parms, CurrentTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WeatherState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentTick,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetRoomWeather Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "SetRoomWeather", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomWeather_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventSetRoomWeather_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomWeather(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execSetRoomWeather)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FNameProperty,Z_Param_WeatherState);
	P_GET_PROPERTY(FIntProperty,Z_Param_CurrentTick);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetRoomWeather(Z_Param_RoomId,Z_Param_WeatherState,Z_Param_CurrentTick);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function SetRoomWeather *****************************

// ********** Begin Class UNLTRoomStateSubsystem Function UnregisterRoom ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_UnregisterRoom_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventUnregisterRoom_Parms
	{
		FName RoomId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unregister a room. */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unregister a room." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UnregisterRoom constinit property declarations ************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTRoomStateSubsystem_eventUnregisterRoom_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UnregisterRoom constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UnregisterRoom Property Definitions ***********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventUnregisterRoom_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTRoomStateSubsystem_eventUnregisterRoom_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function UnregisterRoom Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "UnregisterRoom", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventUnregisterRoom_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventUnregisterRoom_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_UnregisterRoom(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execUnregisterRoom)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->UnregisterRoom(Z_Param_RoomId);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function UnregisterRoom *****************************

// ********** Begin Class UNLTRoomStateSubsystem Function UpdateRoomState **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTRoomStateSubsystem_UpdateRoomState_Statics
struct UHT_STATICS
{
	struct NLTRoomStateSubsystem_eventUpdateRoomState_Parms
	{
		FName RoomId;
		FNLRoomState NewState;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|RoomState" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Update a room's state (broadcasts OnRoomStateChanged). */" },
#endif
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Update a room's state (broadcasts OnRoomStateChanged)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NewState_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function UpdateRoomState constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_NewState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdateRoomState constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdateRoomState Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventUpdateRoomState_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_NewState = { "NewState", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTRoomStateSubsystem_eventUpdateRoomState_Parms, NewState), Z_Construct_UScriptStruct_FNLRoomState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NewState_MetaData), NewProp_NewState_MetaData) }; // fc9fe86a5f00008cd4c764d563efd347a277260f
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NewState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function UpdateRoomState Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTRoomStateSubsystem, nullptr, "UpdateRoomState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTRoomStateSubsystem_eventUpdateRoomState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTRoomStateSubsystem_eventUpdateRoomState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTRoomStateSubsystem_UpdateRoomState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTRoomStateSubsystem::execUpdateRoomState)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_STRUCT_REF(FNLRoomState,Z_Param_Out_NewState);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UpdateRoomState(Z_Param_RoomId,Z_Param_Out_NewState);
	P_NATIVE_END;
}
// ********** End Class UNLTRoomStateSubsystem Function UpdateRoomState ****************************

// ********** Begin Class UNLTRoomStateSubsystem ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTRoomStateSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Room-state persistence for environment-only mode.\n * Tracks and persists the dynamic state of each room/environment zone,\n * enabling deterministic restoration of lighting, weather, activity state.\n */" },
#endif
		{ "IncludePath", "Simulation/NLTRoomStateSubsystem.h" },
		{ "ModuleRelativePath", "Public/Simulation/NLTRoomStateSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Room-state persistence for environment-only mode.\nTracks and persists the dynamic state of each room/environment zone,\nenabling deterministic restoration of lighting, weather, activity state." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTRoomStateSubsystem constinit property declarations *******************
// ********** End Class UNLTRoomStateSubsystem constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DeserializeRoomStates"), .Pointer = &UNLTRoomStateSubsystem::execDeserializeRoomStates },
		{ .NameUTF8 = UTF8TEXT("GetAllRoomIds"), .Pointer = &UNLTRoomStateSubsystem::execGetAllRoomIds },
		{ .NameUTF8 = UTF8TEXT("GetAllRoomStates"), .Pointer = &UNLTRoomStateSubsystem::execGetAllRoomStates },
		{ .NameUTF8 = UTF8TEXT("GetRoomCount"), .Pointer = &UNLTRoomStateSubsystem::execGetRoomCount },
		{ .NameUTF8 = UTF8TEXT("GetRoomState"), .Pointer = &UNLTRoomStateSubsystem::execGetRoomState },
		{ .NameUTF8 = UTF8TEXT("RegisterRoom"), .Pointer = &UNLTRoomStateSubsystem::execRegisterRoom },
		{ .NameUTF8 = UTF8TEXT("RestoreAllRoomStates"), .Pointer = &UNLTRoomStateSubsystem::execRestoreAllRoomStates },
		{ .NameUTF8 = UTF8TEXT("SerializeRoomStates"), .Pointer = &UNLTRoomStateSubsystem::execSerializeRoomStates },
		{ .NameUTF8 = UTF8TEXT("SetRoomActivity"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomActivity },
		{ .NameUTF8 = UTF8TEXT("SetRoomAmbientColor"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomAmbientColor },
		{ .NameUTF8 = UTF8TEXT("SetRoomFogDensity"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomFogDensity },
		{ .NameUTF8 = UTF8TEXT("SetRoomLighting"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomLighting },
		{ .NameUTF8 = UTF8TEXT("SetRoomNoise"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomNoise },
		{ .NameUTF8 = UTF8TEXT("SetRoomTemperature"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomTemperature },
		{ .NameUTF8 = UTF8TEXT("SetRoomWeather"), .Pointer = &UNLTRoomStateSubsystem::execSetRoomWeather },
		{ .NameUTF8 = UTF8TEXT("UnregisterRoom"), .Pointer = &UNLTRoomStateSubsystem::execUnregisterRoom },
		{ .NameUTF8 = UTF8TEXT("UpdateRoomState"), .Pointer = &UNLTRoomStateSubsystem::execUpdateRoomState },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_DeserializeRoomStates, "DeserializeRoomStates" }, // 432812a148ff3b195f06d350f4e19f9c786df603
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_GetAllRoomIds, "GetAllRoomIds" }, // 1ca894cd87aaf4bfc363a0c46bb1e3e0d94b1e0d
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_GetAllRoomStates, "GetAllRoomStates" }, // f651c6ac3562acca4ac7283e82fe4f5dd9c7cf1b
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_GetRoomCount, "GetRoomCount" }, // 2544c7115d5a751348b65b2ca86fba155f4cdff3
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_GetRoomState, "GetRoomState" }, // a80b6cc75c75e9733a7b61e92658c6ddbb28199e
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_RegisterRoom, "RegisterRoom" }, // c4ae3a2260a0742ebb9c6d7da30e82dd39bb1385
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_RestoreAllRoomStates, "RestoreAllRoomStates" }, // 2e4bb99402a3a644116e49ab69228fd66afca333
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SerializeRoomStates, "SerializeRoomStates" }, // c9ca589f515d1eeae8d3f8f57e249bff10d4d5ca
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomActivity, "SetRoomActivity" }, // 2fd5a00d4be0c7184a810c06fbf2f9c30bd5adf8
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomAmbientColor, "SetRoomAmbientColor" }, // 58e4b0a3b581ab5b552ca1491b69abb7135d0f99
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomFogDensity, "SetRoomFogDensity" }, // fbe1b38627e01f4f337fc4fdcead0d26f3d09ac6
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomLighting, "SetRoomLighting" }, // 0d7df39922d5b35ea7c294e57e12e2e47055da09
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomNoise, "SetRoomNoise" }, // 131090775b56f0a53284a8d58f8cb21a475390f3
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomTemperature, "SetRoomTemperature" }, // 659ec96306290f693f26104f2dd6dce699701120
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_SetRoomWeather, "SetRoomWeather" }, // 6e5e83171854ada3a390b52311f7dbb2eb130191
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_UnregisterRoom, "UnregisterRoom" }, // b57fc0c24adad9f3ba1ddc55356464535c34497a
		{ &Z_Construct_UFunction_UNLTRoomStateSubsystem_UpdateRoomState, "UpdateRoomState" }, // 900b354eddeed9f487973bd05a2de7bfa1a76b07
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTRoomStateSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTRoomStateSubsystem,
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
static void UNLTRoomStateSubsystem_StaticRegisterNativesUNLTRoomStateSubsystem()
{
	UClass* Class = UNLTRoomStateSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTRoomStateSubsystem;
UClass* Z_Construct_UClass_UNLTRoomStateSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTRoomStateSubsystem;
		if (!Z_Registration_Info_UClass_UNLTRoomStateSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTRoomStateSubsystem"),
				Z_Registration_Info_UClass_UNLTRoomStateSubsystem.InnerSingleton,
				UNLTRoomStateSubsystem_StaticRegisterNativesUNLTRoomStateSubsystem,
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
		return Z_Registration_Info_UClass_UNLTRoomStateSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTRoomStateSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTRoomStateSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTRoomStateSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTRoomStateSubsystem::UNLTRoomStateSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTRoomStateSubsystem);
UNLTRoomStateSubsystem::~UNLTRoomStateSubsystem() {}
// ********** End Class UNLTRoomStateSubsystem *****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLRoomState, Z_Construct_UScriptStruct_FNLRoomState_Statics::NewStructOps, TEXT("NLRoomState"),&Z_Registration_Info_UScriptStruct_FNLRoomState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLRoomState), 4238338154U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTRoomStateSubsystem, TEXT("UNLTRoomStateSubsystem"), &Z_Registration_Info_UClass_UNLTRoomStateSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTRoomStateSubsystem), 3360073758U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Simulation_NLTRoomStateSubsystem_h__Script_WorldEngine_a8f0dcd008e1f81775b8b24baab57bf7109a8935{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
