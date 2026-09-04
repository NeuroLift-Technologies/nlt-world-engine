// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Persistence/NLTPersistenceSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTPersistenceSubsystem() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTPersistenceSubsystem(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSavedGame(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTPersistenceSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTSavedGame *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTSavedGame_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTSavedGame>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTSavedGame); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotName_MetaData[] = {
		{ "Category", "NLTSavedGame" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulationTick_MetaData[] = {
		{ "Category", "NLTSavedGame" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldTime_MetaData[] = {
		{ "Category", "NLTSavedGame" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveEvents_MetaData[] = {
		{ "Category", "NLTSavedGame" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeOfDay_MetaData[] = {
		{ "Category", "NLTSavedGame" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RandomSeed_MetaData[] = {
		{ "Category", "NLTSavedGame" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTSavedGame constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SlotName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SimulationTick;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_WorldTime;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ActiveEvents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActiveEvents;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeOfDay;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RandomSeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTSavedGame constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTSavedGame>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTSavedGame Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SlotName = { "SlotName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSavedGame, SlotName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotName_MetaData), NewProp_SlotName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SimulationTick = { "SimulationTick", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSavedGame, SimulationTick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulationTick_MetaData), NewProp_SimulationTick_MetaData) };
const UECodeGen_Private::FDoublePropertyParams UHT_STATICS::NewProp_WorldTime = { "WorldTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Double, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSavedGame, WorldTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldTime_MetaData), NewProp_WorldTime_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ActiveEvents_Inner = { "ActiveEvents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ActiveEvents = { "ActiveEvents", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSavedGame, ActiveEvents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveEvents_MetaData), NewProp_ActiveEvents_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TimeOfDay = { "TimeOfDay", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSavedGame, TimeOfDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeOfDay_MetaData), NewProp_TimeOfDay_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RandomSeed = { "RandomSeed", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSavedGame, RandomSeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RandomSeed_MetaData), NewProp_RandomSeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SlotName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SimulationTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEvents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEvents,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TimeOfDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RandomSeed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTSavedGame Property Definitions **********************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTSavedGame",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTSavedGame>(),
	alignof(FNLTSavedGame),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTSavedGame;
UScriptStruct* Z_Construct_UScriptStruct_FNLTSavedGame(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTSavedGame.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTSavedGame.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTSavedGame, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTSavedGame"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTSavedGame.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTSavedGame.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTSavedGame.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTSavedGame.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTSavedGame *******************************************************

// ********** Begin Class UNLTPersistenceSubsystem Function DeleteSaveGame *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPersistenceSubsystem_DeleteSaveGame_Statics
struct UHT_STATICS
{
	struct NLTPersistenceSubsystem_eventDeleteSaveGame_Parms
	{
		FString SlotName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Persistence" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DeleteSaveGame constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SlotName;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTPersistenceSubsystem_eventDeleteSaveGame_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeleteSaveGame constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeleteSaveGame Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SlotName = { "SlotName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPersistenceSubsystem_eventDeleteSaveGame_Parms, SlotName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotName_MetaData), NewProp_SlotName_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTPersistenceSubsystem_eventDeleteSaveGame_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SlotName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeleteSaveGame Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPersistenceSubsystem, nullptr, "DeleteSaveGame", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPersistenceSubsystem_eventDeleteSaveGame_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPersistenceSubsystem_eventDeleteSaveGame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPersistenceSubsystem_DeleteSaveGame(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPersistenceSubsystem::execDeleteSaveGame)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SlotName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DeleteSaveGame(Z_Param_SlotName);
	P_NATIVE_END;
}
// ********** End Class UNLTPersistenceSubsystem Function DeleteSaveGame ***************************

// ********** Begin Class UNLTPersistenceSubsystem Function DoesSaveGameExist **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPersistenceSubsystem_DoesSaveGameExist_Statics
struct UHT_STATICS
{
	struct NLTPersistenceSubsystem_eventDoesSaveGameExist_Parms
	{
		FString SlotName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Persistence" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DoesSaveGameExist constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SlotName;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTPersistenceSubsystem_eventDoesSaveGameExist_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoesSaveGameExist constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoesSaveGameExist Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SlotName = { "SlotName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPersistenceSubsystem_eventDoesSaveGameExist_Parms, SlotName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotName_MetaData), NewProp_SlotName_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTPersistenceSubsystem_eventDoesSaveGameExist_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SlotName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoesSaveGameExist Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPersistenceSubsystem, nullptr, "DoesSaveGameExist", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPersistenceSubsystem_eventDoesSaveGameExist_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPersistenceSubsystem_eventDoesSaveGameExist_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPersistenceSubsystem_DoesSaveGameExist(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPersistenceSubsystem::execDoesSaveGameExist)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SlotName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->DoesSaveGameExist(Z_Param_SlotName);
	P_NATIVE_END;
}
// ********** End Class UNLTPersistenceSubsystem Function DoesSaveGameExist ************************

// ********** Begin Class UNLTPersistenceSubsystem Function GetAllSaveSlots ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPersistenceSubsystem_GetAllSaveSlots_Statics
struct UHT_STATICS
{
	struct NLTPersistenceSubsystem_eventGetAllSaveSlots_Parms
	{
		TArray<FString> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Persistence" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllSaveSlots constinit property declarations ***********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllSaveSlots constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllSaveSlots Property Definitions **********************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPersistenceSubsystem_eventGetAllSaveSlots_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllSaveSlots Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPersistenceSubsystem, nullptr, "GetAllSaveSlots", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPersistenceSubsystem_eventGetAllSaveSlots_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPersistenceSubsystem_eventGetAllSaveSlots_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPersistenceSubsystem_GetAllSaveSlots(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPersistenceSubsystem::execGetAllSaveSlots)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FString>*)Z_Param__Result=P_THIS->GetAllSaveSlots();
	P_NATIVE_END;
}
// ********** End Class UNLTPersistenceSubsystem Function GetAllSaveSlots **************************

// ********** Begin Class UNLTPersistenceSubsystem Function LoadGame *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPersistenceSubsystem_LoadGame_Statics
struct UHT_STATICS
{
	struct NLTPersistenceSubsystem_eventLoadGame_Parms
	{
		FString SlotName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Persistence" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function LoadGame constinit property declarations ******************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SlotName;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTPersistenceSubsystem_eventLoadGame_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function LoadGame constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function LoadGame Property Definitions *****************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SlotName = { "SlotName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPersistenceSubsystem_eventLoadGame_Parms, SlotName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotName_MetaData), NewProp_SlotName_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTPersistenceSubsystem_eventLoadGame_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SlotName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function LoadGame Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPersistenceSubsystem, nullptr, "LoadGame", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPersistenceSubsystem_eventLoadGame_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPersistenceSubsystem_eventLoadGame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPersistenceSubsystem_LoadGame(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPersistenceSubsystem::execLoadGame)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SlotName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->LoadGame(Z_Param_SlotName);
	P_NATIVE_END;
}
// ********** End Class UNLTPersistenceSubsystem Function LoadGame *********************************

// ********** Begin Class UNLTPersistenceSubsystem Function SaveGame *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTPersistenceSubsystem_SaveGame_Statics
struct UHT_STATICS
{
	struct NLTPersistenceSubsystem_eventSaveGame_Parms
	{
		FString SlotName;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Persistence" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SlotName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SaveGame constinit property declarations ******************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SlotName;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTPersistenceSubsystem_eventSaveGame_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SaveGame constinit property declarations ********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SaveGame Property Definitions *****************************************
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_SlotName = { "SlotName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(NLTPersistenceSubsystem_eventSaveGame_Parms, SlotName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SlotName_MetaData), NewProp_SlotName_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTPersistenceSubsystem_eventSaveGame_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SlotName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SaveGame Property Definitions *******************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTPersistenceSubsystem, nullptr, "SaveGame", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTPersistenceSubsystem_eventSaveGame_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTPersistenceSubsystem_eventSaveGame_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTPersistenceSubsystem_SaveGame(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTPersistenceSubsystem::execSaveGame)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SlotName);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->SaveGame(Z_Param_SlotName);
	P_NATIVE_END;
}
// ********** End Class UNLTPersistenceSubsystem Function SaveGame *********************************

// ********** Begin Class UNLTPersistenceSubsystem *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTPersistenceSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Persistence/NLTPersistenceSubsystem.h" },
		{ "ModuleRelativePath", "Public/Persistence/NLTPersistenceSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTPersistenceSubsystem constinit property declarations *****************
// ********** End Class UNLTPersistenceSubsystem constinit property declarations *******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DeleteSaveGame"), .Pointer = &UNLTPersistenceSubsystem::execDeleteSaveGame },
		{ .NameUTF8 = UTF8TEXT("DoesSaveGameExist"), .Pointer = &UNLTPersistenceSubsystem::execDoesSaveGameExist },
		{ .NameUTF8 = UTF8TEXT("GetAllSaveSlots"), .Pointer = &UNLTPersistenceSubsystem::execGetAllSaveSlots },
		{ .NameUTF8 = UTF8TEXT("LoadGame"), .Pointer = &UNLTPersistenceSubsystem::execLoadGame },
		{ .NameUTF8 = UTF8TEXT("SaveGame"), .Pointer = &UNLTPersistenceSubsystem::execSaveGame },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTPersistenceSubsystem_DeleteSaveGame, "DeleteSaveGame" }, // 89129113eeee9b55cefbded5d077d89ecd3ed84f
		{ &Z_Construct_UFunction_UNLTPersistenceSubsystem_DoesSaveGameExist, "DoesSaveGameExist" }, // 517c308b558dac4abc40c3bbb49120fd6d3071de
		{ &Z_Construct_UFunction_UNLTPersistenceSubsystem_GetAllSaveSlots, "GetAllSaveSlots" }, // 59415b92316c2d2ffa66ce63c1ad52cb2c0edbfd
		{ &Z_Construct_UFunction_UNLTPersistenceSubsystem_LoadGame, "LoadGame" }, // e2ea7c63c843a1c32e26591f6bf431a291e21892
		{ &Z_Construct_UFunction_UNLTPersistenceSubsystem_SaveGame, "SaveGame" }, // a876c7ebee7def9084a5c891c00036077a676ee2
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTPersistenceSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTPersistenceSubsystem,
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
static void UNLTPersistenceSubsystem_StaticRegisterNativesUNLTPersistenceSubsystem()
{
	UClass* Class = UNLTPersistenceSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTPersistenceSubsystem;
UClass* Z_Construct_UClass_UNLTPersistenceSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTPersistenceSubsystem;
		if (!Z_Registration_Info_UClass_UNLTPersistenceSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTPersistenceSubsystem"),
				Z_Registration_Info_UClass_UNLTPersistenceSubsystem.InnerSingleton,
				UNLTPersistenceSubsystem_StaticRegisterNativesUNLTPersistenceSubsystem,
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
		return Z_Registration_Info_UClass_UNLTPersistenceSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTPersistenceSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTPersistenceSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTPersistenceSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTPersistenceSubsystem::UNLTPersistenceSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTPersistenceSubsystem);
UNLTPersistenceSubsystem::~UNLTPersistenceSubsystem() {}
// ********** End Class UNLTPersistenceSubsystem ***************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTSavedGame, Z_Construct_UScriptStruct_FNLTSavedGame_Statics::NewStructOps, TEXT("NLTSavedGame"),&Z_Registration_Info_UScriptStruct_FNLTSavedGame, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTSavedGame), 1618682969U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTPersistenceSubsystem, TEXT("UNLTPersistenceSubsystem"), &Z_Registration_Info_UClass_UNLTPersistenceSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTPersistenceSubsystem), 3748153270U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Persistence_NLTPersistenceSubsystem_h__Script_WorldEngine_ab1ed0dacbb7942acdaf7a0d4f808df0545cfd6f{
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
