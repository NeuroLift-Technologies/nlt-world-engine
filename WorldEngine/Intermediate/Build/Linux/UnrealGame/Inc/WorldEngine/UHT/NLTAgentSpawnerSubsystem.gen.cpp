// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/NLTAgentSpawnerSubsystem.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTAgentSpawnerSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentRole(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAgentSpawnerSubsystem(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSpawnRequest(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAgentSpawnerSubsystem(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTSpawnRequest **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTSpawnRequest_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTSpawnRequest>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTSpawnRequest); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProfileId_MetaData[] = {
		{ "Category", "NLTSpawnRequest" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "Category", "NLTSpawnRequest" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "NLTSpawnRequest" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "Category", "NLTSpawnRequest" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTSpawnRequest constinit property declarations ******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_ProfileId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTSpawnRequest constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTSpawnRequest>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTSpawnRequest Property Definitions *****************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ProfileId = { "ProfileId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSpawnRequest, ProfileId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProfileId_MetaData), NewProp_ProfileId_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSpawnRequest, Role), Z_Construct_UEnum_WorldEngine_ENLTAgentRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) }; // a15cdb4d293d5445794fbe0b12a625f42b91da5d
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSpawnRequest, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSpawnRequest, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ProfileId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Position,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTSpawnRequest Property Definitions *******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTSpawnRequest",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTSpawnRequest>(),
	alignof(FNLTSpawnRequest),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTSpawnRequest;
UScriptStruct* Z_Construct_UScriptStruct_FNLTSpawnRequest(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTSpawnRequest.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTSpawnRequest.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTSpawnRequest, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTSpawnRequest"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTSpawnRequest.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTSpawnRequest.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTSpawnRequest.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTSpawnRequest.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTSpawnRequest ****************************************************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function DespawnAllAgents **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_DespawnAllAgents_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DespawnAllAgents constinit property declarations **********************
// ********** End Function DespawnAllAgents constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "DespawnAllAgents", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_DespawnAllAgents(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execDespawnAllAgents)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DespawnAllAgents();
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function DespawnAllAgents ************************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function GetAgentCount *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_GetAgentCount_Statics
struct UHT_STATICS
{
	struct NLTAgentSpawnerSubsystem_eventGetAgentCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAgentCount constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAgentCount constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAgentCount Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventGetAgentCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAgentCount Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "GetAgentCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAgentSpawnerSubsystem_eventGetAgentCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAgentSpawnerSubsystem_eventGetAgentCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_GetAgentCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execGetAgentCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetAgentCount();
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function GetAgentCount ***************************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function SetNeedGrowthMultiplier ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SetNeedGrowthMultiplier_Statics
struct UHT_STATICS
{
	struct NLTAgentSpawnerSubsystem_eventSetNeedGrowthMultiplier_Parms
	{
		float InMultiplier;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Applied to FNLTScenarioConfigFragment.NeedGrowthMultiplier at spawn (1.0 = baseline). */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Applied to FNLTScenarioConfigFragment.NeedGrowthMultiplier at spawn (1.0 = baseline)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetNeedGrowthMultiplier constinit property declarations ***************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InMultiplier;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetNeedGrowthMultiplier constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetNeedGrowthMultiplier Property Definitions **************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InMultiplier = { "InMultiplier", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSetNeedGrowthMultiplier_Parms, InMultiplier), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InMultiplier,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetNeedGrowthMultiplier Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "SetNeedGrowthMultiplier", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAgentSpawnerSubsystem_eventSetNeedGrowthMultiplier_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAgentSpawnerSubsystem_eventSetNeedGrowthMultiplier_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SetNeedGrowthMultiplier(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execSetNeedGrowthMultiplier)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_InMultiplier);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetNeedGrowthMultiplier(Z_Param_InMultiplier);
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function SetNeedGrowthMultiplier *****************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function SetSpawnSeed **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SetSpawnSeed_Statics
struct UHT_STATICS
{
	struct NLTAgentSpawnerSubsystem_eventSetSpawnSeed_Parms
	{
		int32 InSeed;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetSpawnSeed constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_InSeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetSpawnSeed constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetSpawnSeed Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_InSeed = { "InSeed", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSetSpawnSeed_Parms, InSeed), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InSeed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetSpawnSeed Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "SetSpawnSeed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAgentSpawnerSubsystem_eventSetSpawnSeed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAgentSpawnerSubsystem_eventSetSpawnSeed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SetSpawnSeed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execSetSpawnSeed)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_InSeed);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetSpawnSeed(Z_Param_InSeed);
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function SetSpawnSeed ****************************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function SpawnAgent ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgent_Statics
struct UHT_STATICS
{
	struct NLTAgentSpawnerSubsystem_eventSpawnAgent_Parms
	{
		FNLTSpawnRequest Request;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Request_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SpawnAgent constinit property declarations ****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Request;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SpawnAgent constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SpawnAgent Property Definitions ***************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSpawnAgent_Parms, Request), Z_Construct_UScriptStruct_FNLTSpawnRequest, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Request_MetaData), NewProp_Request_MetaData) }; // f1e223296aba39f9b17eaef82740be9658c432e9
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Request,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SpawnAgent Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "SpawnAgent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAgentSpawnerSubsystem_eventSpawnAgent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAgentSpawnerSubsystem_eventSpawnAgent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execSpawnAgent)
{
	P_GET_STRUCT_REF(FNLTSpawnRequest,Z_Param_Out_Request);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SpawnAgent(Z_Param_Out_Request);
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function SpawnAgent ******************************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function SpawnAgents ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgents_Statics
struct UHT_STATICS
{
	struct NLTAgentSpawnerSubsystem_eventSpawnAgents_Parms
	{
		int32 Count;
		FVector Origin;
		float Radius;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Origin_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function SpawnAgents constinit property declarations ***************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Origin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SpawnAgents constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SpawnAgents Property Definitions **************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSpawnAgents_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Origin = { "Origin", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSpawnAgents_Parms, Origin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Origin_MetaData), NewProp_Origin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSpawnAgents_Parms, Radius), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Count,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Origin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Radius,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SpawnAgents Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "SpawnAgents", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAgentSpawnerSubsystem_eventSpawnAgents_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04C20401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAgentSpawnerSubsystem_eventSpawnAgents_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgents(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execSpawnAgents)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_GET_STRUCT_REF(FVector,Z_Param_Out_Origin);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Radius);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SpawnAgents(Z_Param_Count,Z_Param_Out_Origin,Z_Param_Radius);
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function SpawnAgents *****************************

// ********** Begin Class UNLTAgentSpawnerSubsystem Function SpawnAgentsByType *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgentsByType_Statics
struct UHT_STATICS
{
	struct NLTAgentSpawnerSubsystem_eventSpawnAgentsByType_Parms
	{
		FName AgentType;
		int32 Count;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Agents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Spawns agents by profile/type name at a default origin with a default radius. */" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Spawns agents by profile/type name at a default origin with a default radius." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SpawnAgentsByType constinit property declarations *********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SpawnAgentsByType constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SpawnAgentsByType Property Definitions ********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentType = { "AgentType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSpawnAgentsByType_Parms, AgentType), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTAgentSpawnerSubsystem_eventSpawnAgentsByType_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Count,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SpawnAgentsByType Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTAgentSpawnerSubsystem, nullptr, "SpawnAgentsByType", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTAgentSpawnerSubsystem_eventSpawnAgentsByType_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTAgentSpawnerSubsystem_eventSpawnAgentsByType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgentsByType(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTAgentSpawnerSubsystem::execSpawnAgentsByType)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentType);
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SpawnAgentsByType(Z_Param_AgentType,Z_Param_Count);
	P_NATIVE_END;
}
// ********** End Class UNLTAgentSpawnerSubsystem Function SpawnAgentsByType ***********************

// ********** Begin Class UNLTAgentSpawnerSubsystem ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTAgentSpawnerSubsystem_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Agents/NLTAgentSpawnerSubsystem.h" },
		{ "ModuleRelativePath", "Public/Agents/NLTAgentSpawnerSubsystem.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTAgentSpawnerSubsystem constinit property declarations ****************
// ********** End Class UNLTAgentSpawnerSubsystem constinit property declarations ******************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DespawnAllAgents"), .Pointer = &UNLTAgentSpawnerSubsystem::execDespawnAllAgents },
		{ .NameUTF8 = UTF8TEXT("GetAgentCount"), .Pointer = &UNLTAgentSpawnerSubsystem::execGetAgentCount },
		{ .NameUTF8 = UTF8TEXT("SetNeedGrowthMultiplier"), .Pointer = &UNLTAgentSpawnerSubsystem::execSetNeedGrowthMultiplier },
		{ .NameUTF8 = UTF8TEXT("SetSpawnSeed"), .Pointer = &UNLTAgentSpawnerSubsystem::execSetSpawnSeed },
		{ .NameUTF8 = UTF8TEXT("SpawnAgent"), .Pointer = &UNLTAgentSpawnerSubsystem::execSpawnAgent },
		{ .NameUTF8 = UTF8TEXT("SpawnAgents"), .Pointer = &UNLTAgentSpawnerSubsystem::execSpawnAgents },
		{ .NameUTF8 = UTF8TEXT("SpawnAgentsByType"), .Pointer = &UNLTAgentSpawnerSubsystem::execSpawnAgentsByType },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_DespawnAllAgents, "DespawnAllAgents" }, // f6cb5d2d832398a8ef283ae8c7a9859c2a9a4d19
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_GetAgentCount, "GetAgentCount" }, // 1409a6b680a823598df8ed0c0127f02249ab80af
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SetNeedGrowthMultiplier, "SetNeedGrowthMultiplier" }, // 31de2329ce66ffb64a30999239b348f3a8bccf3e
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SetSpawnSeed, "SetSpawnSeed" }, // a0bcf6badcb084d668df9d29590abb061f50ec1c
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgent, "SpawnAgent" }, // 97c03126a6110239a5f6eb1b0347dd434277c929
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgents, "SpawnAgents" }, // ea9096f3bfc5e8e90da06921ebdc3deaea8cb961
		{ &Z_Construct_UFunction_UNLTAgentSpawnerSubsystem_SpawnAgentsByType, "SpawnAgentsByType" }, // f30530399ab713009ba76db6efe101aeb25efb39
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTAgentSpawnerSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTAgentSpawnerSubsystem,
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
static void UNLTAgentSpawnerSubsystem_StaticRegisterNativesUNLTAgentSpawnerSubsystem()
{
	UClass* Class = UNLTAgentSpawnerSubsystem::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem;
UClass* Z_Construct_UClass_UNLTAgentSpawnerSubsystem(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTAgentSpawnerSubsystem;
		if (!Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTAgentSpawnerSubsystem"),
				Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem.InnerSingleton,
				UNLTAgentSpawnerSubsystem_StaticRegisterNativesUNLTAgentSpawnerSubsystem,
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
		return Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem.OuterSingleton;
}
#undef UHT_STATICS
UNLTAgentSpawnerSubsystem::UNLTAgentSpawnerSubsystem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTAgentSpawnerSubsystem);
UNLTAgentSpawnerSubsystem::~UNLTAgentSpawnerSubsystem() {}
// ********** End Class UNLTAgentSpawnerSubsystem **************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTSpawnRequest, Z_Construct_UScriptStruct_FNLTSpawnRequest_Statics::NewStructOps, TEXT("NLTSpawnRequest"),&Z_Registration_Info_UScriptStruct_FNLTSpawnRequest, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTSpawnRequest), 4058129193U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTAgentSpawnerSubsystem, TEXT("UNLTAgentSpawnerSubsystem"), &Z_Registration_Info_UClass_UNLTAgentSpawnerSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTAgentSpawnerSubsystem), 1775463575U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentSpawnerSubsystem_h__Script_WorldEngine_1e7dbea21303c902f419a47fcb0de4ac09465658{
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
