// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scenarios/Demo/NLTDemoScenarioFragments.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTDemoScenarioFragments() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
MASSCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMassFragment(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioConfigFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTScenarioNeedsFragment *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTScenarioNeedsFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTScenarioNeedsFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Numeric need drives for scenario agents (all values clamped to 0..1).\n * Grown deterministically by UNLTScenarioNeedsProcessor, consumed by\n * UNLTScenarioDecisionProcessor and the StateTree conditions.\n * Complements the enum-level FNLTAgentNeedsFragment (PrimaryNeed/Urgency).\n */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Numeric need drives for scenario agents (all values clamped to 0..1).\nGrown deterministically by UNLTScenarioNeedsProcessor, consumed by\nUNLTScenarioDecisionProcessor and the StateTree conditions.\nComplements the enum-level FNLTAgentNeedsFragment (PrimaryNeed/Urgency)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Quiet_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rest_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Social_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stimulation_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTScenarioNeedsFragment constinit property declarations *********
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Quiet;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rest;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Social;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stimulation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTScenarioNeedsFragment constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTScenarioNeedsFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTScenarioNeedsFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTScenarioNeedsFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTScenarioNeedsFragment Property Definitions ********************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Quiet = { "Quiet", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioNeedsFragment, Quiet), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Quiet_MetaData), NewProp_Quiet_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Rest = { "Rest", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioNeedsFragment, Rest), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rest_MetaData), NewProp_Rest_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Social = { "Social", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioNeedsFragment, Social), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Social_MetaData), NewProp_Social_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Stimulation = { "Stimulation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioNeedsFragment, Stimulation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stimulation_MetaData), NewProp_Stimulation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Quiet,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Rest,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Social,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stimulation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTScenarioNeedsFragment Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTScenarioNeedsFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTScenarioNeedsFragment>(),
	alignof(FNLTScenarioNeedsFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTScenarioNeedsFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTScenarioNeedsFragment *******************************************

// ********** Begin ScriptStruct FNLTScenarioConfigFragment ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTScenarioConfigFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTScenarioConfigFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTScenarioConfigFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Per-agent tuning for the demo scenario systems. Values are fixed at spawn\n * (deterministic seeding) and never mutated during the simulation.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Per-agent tuning for the demo scenario systems. Values are fixed at spawn\n(deterministic seeding) and never mutated during the simulation." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MovementSpeed_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Movement speed in cm/s (custom movement, no Chaos). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movement speed in cm/s (custom movement, no Chaos)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArrivalRadius_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance at which an agent is considered to have arrived (cm). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance at which an agent is considered to have arrived (cm)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DecisionIntervalTicks_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Decision re-evaluation period in simulation ticks (60 ticks = 1s at fixed 60Hz). */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Decision re-evaluation period in simulation ticks (60 ticks = 1s at fixed 60Hz)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WanderRadius_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max radius (cm) for deterministic wander targets when no location matches. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max radius (cm) for deterministic wander targets when no location matches." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NeedGrowthMultiplier_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Multiplier applied to all need growth rates. Set from the scenario data\n     *  asset (aversiveness + cognitive demand); 1.0 = baseline. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Multiplier applied to all need growth rates. Set from the scenario data\nasset (aversiveness + cognitive demand); 1.0 = baseline." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTScenarioConfigFragment constinit property declarations ********
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MovementSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ArrivalRadius;
	static const UECodeGen_Private::FIntPropertyParams NewProp_DecisionIntervalTicks;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WanderRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NeedGrowthMultiplier;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTScenarioConfigFragment constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTScenarioConfigFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTScenarioConfigFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTScenarioConfigFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTScenarioConfigFragment Property Definitions *******************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MovementSpeed = { "MovementSpeed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioConfigFragment, MovementSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MovementSpeed_MetaData), NewProp_MovementSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ArrivalRadius = { "ArrivalRadius", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioConfigFragment, ArrivalRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArrivalRadius_MetaData), NewProp_ArrivalRadius_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_DecisionIntervalTicks = { "DecisionIntervalTicks", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioConfigFragment, DecisionIntervalTicks), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DecisionIntervalTicks_MetaData), NewProp_DecisionIntervalTicks_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WanderRadius = { "WanderRadius", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioConfigFragment, WanderRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WanderRadius_MetaData), NewProp_WanderRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_NeedGrowthMultiplier = { "NeedGrowthMultiplier", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioConfigFragment, NeedGrowthMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NeedGrowthMultiplier_MetaData), NewProp_NeedGrowthMultiplier_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MovementSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ArrivalRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DecisionIntervalTicks,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WanderRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NeedGrowthMultiplier,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTScenarioConfigFragment Property Definitions *********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTScenarioConfigFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTScenarioConfigFragment>(),
	alignof(FNLTScenarioConfigFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioConfigFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTScenarioConfigFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTScenarioConfigFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTScenarioConfigFragment ******************************************

// ********** Begin Enum ENLTScenarioMovementPhase *************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTScenarioMovementPhase>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Arrived.Name", "ENLTScenarioMovementPhase::Arrived" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Movement phase of a scenario agent. */" },
#endif
		{ "Idle.Name", "ENLTScenarioMovementPhase::Idle" },
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
		{ "Moving.Name", "ENLTScenarioMovementPhase::Moving" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Movement phase of a scenario agent." },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTScenarioMovementPhase::Idle", (int64)ENLTScenarioMovementPhase::Idle },
		{ "ENLTScenarioMovementPhase::Moving", (int64)ENLTScenarioMovementPhase::Moving },
		{ "ENLTScenarioMovementPhase::Arrived", (int64)ENLTScenarioMovementPhase::Arrived },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTScenarioMovementPhase",
	"ENLTScenarioMovementPhase",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTScenarioMovementPhase;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTScenarioMovementPhase.OuterSingleton)
		{
			ZRIE_ENLTScenarioMovementPhase.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTScenarioMovementPhase"));
		}
		return ZRIE_ENLTScenarioMovementPhase.OuterSingleton;
	}
	if (!ZRIE_ENLTScenarioMovementPhase.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTScenarioMovementPhase.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTScenarioMovementPhase.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTScenarioMovementPhase ***************************************************

// ********** Begin ScriptStruct FNLTScenarioBehaviorFragment **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTScenarioBehaviorFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTScenarioBehaviorFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Per-tick behavior state written by the decision processor and read by the\n * movement processor and StateTree tasks.\n */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Per-tick behavior state written by the decision processor and read by the\nmovement processor and StateTree tasks." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Phase_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DrivenNeed_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPosition_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasTarget_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TicksSinceDecision_MetaData[] = {
		{ "ModuleRelativePath", "Public/Scenarios/Demo/NLTDemoScenarioFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTScenarioBehaviorFragment constinit property declarations ******
	static const UECodeGen_Private::FBytePropertyParams NewProp_Phase_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Phase;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DrivenNeed_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DrivenNeed;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetPosition;
	static void NewProp_bHasTarget_SetBit(void* Obj)
	{
		((FNLTScenarioBehaviorFragment*)Obj)->bHasTarget = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasTarget;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TicksSinceDecision;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTScenarioBehaviorFragment constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTScenarioBehaviorFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTScenarioBehaviorFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTScenarioBehaviorFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTScenarioBehaviorFragment Property Definitions *****************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Phase_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Phase = { "Phase", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioBehaviorFragment, Phase), Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Phase_MetaData), NewProp_Phase_MetaData) }; // 81159f3b21a02ec6b2530c11b44b4e59e5ac4329
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_DrivenNeed_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_DrivenNeed = { "DrivenNeed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioBehaviorFragment, DrivenNeed), Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DrivenNeed_MetaData), NewProp_DrivenNeed_MetaData) }; // 345bcb711db8b50a21de46ae83aa1b8526889732
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TargetPosition = { "TargetPosition", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioBehaviorFragment, TargetPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPosition_MetaData), NewProp_TargetPosition_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bHasTarget = { "bHasTarget", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FNLTScenarioBehaviorFragment), &UHT_STATICS::NewProp_bHasTarget_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasTarget_MetaData), NewProp_bHasTarget_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_TicksSinceDecision = { "TicksSinceDecision", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTScenarioBehaviorFragment, TicksSinceDecision), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TicksSinceDecision_MetaData), NewProp_TicksSinceDecision_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Phase_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Phase,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DrivenNeed_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DrivenNeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bHasTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TicksSinceDecision,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTScenarioBehaviorFragment Property Definitions *******************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTScenarioBehaviorFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTScenarioBehaviorFragment>(),
	alignof(FNLTScenarioBehaviorFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTScenarioBehaviorFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTScenarioBehaviorFragment ****************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioFragments_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ENLTScenarioMovementPhase, TEXT("ENLTScenarioMovementPhase"), &ZRIE_ENLTScenarioMovementPhase, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2165677883U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment, Z_Construct_UScriptStruct_FNLTScenarioNeedsFragment_Statics::NewStructOps, TEXT("NLTScenarioNeedsFragment"),&Z_Registration_Info_UScriptStruct_FNLTScenarioNeedsFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTScenarioNeedsFragment), 2974581305U) },
		{ Z_Construct_UScriptStruct_FNLTScenarioConfigFragment, Z_Construct_UScriptStruct_FNLTScenarioConfigFragment_Statics::NewStructOps, TEXT("NLTScenarioConfigFragment"),&Z_Registration_Info_UScriptStruct_FNLTScenarioConfigFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTScenarioConfigFragment), 3544579837U) },
		{ Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment, Z_Construct_UScriptStruct_FNLTScenarioBehaviorFragment_Statics::NewStructOps, TEXT("NLTScenarioBehaviorFragment"),&Z_Registration_Info_UScriptStruct_FNLTScenarioBehaviorFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTScenarioBehaviorFragment), 1152300306U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_Demo_NLTDemoScenarioFragments_h__Script_WorldEngine_cc1ff20ec56d8cb4b9290d6e4f5e137601786ed0{
	TEXT("/Script/WorldEngine"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
