// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/NLTSimulationState.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTSimulationState() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentIntent(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentRole(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ESimulationMode(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentState(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTRandomStream(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSimulationState(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTAgentState ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentState_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentState>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentId_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProfileId_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intent_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Focus_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CognitiveLoad_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stress_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Burnout_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Independence_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FusionReady_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuccessRate_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionalState_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryNeed_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentState constinit property declarations ********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Role;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ProfileId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Intent_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Intent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Focus;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CognitiveLoad;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stress;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Burnout;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Independence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FusionReady;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SuccessRate;
	static const UECodeGen_Private::FNamePropertyParams NewProp_EmotionalState;
	static const UECodeGen_Private::FBytePropertyParams NewProp_PrimaryNeed_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PrimaryNeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentState constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTAgentState Property Definitions *******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, AgentId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentId_MetaData), NewProp_AgentId_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Role), Z_Construct_UEnum_WorldEngine_ENLTAgentRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) }; // a15cdb4d293d5445794fbe0b12a625f42b91da5d
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ProfileId = { "ProfileId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, ProfileId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProfileId_MetaData), NewProp_ProfileId_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Intent_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Intent = { "Intent", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Intent), Z_Construct_UEnum_WorldEngine_ENLTAgentIntent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intent_MetaData), NewProp_Intent_MetaData) }; // 510d8e28c4d53ed4cb1edb895bfe266a65787360
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Focus = { "Focus", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Focus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Focus_MetaData), NewProp_Focus_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CognitiveLoad = { "CognitiveLoad", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, CognitiveLoad), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CognitiveLoad_MetaData), NewProp_CognitiveLoad_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Stress = { "Stress", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Stress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stress_MetaData), NewProp_Stress_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Burnout = { "Burnout", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Burnout), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Burnout_MetaData), NewProp_Burnout_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Independence = { "Independence", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, Independence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Independence_MetaData), NewProp_Independence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FusionReady = { "FusionReady", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, FusionReady), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FusionReady_MetaData), NewProp_FusionReady_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SuccessRate = { "SuccessRate", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, SuccessRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuccessRate_MetaData), NewProp_SuccessRate_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_EmotionalState = { "EmotionalState", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, EmotionalState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionalState_MetaData), NewProp_EmotionalState_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_PrimaryNeed_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_PrimaryNeed = { "PrimaryNeed", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentState, PrimaryNeed), Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryNeed_MetaData), NewProp_PrimaryNeed_MetaData) }; // 345bcb711db8b50a21de46ae83aa1b8526889732
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ProfileId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Intent_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Intent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Focus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitiveLoad,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stress,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Burnout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Independence,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FusionReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SuccessRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmotionalState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PrimaryNeed_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PrimaryNeed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentState Property Definitions *********************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTAgentState",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentState>(),
	alignof(FNLTAgentState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentState;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentState.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentState"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentState.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentState.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentState.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentState ******************************************************

// ********** Begin ScriptStruct FNLTSimulationState ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTSimulationState_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTSimulationState>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTSimulationState); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SimulationTick_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldTime_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeOfDay_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mode_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RandomSeed_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Agents_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActiveEvents_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTSimulationState constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_SimulationTick;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_WorldTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeOfDay;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Mode_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Mode;
	static const UECodeGen_Private::FIntPropertyParams NewProp_RandomSeed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Agents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Agents;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ActiveEvents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActiveEvents;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTSimulationState constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTSimulationState>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTSimulationState Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SimulationTick = { "SimulationTick", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, SimulationTick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SimulationTick_MetaData), NewProp_SimulationTick_MetaData) };
const UECodeGen_Private::FDoublePropertyParams UHT_STATICS::NewProp_WorldTime = { "WorldTime", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Double, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, WorldTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldTime_MetaData), NewProp_WorldTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TimeOfDay = { "TimeOfDay", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, TimeOfDay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeOfDay_MetaData), NewProp_TimeOfDay_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Mode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Mode = { "Mode", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, Mode), Z_Construct_UEnum_WorldEngine_ESimulationMode, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mode_MetaData), NewProp_Mode_MetaData) }; // a8218c1e22a62a7382a9437a3e8095c11a0f2e41
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_RandomSeed = { "RandomSeed", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, RandomSeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RandomSeed_MetaData), NewProp_RandomSeed_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Agents_Inner = { "Agents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTAgentState, METADATA_PARAMS(0, nullptr) }; // 8f96309e449e8b4e3589b2439e4bb2f68406d13e
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_Agents = { "Agents", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, Agents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Agents_MetaData), NewProp_Agents_MetaData) }; // 8f96309e449e8b4e3589b2439e4bb2f68406d13e
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ActiveEvents_Inner = { "ActiveEvents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ActiveEvents = { "ActiveEvents", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationState, ActiveEvents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActiveEvents_MetaData), NewProp_ActiveEvents_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SimulationTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TimeOfDay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Mode_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Mode,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RandomSeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Agents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Agents,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEvents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActiveEvents,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTSimulationState Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTSimulationState",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTSimulationState>(),
	alignof(FNLTSimulationState),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTSimulationState;
UScriptStruct* Z_Construct_UScriptStruct_FNLTSimulationState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTSimulationState.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTSimulationState.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTSimulationState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTSimulationState"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTSimulationState.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTSimulationState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTSimulationState.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTSimulationState.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTSimulationState *************************************************

// ********** Begin ScriptStruct FNLTRandomStream **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTRandomStream_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTRandomStream>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTRandomStream); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Seed_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Calls_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTSimulationState.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTRandomStream constinit property declarations ******************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Seed;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Calls;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTRandomStream constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTRandomStream>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTRandomStream Property Definitions *****************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Seed = { "Seed", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTRandomStream, Seed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Seed_MetaData), NewProp_Seed_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Calls = { "Calls", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTRandomStream, Calls), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Calls_MetaData), NewProp_Calls_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Seed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Calls,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTRandomStream Property Definitions *******************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTRandomStream",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTRandomStream>(),
	alignof(FNLTRandomStream),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTRandomStream;
UScriptStruct* Z_Construct_UScriptStruct_FNLTRandomStream(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTRandomStream.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTRandomStream.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTRandomStream, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTRandomStream"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTRandomStream.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTRandomStream.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTRandomStream.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTRandomStream.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTRandomStream ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationState_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTAgentState, Z_Construct_UScriptStruct_FNLTAgentState_Statics::NewStructOps, TEXT("NLTAgentState"),&Z_Registration_Info_UScriptStruct_FNLTAgentState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentState), 2408984734U) },
		{ Z_Construct_UScriptStruct_FNLTSimulationState, Z_Construct_UScriptStruct_FNLTSimulationState_Statics::NewStructOps, TEXT("NLTSimulationState"),&Z_Registration_Info_UScriptStruct_FNLTSimulationState, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTSimulationState), 3528543290U) },
		{ Z_Construct_UScriptStruct_FNLTRandomStream, Z_Construct_UScriptStruct_FNLTRandomStream_Statics::NewStructOps, TEXT("NLTRandomStream"),&Z_Registration_Info_UScriptStruct_FNLTRandomStream, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTRandomStream), 2693432565U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTSimulationState_h__Script_WorldEngine_835a21e3a91c7d361fcac63874a141213e3ddb3b{
	TEXT("/Script/WorldEngine"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
