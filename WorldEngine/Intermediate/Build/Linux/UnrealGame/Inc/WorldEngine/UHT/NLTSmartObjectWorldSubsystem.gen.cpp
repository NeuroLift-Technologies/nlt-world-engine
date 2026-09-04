// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "World/NLTSmartObjectWorldSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTSmartObjectWorldSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FBox(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSmartObjectWorldSubsystem(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldLocation(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTSmartObjectWorldSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTWorldLocation *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTWorldLocation_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTWorldLocation>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTWorldLocation); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actor_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocationType_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseLevel_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SocialDensity_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Privacy_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldLocation_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvailableActivities_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bounds_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsOccupied_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxOccupants_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentOccupants_MetaData[] = {
		{ "Category", "NLTWorldLocation" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTWorldLocation constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FNamePropertyParams NewProp_LocationType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseLevel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SocialDensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Privacy;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldLocation;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AvailableActivities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_AvailableActivities;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bounds;
	static void NewProp_bIsOccupied_SetBit(void* Obj)
	{
		((FNLTWorldLocation*)Obj)->bIsOccupied = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsOccupied;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxOccupants;
	static const UECodeGen_Private::FNamePropertyParams NewProp_CurrentOccupants_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_CurrentOccupants;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTWorldLocation constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTWorldLocation>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTWorldLocation Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, Actor), Z_Construct_UClass_AActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actor_MetaData), NewProp_Actor_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_LocationType = { "LocationType", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, LocationType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocationType_MetaData), NewProp_LocationType_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NoiseLevel = { "NoiseLevel", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, NoiseLevel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseLevel_MetaData), NewProp_NoiseLevel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SocialDensity = { "SocialDensity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, SocialDensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SocialDensity_MetaData), NewProp_SocialDensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Privacy = { "Privacy", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, Privacy), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Privacy_MetaData), NewProp_Privacy_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WorldLocation = { "WorldLocation", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, WorldLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldLocation_MetaData), NewProp_WorldLocation_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AvailableActivities_Inner = { "AvailableActivities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_AvailableActivities = { "AvailableActivities", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, AvailableActivities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvailableActivities_MetaData), NewProp_AvailableActivities_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Bounds = { "Bounds", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, Bounds), Z_Construct_UScriptStruct_FBox, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bounds_MetaData), NewProp_Bounds_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIsOccupied = { "bIsOccupied", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FNLTWorldLocation), &UHT_STATICS::NewProp_bIsOccupied_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsOccupied_MetaData), NewProp_bIsOccupied_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxOccupants = { "MaxOccupants", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, MaxOccupants), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxOccupants_MetaData), NewProp_MaxOccupants_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_CurrentOccupants_Inner = { "CurrentOccupants", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_CurrentOccupants = { "CurrentOccupants", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTWorldLocation, CurrentOccupants), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentOccupants_MetaData), NewProp_CurrentOccupants_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LocationType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NoiseLevel,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SocialDensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Privacy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvailableActivities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvailableActivities,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Bounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIsOccupied,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxOccupants,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentOccupants_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentOccupants,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTWorldLocation Property Definitions ******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTWorldLocation",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTWorldLocation>(),
	alignof(FNLTWorldLocation),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTWorldLocation;
UScriptStruct* Z_Construct_UScriptStruct_FNLTWorldLocation(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTWorldLocation.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTWorldLocation.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTWorldLocation, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTWorldLocation"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTWorldLocation.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTWorldLocation.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTWorldLocation.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTWorldLocation.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTWorldLocation ***************************************************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function FindBestLocationForAgent **********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindBestLocationForAgent_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms
	{
		FName AgentId;
		ENLTAgentNeed Need;
		FNLTWorldLocation OutLocation;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindBestLocationForAgent constinit property declarations **************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Need_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Need;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutLocation;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindBestLocationForAgent constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindBestLocationForAgent Property Definitions *************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms, AgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Need_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Need = { "Need", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms, Need), Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, METADATA_PARAMS(0, nullptr) }; // 345bcb711db8b50a21de46ae83aa1b8526889732
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutLocation = { "OutLocation", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms, OutLocation), Z_Construct_UScriptStruct_FNLTWorldLocation, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Need_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Need,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function FindBestLocationForAgent Property Definitions ***************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "FindBestLocationForAgent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindBestLocationForAgent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindBestLocationForAgent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execFindBestLocationForAgent)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentId);
	P_GET_ENUM(ENLTAgentNeed,Z_Param_Need);
	P_GET_STRUCT_REF(FNLTWorldLocation,Z_Param_Out_OutLocation);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->FindBestLocationForAgent(Z_Param_AgentId,ENLTAgentNeed(Z_Param_Need),Z_Param_Out_OutLocation);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function FindBestLocationForAgent ************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function FindLocationsByActivity ***********
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByActivity_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventFindLocationsByActivity_Parms
	{
		FName Activity;
		TArray<FNLTWorldLocation> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindLocationsByActivity constinit property declarations ***************
	static const UECodeGen_Private::FNamePropertyParams NewProp_Activity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindLocationsByActivity constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindLocationsByActivity Property Definitions **************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_Activity = { "Activity", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindLocationsByActivity_Parms, Activity), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTWorldLocation, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindLocationsByActivity_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Activity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function FindLocationsByActivity Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "FindLocationsByActivity", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindLocationsByActivity_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindLocationsByActivity_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByActivity(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execFindLocationsByActivity)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_Activity);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FNLTWorldLocation>*)Z_Param__Result=P_THIS->FindLocationsByActivity(Z_Param_Activity);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function FindLocationsByActivity *************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function FindLocationsByNeed ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByNeed_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventFindLocationsByNeed_Parms
	{
		ENLTAgentNeed Need;
		TArray<FNLTWorldLocation> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindLocationsByNeed constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Need_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Need;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindLocationsByNeed constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindLocationsByNeed Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Need_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Need = { "Need", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindLocationsByNeed_Parms, Need), Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, METADATA_PARAMS(0, nullptr) }; // 345bcb711db8b50a21de46ae83aa1b8526889732
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTWorldLocation, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindLocationsByNeed_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Need_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Need,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function FindLocationsByNeed Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "FindLocationsByNeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindLocationsByNeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindLocationsByNeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByNeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execFindLocationsByNeed)
{
	P_GET_ENUM(ENLTAgentNeed,Z_Param_Need);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FNLTWorldLocation>*)Z_Param__Result=P_THIS->FindLocationsByNeed(ENLTAgentNeed(Z_Param_Need));
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function FindLocationsByNeed *****************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function FindLocationsByType ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByType_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventFindLocationsByType_Parms
	{
		FName LocationType;
		TArray<FNLTWorldLocation> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function FindLocationsByType constinit property declarations *******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_LocationType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function FindLocationsByType constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function FindLocationsByType Property Definitions ******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_LocationType = { "LocationType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindLocationsByType_Parms, LocationType), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTWorldLocation, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventFindLocationsByType_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LocationType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function FindLocationsByType Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "FindLocationsByType", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindLocationsByType_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventFindLocationsByType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByType(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execFindLocationsByType)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_LocationType);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FNLTWorldLocation>*)Z_Param__Result=P_THIS->FindLocationsByType(Z_Param_LocationType);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function FindLocationsByType *****************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function GetLocationCount ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_GetLocationCount_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventGetLocationCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetLocationCount constinit property declarations **********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetLocationCount constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetLocationCount Property Definitions *********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventGetLocationCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetLocationCount Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "GetLocationCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventGetLocationCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventGetLocationCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_GetLocationCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execGetLocationCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetLocationCount();
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function GetLocationCount ********************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function RegisterLocation ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_RegisterLocation_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventRegisterLocation_Parms
	{
		AActor* Actor;
		FNLTWorldLocation Location;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RegisterLocation constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RegisterLocation constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RegisterLocation Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventRegisterLocation_Parms, Actor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventRegisterLocation_Parms, Location), Z_Construct_UScriptStruct_FNLTWorldLocation, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) }; // f1eb377f003e3be6265a840cfea7604df29c59ab
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Location,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RegisterLocation Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "RegisterLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventRegisterLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventRegisterLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_RegisterLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execRegisterLocation)
{
	P_GET_OBJECT(AActor,Z_Param_Actor);
	P_GET_STRUCT_REF(FNLTWorldLocation,Z_Param_Out_Location);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RegisterLocation(Z_Param_Actor,Z_Param_Out_Location);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function RegisterLocation ********************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function ReleaseLocation *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_ReleaseLocation_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventReleaseLocation_Parms
	{
		AActor* Actor;
		FName AgentId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ReleaseLocation constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ReleaseLocation constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ReleaseLocation Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventReleaseLocation_Parms, Actor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventReleaseLocation_Parms, AgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ReleaseLocation Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "ReleaseLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventReleaseLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventReleaseLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_ReleaseLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execReleaseLocation)
{
	P_GET_OBJECT(AActor,Z_Param_Actor);
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ReleaseLocation(Z_Param_Actor,Z_Param_AgentId);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function ReleaseLocation *********************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function ReserveLocation *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_ReserveLocation_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventReserveLocation_Parms
	{
		AActor* Actor;
		FName AgentId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function ReserveLocation constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ReserveLocation constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ReserveLocation Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventReserveLocation_Parms, Actor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventReserveLocation_Parms, AgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Actor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ReserveLocation Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "ReserveLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventReserveLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventReserveLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_ReserveLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execReserveLocation)
{
	P_GET_OBJECT(AActor,Z_Param_Actor);
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ReserveLocation(Z_Param_Actor,Z_Param_AgentId);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function ReserveLocation *********************

// ********** Begin Class UNLTSmartObjectWorldSubsystem Function UnregisterLocation ****************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_UnregisterLocation_Statics
struct UHT_STATICS
{
	struct NLTSmartObjectWorldSubsystem_eventUnregisterLocation_Parms
	{
		AActor* Actor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|World" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function UnregisterLocation constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Actor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UnregisterLocation constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UnregisterLocation Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Actor = { "Actor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(NLTSmartObjectWorldSubsystem_eventUnregisterLocation_Parms, Actor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Actor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function UnregisterLocation Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, nullptr, "UnregisterLocation", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTSmartObjectWorldSubsystem_eventUnregisterLocation_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTSmartObjectWorldSubsystem_eventUnregisterLocation_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_UnregisterLocation(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTSmartObjectWorldSubsystem::execUnregisterLocation)
{
	P_GET_OBJECT(AActor,Z_Param_Actor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->UnregisterLocation(Z_Param_Actor);
	P_NATIVE_END;
}
// ********** End Class UNLTSmartObjectWorldSubsystem Function UnregisterLocation ******************

// ********** Begin Class UNLTSmartObjectWorldSubsystem ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTSmartObjectWorldSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "World/NLTSmartObjectWorldSubsystem.h" },
		{ "ModuleRelativePath", "Public/World/NLTSmartObjectWorldSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTSmartObjectWorldSubsystem constinit property declarations ************
// ********** End Class UNLTSmartObjectWorldSubsystem constinit property declarations **************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("FindBestLocationForAgent"), .Pointer = &UNLTSmartObjectWorldSubsystem::execFindBestLocationForAgent },
		{ .NameUTF8 = UTF8TEXT("FindLocationsByActivity"), .Pointer = &UNLTSmartObjectWorldSubsystem::execFindLocationsByActivity },
		{ .NameUTF8 = UTF8TEXT("FindLocationsByNeed"), .Pointer = &UNLTSmartObjectWorldSubsystem::execFindLocationsByNeed },
		{ .NameUTF8 = UTF8TEXT("FindLocationsByType"), .Pointer = &UNLTSmartObjectWorldSubsystem::execFindLocationsByType },
		{ .NameUTF8 = UTF8TEXT("GetLocationCount"), .Pointer = &UNLTSmartObjectWorldSubsystem::execGetLocationCount },
		{ .NameUTF8 = UTF8TEXT("RegisterLocation"), .Pointer = &UNLTSmartObjectWorldSubsystem::execRegisterLocation },
		{ .NameUTF8 = UTF8TEXT("ReleaseLocation"), .Pointer = &UNLTSmartObjectWorldSubsystem::execReleaseLocation },
		{ .NameUTF8 = UTF8TEXT("ReserveLocation"), .Pointer = &UNLTSmartObjectWorldSubsystem::execReserveLocation },
		{ .NameUTF8 = UTF8TEXT("UnregisterLocation"), .Pointer = &UNLTSmartObjectWorldSubsystem::execUnregisterLocation },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindBestLocationForAgent, "FindBestLocationForAgent" }, // cef9eb4dfd4df158d403e27568ab31d29095c445
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByActivity, "FindLocationsByActivity" }, // 2f9bc86132c3dd7f90165a7d8cb8f0968c8f4c47
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByNeed, "FindLocationsByNeed" }, // 857400a6771370da6509ff3282cc460c7d328084
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_FindLocationsByType, "FindLocationsByType" }, // b31be5929565f0317742f7919d9315f6ccc0fbc8
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_GetLocationCount, "GetLocationCount" }, // 72217e9e2417a2cfd0cbc56b8f80445f7dad4c8f
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_RegisterLocation, "RegisterLocation" }, // bb18f760754022cb04b4a134d4742cfcb9d4d241
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_ReleaseLocation, "ReleaseLocation" }, // c7eb183711148d79814c26ab636a24699217271b
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_ReserveLocation, "ReserveLocation" }, // 6afc6745bd4156447cf057ef489aa4d674966858
		{ &Z_Construct_UFunction_UNLTSmartObjectWorldSubsystem_UnregisterLocation, "UnregisterLocation" }, // 26631d9359b22df2d663e479fdb7ba96a77aec37
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTSmartObjectWorldSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTSmartObjectWorldSubsystem,
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
static void UNLTSmartObjectWorldSubsystem_StaticRegisterNativesUNLTSmartObjectWorldSubsystem()
{
	UClass* Class = UNLTSmartObjectWorldSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem;
UClass* Z_Construct_UClass_UNLTSmartObjectWorldSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTSmartObjectWorldSubsystem;
		if (!Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTSmartObjectWorldSubsystem"),
				Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem.InnerSingleton,
				UNLTSmartObjectWorldSubsystem_StaticRegisterNativesUNLTSmartObjectWorldSubsystem,
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
		return Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTSmartObjectWorldSubsystem::UNLTSmartObjectWorldSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTSmartObjectWorldSubsystem);
UNLTSmartObjectWorldSubsystem::~UNLTSmartObjectWorldSubsystem() {}
// ********** End Class UNLTSmartObjectWorldSubsystem **********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTWorldLocation, Z_Construct_UScriptStruct_FNLTWorldLocation_Statics::NewStructOps, TEXT("NLTWorldLocation"),&Z_Registration_Info_UScriptStruct_FNLTWorldLocation, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTWorldLocation), 4058724223U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTSmartObjectWorldSubsystem, TEXT("UNLTSmartObjectWorldSubsystem"), &Z_Registration_Info_UClass_UNLTSmartObjectWorldSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTSmartObjectWorldSubsystem), 2567891064U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_World_NLTSmartObjectWorldSubsystem_h__Script_WorldEngine_d89521add113ff4773876a4eac1a175f42b66498{
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
