// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/NLTEventBus.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTEventBus() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEventBus(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTSimulationEvent(ETypeConstructPhase);
WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationEvent__DelegateSignature(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEventBus(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum ENLTSimulationEventType ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTSimulationEventType>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "AgentCreated.DisplayName", "AgentCreated" },
		{ "AgentCreated.Name", "ENLTSimulationEventType::AgentCreated" },
		{ "AgentDespawned.DisplayName", "AgentDespawned" },
		{ "AgentDespawned.Name", "ENLTSimulationEventType::AgentDespawned" },
		{ "AgentDestroyed.DisplayName", "AgentDestroyed" },
		{ "AgentDestroyed.Name", "ENLTSimulationEventType::AgentDestroyed" },
		{ "AgentMoved.DisplayName", "AgentMoved" },
		{ "AgentMoved.Name", "ENLTSimulationEventType::AgentMoved" },
		{ "AgentSpawned.DisplayName", "AgentSpawned" },
		{ "AgentSpawned.Name", "ENLTSimulationEventType::AgentSpawned" },
		{ "BlueprintType", "true" },
		{ "Breakthrough.DisplayName", "Breakthrough" },
		{ "Breakthrough.Name", "ENLTSimulationEventType::Breakthrough" },
		{ "BurnoutDetected.DisplayName", "BurnoutDetected" },
		{ "BurnoutDetected.Name", "ENLTSimulationEventType::BurnoutDetected" },
		{ "Distraction.DisplayName", "Distraction" },
		{ "Distraction.Name", "ENLTSimulationEventType::Distraction" },
		{ "EmotionalShift.DisplayName", "EmotionalShift" },
		{ "EmotionalShift.Name", "ENLTSimulationEventType::EmotionalShift" },
		{ "EnvAmbientSound.DisplayName", "EnvAmbientSound" },
		{ "EnvAmbientSound.Name", "ENLTSimulationEventType::EnvAmbientSound" },
		{ "EnvFogChanged.DisplayName", "EnvFogChanged" },
		{ "EnvFogChanged.Name", "ENLTSimulationEventType::EnvFogChanged" },
		{ "EnvLightingChanged.DisplayName", "EnvLightingChanged" },
		{ "EnvLightingChanged.Name", "ENLTSimulationEventType::EnvLightingChanged" },
		{ "EnvParticleEffect.DisplayName", "EnvParticleEffect" },
		{ "EnvParticleEffect.Name", "ENLTSimulationEventType::EnvParticleEffect" },
		{ "EnvRoomStateChanged.DisplayName", "EnvRoomStateChanged" },
		{ "EnvRoomStateChanged.Name", "ENLTSimulationEventType::EnvRoomStateChanged" },
		{ "EnvTimeOfDayChanged.DisplayName", "EnvTimeOfDayChanged" },
		{ "EnvTimeOfDayChanged.Name", "ENLTSimulationEventType::EnvTimeOfDayChanged" },
		{ "EnvWeatherChanged.Comment", "// Environment events (environment-only mode)\n" },
		{ "EnvWeatherChanged.DisplayName", "EnvWeatherChanged" },
		{ "EnvWeatherChanged.Name", "ENLTSimulationEventType::EnvWeatherChanged" },
		{ "EnvWeatherChanged.ToolTip", "Environment events (environment-only mode)" },
		{ "EnvWindChanged.DisplayName", "EnvWindChanged" },
		{ "EnvWindChanged.Name", "ENLTSimulationEventType::EnvWindChanged" },
		{ "FusionComplete.DisplayName", "FusionComplete" },
		{ "FusionComplete.Name", "ENLTSimulationEventType::FusionComplete" },
		{ "FusionFail.DisplayName", "FusionFail" },
		{ "FusionFail.Name", "ENLTSimulationEventType::FusionFail" },
		{ "FusionStart.DisplayName", "FusionStart" },
		{ "FusionStart.Name", "ENLTSimulationEventType::FusionStart" },
		{ "IntentChanged.DisplayName", "IntentChanged" },
		{ "IntentChanged.Name", "ENLTSimulationEventType::IntentChanged" },
		{ "ModeChanged.DisplayName", "ModeChanged" },
		{ "ModeChanged.Name", "ENLTSimulationEventType::ModeChanged" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
		{ "NeedChanged.DisplayName", "NeedChanged" },
		{ "NeedChanged.Name", "ENLTSimulationEventType::NeedChanged" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "ENLTSimulationEventType::None" },
		{ "SimulationReset.DisplayName", "SimulationReset" },
		{ "SimulationReset.Name", "ENLTSimulationEventType::SimulationReset" },
		{ "SocialInteraction.DisplayName", "SocialInteraction" },
		{ "SocialInteraction.Name", "ENLTSimulationEventType::SocialInteraction" },
		{ "StressSpike.DisplayName", "StressSpike" },
		{ "StressSpike.Name", "ENLTSimulationEventType::StressSpike" },
		{ "TaskComplete.DisplayName", "TaskComplete" },
		{ "TaskComplete.Name", "ENLTSimulationEventType::TaskComplete" },
		{ "Tick.DisplayName", "Tick" },
		{ "Tick.Name", "ENLTSimulationEventType::Tick" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTSimulationEventType::None", (int64)ENLTSimulationEventType::None },
		{ "ENLTSimulationEventType::Tick", (int64)ENLTSimulationEventType::Tick },
		{ "ENLTSimulationEventType::AgentCreated", (int64)ENLTSimulationEventType::AgentCreated },
		{ "ENLTSimulationEventType::AgentDestroyed", (int64)ENLTSimulationEventType::AgentDestroyed },
		{ "ENLTSimulationEventType::AgentSpawned", (int64)ENLTSimulationEventType::AgentSpawned },
		{ "ENLTSimulationEventType::AgentDespawned", (int64)ENLTSimulationEventType::AgentDespawned },
		{ "ENLTSimulationEventType::AgentMoved", (int64)ENLTSimulationEventType::AgentMoved },
		{ "ENLTSimulationEventType::NeedChanged", (int64)ENLTSimulationEventType::NeedChanged },
		{ "ENLTSimulationEventType::IntentChanged", (int64)ENLTSimulationEventType::IntentChanged },
		{ "ENLTSimulationEventType::EmotionalShift", (int64)ENLTSimulationEventType::EmotionalShift },
		{ "ENLTSimulationEventType::FusionStart", (int64)ENLTSimulationEventType::FusionStart },
		{ "ENLTSimulationEventType::FusionComplete", (int64)ENLTSimulationEventType::FusionComplete },
		{ "ENLTSimulationEventType::FusionFail", (int64)ENLTSimulationEventType::FusionFail },
		{ "ENLTSimulationEventType::StressSpike", (int64)ENLTSimulationEventType::StressSpike },
		{ "ENLTSimulationEventType::BurnoutDetected", (int64)ENLTSimulationEventType::BurnoutDetected },
		{ "ENLTSimulationEventType::Breakthrough", (int64)ENLTSimulationEventType::Breakthrough },
		{ "ENLTSimulationEventType::Distraction", (int64)ENLTSimulationEventType::Distraction },
		{ "ENLTSimulationEventType::SocialInteraction", (int64)ENLTSimulationEventType::SocialInteraction },
		{ "ENLTSimulationEventType::TaskComplete", (int64)ENLTSimulationEventType::TaskComplete },
		{ "ENLTSimulationEventType::SimulationReset", (int64)ENLTSimulationEventType::SimulationReset },
		{ "ENLTSimulationEventType::ModeChanged", (int64)ENLTSimulationEventType::ModeChanged },
		{ "ENLTSimulationEventType::EnvWeatherChanged", (int64)ENLTSimulationEventType::EnvWeatherChanged },
		{ "ENLTSimulationEventType::EnvLightingChanged", (int64)ENLTSimulationEventType::EnvLightingChanged },
		{ "ENLTSimulationEventType::EnvTimeOfDayChanged", (int64)ENLTSimulationEventType::EnvTimeOfDayChanged },
		{ "ENLTSimulationEventType::EnvRoomStateChanged", (int64)ENLTSimulationEventType::EnvRoomStateChanged },
		{ "ENLTSimulationEventType::EnvAmbientSound", (int64)ENLTSimulationEventType::EnvAmbientSound },
		{ "ENLTSimulationEventType::EnvParticleEffect", (int64)ENLTSimulationEventType::EnvParticleEffect },
		{ "ENLTSimulationEventType::EnvFogChanged", (int64)ENLTSimulationEventType::EnvFogChanged },
		{ "ENLTSimulationEventType::EnvWindChanged", (int64)ENLTSimulationEventType::EnvWindChanged },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTSimulationEventType",
	"ENLTSimulationEventType",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTSimulationEventType;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTSimulationEventType.OuterSingleton)
		{
			ZRIE_ENLTSimulationEventType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTSimulationEventType"));
		}
		return ZRIE_ENLTSimulationEventType.OuterSingleton;
	}
	if (!ZRIE_ENLTSimulationEventType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTSimulationEventType.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTSimulationEventType.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTSimulationEventType *****************************************************

// ********** Begin ScriptStruct FNLTSimulationEvent ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTSimulationEvent_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTSimulationEvent>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTSimulationEvent); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventType_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tick_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentId_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetId_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTSimulationEvent constinit property declarations ***************
	static const UECodeGen_Private::FBytePropertyParams NewProp_EventType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EventType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Tick;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TargetId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTSimulationEvent constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTSimulationEvent>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTSimulationEvent Property Definitions **************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_EventType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_EventType = { "EventType", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationEvent, EventType), Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventType_MetaData), NewProp_EventType_MetaData) }; // 0f886609ec20ad73bbfa05804fd1dcd8d59c0e24
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Tick = { "Tick", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationEvent, Tick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tick_MetaData), NewProp_Tick_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationEvent, AgentId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentId_MetaData), NewProp_AgentId_MetaData) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationEvent, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TargetId = { "TargetId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationEvent, TargetId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetId_MetaData), NewProp_TargetId_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTSimulationEvent, Value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTSimulationEvent Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTSimulationEvent",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTSimulationEvent>(),
	alignof(FNLTSimulationEvent),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTSimulationEvent;
UScriptStruct* Z_Construct_UScriptStruct_FNLTSimulationEvent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTSimulationEvent.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTSimulationEvent.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTSimulationEvent, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTSimulationEvent"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTSimulationEvent.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTSimulationEvent.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTSimulationEvent.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTSimulationEvent.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTSimulationEvent *************************************************

// ********** Begin Delegate FOnSimulationEvent ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_WorldEngine_OnSimulationEvent__DelegateSignature_Statics
struct UHT_STATICS
{
	struct _Script_WorldEngine_eventOnSimulationEvent_Parms
	{
		FNLTSimulationEvent Event;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnSimulationEvent constinit property declarations ********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Event;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Delegate FOnSimulationEvent constinit property declarations **********************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};

// ********** Begin Delegate FOnSimulationEvent Property Definitions *******************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_WorldEngine_eventOnSimulationEvent_Parms, Event), Z_Construct_UScriptStruct_FNLTSimulationEvent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Event_MetaData), NewProp_Event_MetaData) }; // 5ed341a8290e78097264a973327583f297d48916
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Event,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Delegate FOnSimulationEvent Property Definitions *********************************
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine, nullptr, "OnSimulationEvent__DelegateSignature", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::_Script_WorldEngine_eventOnSimulationEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::_Script_WorldEngine_eventOnSimulationEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationEvent__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnSimulationEvent ******************************************************

// ********** Begin Class UNLTEventBus Function GetEventsByType ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEventBus_GetEventsByType_Statics
struct UHT_STATICS
{
	struct NLTEventBus_eventGetEventsByType_Parms
	{
		ENLTSimulationEventType EventType;
		TArray<FNLTSimulationEvent> OutEvents;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get all events of a specific type from the ring buffer. */" },
#endif
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get all events of a specific type from the ring buffer." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetEventsByType constinit property declarations ***********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_EventType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EventType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutEvents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutEvents;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetEventsByType constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetEventsByType Property Definitions **********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_EventType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_EventType = { "EventType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventGetEventsByType_Parms, EventType), Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType, METADATA_PARAMS(0, nullptr) }; // 0f886609ec20ad73bbfa05804fd1dcd8d59c0e24
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutEvents_Inner = { "OutEvents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTSimulationEvent, METADATA_PARAMS(0, nullptr) }; // 5ed341a8290e78097264a973327583f297d48916
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutEvents = { "OutEvents", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventGetEventsByType_Parms, OutEvents), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 5ed341a8290e78097264a973327583f297d48916
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutEvents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutEvents,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetEventsByType Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEventBus, nullptr, "GetEventsByType", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEventBus_eventGetEventsByType_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEventBus_eventGetEventsByType_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEventBus_GetEventsByType(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEventBus::execGetEventsByType)
{
	P_GET_ENUM(ENLTSimulationEventType,Z_Param_EventType);
	P_GET_TARRAY_REF(FNLTSimulationEvent,Z_Param_Out_OutEvents);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->GetEventsByType(ENLTSimulationEventType(Z_Param_EventType),Z_Param_Out_OutEvents);
	P_NATIVE_END;
}
// ********** End Class UNLTEventBus Function GetEventsByType **************************************

// ********** Begin Class UNLTEventBus Function GetRecentEvents ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEventBus_GetRecentEvents_Statics
struct UHT_STATICS
{
	struct NLTEventBus_eventGetRecentEvents_Parms
	{
		int32 Count;
		TArray<FNLTSimulationEvent> OutEvents;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the most recent N events from the ring buffer (newest first). */" },
#endif
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the most recent N events from the ring buffer (newest first)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetRecentEvents constinit property declarations ***********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Count;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutEvents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_OutEvents;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetRecentEvents constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetRecentEvents Property Definitions **********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Count = { "Count", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventGetRecentEvents_Parms, Count), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutEvents_Inner = { "OutEvents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FNLTSimulationEvent, METADATA_PARAMS(0, nullptr) }; // 5ed341a8290e78097264a973327583f297d48916
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_OutEvents = { "OutEvents", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventGetRecentEvents_Parms, OutEvents), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 5ed341a8290e78097264a973327583f297d48916
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Count,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutEvents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutEvents,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetRecentEvents Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEventBus, nullptr, "GetRecentEvents", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEventBus_eventGetRecentEvents_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEventBus_eventGetRecentEvents_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEventBus_GetRecentEvents(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEventBus::execGetRecentEvents)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_Count);
	P_GET_TARRAY_REF(FNLTSimulationEvent,Z_Param_Out_OutEvents);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->GetRecentEvents(Z_Param_Count,Z_Param_Out_OutEvents);
	P_NATIVE_END;
}
// ********** End Class UNLTEventBus Function GetRecentEvents **************************************

// ********** Begin Class UNLTEventBus Function GetTotalEventCount *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEventBus_GetTotalEventCount_Statics
struct UHT_STATICS
{
	struct NLTEventBus_eventGetTotalEventCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Get the total number of events ever raised (including overwritten ones). */" },
#endif
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get the total number of events ever raised (including overwritten ones)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetTotalEventCount constinit property declarations ********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetTotalEventCount constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetTotalEventCount Property Definitions *******************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventGetTotalEventCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetTotalEventCount Property Definitions *********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEventBus, nullptr, "GetTotalEventCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEventBus_eventGetTotalEventCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEventBus_eventGetTotalEventCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEventBus_GetTotalEventCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEventBus::execGetTotalEventCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetTotalEventCount();
	P_NATIVE_END;
}
// ********** End Class UNLTEventBus Function GetTotalEventCount ***********************************

// ********** Begin Class UNLTEventBus Function RaiseEnvironmentEvent ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEventBus_RaiseEnvironmentEvent_Statics
struct UHT_STATICS
{
	struct NLTEventBus_eventRaiseEnvironmentEvent_Parms
	{
		ENLTSimulationEventType EventType;
		int32 Tick;
		FName RoomId;
		FString Description;
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation|Environment" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Raise an environment event (no agent, environment-only mode). */" },
#endif
		{ "CPP_Default_Value", "0.000000" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Raise an environment event (no agent, environment-only mode)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function RaiseEnvironmentEvent constinit property declarations *****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_EventType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EventType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Tick;
	static const UECodeGen_Private::FNamePropertyParams NewProp_RoomId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RaiseEnvironmentEvent constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RaiseEnvironmentEvent Property Definitions ****************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_EventType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_EventType = { "EventType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseEnvironmentEvent_Parms, EventType), Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType, METADATA_PARAMS(0, nullptr) }; // 0f886609ec20ad73bbfa05804fd1dcd8d59c0e24
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Tick = { "Tick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseEnvironmentEvent_Parms, Tick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_RoomId = { "RoomId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseEnvironmentEvent_Parms, RoomId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseEnvironmentEvent_Parms, Description), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseEnvironmentEvent_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RoomId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RaiseEnvironmentEvent Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEventBus, nullptr, "RaiseEnvironmentEvent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEventBus_eventRaiseEnvironmentEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEventBus_eventRaiseEnvironmentEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEventBus_RaiseEnvironmentEvent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEventBus::execRaiseEnvironmentEvent)
{
	P_GET_ENUM(ENLTSimulationEventType,Z_Param_EventType);
	P_GET_PROPERTY(FIntProperty,Z_Param_Tick);
	P_GET_PROPERTY(FNameProperty,Z_Param_RoomId);
	P_GET_PROPERTY(FStrProperty,Z_Param_Description);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RaiseEnvironmentEvent(ENLTSimulationEventType(Z_Param_EventType),Z_Param_Tick,Z_Param_RoomId,Z_Param_Description,Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UNLTEventBus Function RaiseEnvironmentEvent ********************************

// ********** Begin Class UNLTEventBus Function RaiseEvent *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEventBus_RaiseEvent_Statics
struct UHT_STATICS
{
	struct NLTEventBus_eventRaiseEvent_Parms
	{
		FNLTSimulationEvent Event;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function RaiseEvent constinit property declarations ****************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Event;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RaiseEvent constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RaiseEvent Property Definitions ***************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseEvent_Parms, Event), Z_Construct_UScriptStruct_FNLTSimulationEvent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Event_MetaData), NewProp_Event_MetaData) }; // 5ed341a8290e78097264a973327583f297d48916
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Event,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RaiseEvent Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEventBus, nullptr, "RaiseEvent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEventBus_eventRaiseEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEventBus_eventRaiseEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEventBus_RaiseEvent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEventBus::execRaiseEvent)
{
	P_GET_STRUCT_REF(FNLTSimulationEvent,Z_Param_Out_Event);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RaiseEvent(Z_Param_Out_Event);
	P_NATIVE_END;
}
// ********** End Class UNLTEventBus Function RaiseEvent *******************************************

// ********** Begin Class UNLTEventBus Function RaiseSimpleEvent ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTEventBus_RaiseSimpleEvent_Statics
struct UHT_STATICS
{
	struct NLTEventBus_eventRaiseSimpleEvent_Parms
	{
		ENLTSimulationEventType EventType;
		int32 Tick;
		FName AgentId;
		FString Description;
		FName TargetId;
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Simulation" },
		{ "CPP_Default_TargetId", "None" },
		{ "CPP_Default_Value", "0.000000" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function RaiseSimpleEvent constinit property declarations **********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_EventType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_EventType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Tick;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TargetId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function RaiseSimpleEvent constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function RaiseSimpleEvent Property Definitions *********************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_EventType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_EventType = { "EventType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseSimpleEvent_Parms, EventType), Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType, METADATA_PARAMS(0, nullptr) }; // 0f886609ec20ad73bbfa05804fd1dcd8d59c0e24
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Tick = { "Tick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseSimpleEvent_Parms, Tick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseSimpleEvent_Parms, AgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams UHT_STATICS::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseSimpleEvent_Parms, Description), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TargetId = { "TargetId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseSimpleEvent_Parms, TargetId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTEventBus_eventRaiseSimpleEvent_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EventType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Tick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function RaiseSimpleEvent Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTEventBus, nullptr, "RaiseSimpleEvent", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTEventBus_eventRaiseSimpleEvent_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTEventBus_eventRaiseSimpleEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTEventBus_RaiseSimpleEvent(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTEventBus::execRaiseSimpleEvent)
{
	P_GET_ENUM(ENLTSimulationEventType,Z_Param_EventType);
	P_GET_PROPERTY(FIntProperty,Z_Param_Tick);
	P_GET_PROPERTY(FNameProperty,Z_Param_AgentId);
	P_GET_PROPERTY(FStrProperty,Z_Param_Description);
	P_GET_PROPERTY(FNameProperty,Z_Param_TargetId);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->RaiseSimpleEvent(ENLTSimulationEventType(Z_Param_EventType),Z_Param_Tick,Z_Param_AgentId,Z_Param_Description,Z_Param_TargetId,Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class UNLTEventBus Function RaiseSimpleEvent *************************************

// ********** Begin Class UNLTEventBus *************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTEventBus_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Core/NLTEventBus.h" },
		{ "ModuleRelativePath", "Public/Core/NLTEventBus.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTEventBus constinit property declarations *****************************
// ********** End Class UNLTEventBus constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetEventsByType"), .Pointer = &UNLTEventBus::execGetEventsByType },
		{ .NameUTF8 = UTF8TEXT("GetRecentEvents"), .Pointer = &UNLTEventBus::execGetRecentEvents },
		{ .NameUTF8 = UTF8TEXT("GetTotalEventCount"), .Pointer = &UNLTEventBus::execGetTotalEventCount },
		{ .NameUTF8 = UTF8TEXT("RaiseEnvironmentEvent"), .Pointer = &UNLTEventBus::execRaiseEnvironmentEvent },
		{ .NameUTF8 = UTF8TEXT("RaiseEvent"), .Pointer = &UNLTEventBus::execRaiseEvent },
		{ .NameUTF8 = UTF8TEXT("RaiseSimpleEvent"), .Pointer = &UNLTEventBus::execRaiseSimpleEvent },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTEventBus_GetEventsByType, "GetEventsByType" }, // 4520bfeff0157e1c7be6909d13628eeb14106df5
		{ &Z_Construct_UFunction_UNLTEventBus_GetRecentEvents, "GetRecentEvents" }, // df38247c56b56b403a3a082c94c31d49c6ba0f79
		{ &Z_Construct_UFunction_UNLTEventBus_GetTotalEventCount, "GetTotalEventCount" }, // 6ea6bdcc98b7213550e1ca07f87c5d3d72f5da7c
		{ &Z_Construct_UFunction_UNLTEventBus_RaiseEnvironmentEvent, "RaiseEnvironmentEvent" }, // d7fc588b01c1dacaca2bca89ce658eeca3f79356
		{ &Z_Construct_UFunction_UNLTEventBus_RaiseEvent, "RaiseEvent" }, // 60b04901cc2c883639c411d302f2f1c8451f0fd6
		{ &Z_Construct_UFunction_UNLTEventBus_RaiseSimpleEvent, "RaiseSimpleEvent" }, // bb912002b4f1ae528cf09f2da05a91403aa42f54
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTEventBus>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTEventBus,
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
static void UNLTEventBus_StaticRegisterNativesUNLTEventBus()
{
	UClass* Class = UNLTEventBus::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTEventBus;
UClass* Z_Construct_UClass_UNLTEventBus(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTEventBus;
		if (!Z_Registration_Info_UClass_UNLTEventBus.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTEventBus"),
				Z_Registration_Info_UClass_UNLTEventBus.InnerSingleton,
				UNLTEventBus_StaticRegisterNativesUNLTEventBus,
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
		return Z_Registration_Info_UClass_UNLTEventBus.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTEventBus.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTEventBus.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTEventBus.OuterSingleton;
}
#undef UHT_STATICS
UNLTEventBus::UNLTEventBus(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTEventBus);
UNLTEventBus::~UNLTEventBus() {}
// ********** End Class UNLTEventBus ***************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ENLTSimulationEventType, TEXT("ENLTSimulationEventType"), &ZRIE_ENLTSimulationEventType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 260597257U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTSimulationEvent, Z_Construct_UScriptStruct_FNLTSimulationEvent_Statics::NewStructOps, TEXT("NLTSimulationEvent"),&Z_Registration_Info_UScriptStruct_FNLTSimulationEvent, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTSimulationEvent), 1590903208U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTEventBus, TEXT("UNLTEventBus"), &Z_Registration_Info_UClass_UNLTEventBus, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTEventBus), 1246238733U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTEventBus_h__Script_WorldEngine_f9a53f2c4d9de65ff8362f4087c79879f149396d{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
