// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Roles/NLTFusionRoleManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTFusionRoleManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UWorldSubsystem(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAdvocate(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTFusionPair(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTFusionRoleManager(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTFusionRoleManager(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum ENLTFusionRoleState *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTFusionRoleState>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Active.DisplayName", "Active" },
		{ "Active.Name", "ENLTFusionRoleState::Active" },
		{ "BlueprintType", "true" },
		{ "Coaching.DisplayName", "Coaching" },
		{ "Coaching.Name", "ENLTFusionRoleState::Coaching" },
		{ "Fused.DisplayName", "Fused" },
		{ "Fused.Name", "ENLTFusionRoleState::Fused" },
		{ "Inactive.DisplayName", "Inactive" },
		{ "Inactive.Name", "ENLTFusionRoleState::Inactive" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
		{ "Monitoring.DisplayName", "Monitoring" },
		{ "Monitoring.Name", "ENLTFusionRoleState::Monitoring" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTFusionRoleState::Inactive", (int64)ENLTFusionRoleState::Inactive },
		{ "ENLTFusionRoleState::Active", (int64)ENLTFusionRoleState::Active },
		{ "ENLTFusionRoleState::Coaching", (int64)ENLTFusionRoleState::Coaching },
		{ "ENLTFusionRoleState::Monitoring", (int64)ENLTFusionRoleState::Monitoring },
		{ "ENLTFusionRoleState::Fused", (int64)ENLTFusionRoleState::Fused },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTFusionRoleState",
	"ENLTFusionRoleState",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTFusionRoleState;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTFusionRoleState.OuterSingleton)
		{
			ZRIE_ENLTFusionRoleState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTFusionRoleState"));
		}
		return ZRIE_ENLTFusionRoleState.OuterSingleton;
	}
	if (!ZRIE_ENLTFusionRoleState.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTFusionRoleState.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTFusionRoleState.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTFusionRoleState *********************************************************

// ********** Begin ScriptStruct FNLTFusionPair ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTFusionPair_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTFusionPair>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTFusionPair); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PairId_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvatarId_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AideId_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BondStrength_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FusionReadiness_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvatarState_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AideState_MetaData[] = {
		{ "Category", "NLTFusionPair" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTFusionPair constinit property declarations ********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_PairId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AvatarId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AideId;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BondStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FusionReadiness;
	static const UECodeGen_Private::FBytePropertyParams NewProp_AvatarState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_AvatarState;
	static const UECodeGen_Private::FBytePropertyParams NewProp_AideState_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_AideState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTFusionPair constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTFusionPair>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTFusionPair Property Definitions *******************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PairId = { "PairId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, PairId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PairId_MetaData), NewProp_PairId_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AvatarId = { "AvatarId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, AvatarId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvatarId_MetaData), NewProp_AvatarId_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AideId = { "AideId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, AideId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AideId_MetaData), NewProp_AideId_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BondStrength = { "BondStrength", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, BondStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BondStrength_MetaData), NewProp_BondStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FusionReadiness = { "FusionReadiness", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, FusionReadiness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FusionReadiness_MetaData), NewProp_FusionReadiness_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_AvatarState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_AvatarState = { "AvatarState", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, AvatarState), Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvatarState_MetaData), NewProp_AvatarState_MetaData) }; // d5bdbb10731c45d8e6dcf3d6265b950e09a8c837
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_AideState_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_AideState = { "AideState", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTFusionPair, AideState), Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AideState_MetaData), NewProp_AideState_MetaData) }; // d5bdbb10731c45d8e6dcf3d6265b950e09a8c837
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PairId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BondStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FusionReadiness,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideState_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTFusionPair Property Definitions *********************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTFusionPair",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTFusionPair>(),
	alignof(FNLTFusionPair),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTFusionPair;
UScriptStruct* Z_Construct_UScriptStruct_FNLTFusionPair(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTFusionPair.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTFusionPair.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTFusionPair, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTFusionPair"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTFusionPair.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTFusionPair.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTFusionPair.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTFusionPair.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTFusionPair ******************************************************

// ********** Begin ScriptStruct FNLTAdvocate ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAdvocate_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAdvocate>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAdvocate); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AdvocateId_MetaData[] = {
		{ "Category", "NLTAdvocate" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MonitoredPairs_MetaData[] = {
		{ "Category", "NLTAdvocate" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxMonitoringCapacity_MetaData[] = {
		{ "Category", "NLTAdvocate" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_State_MetaData[] = {
		{ "Category", "NLTAdvocate" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAdvocate constinit property declarations **********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AdvocateId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_MonitoredPairs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MonitoredPairs;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxMonitoringCapacity;
	static const UECodeGen_Private::FBytePropertyParams NewProp_State_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_State;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAdvocate constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAdvocate>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FNLTAdvocate Property Definitions *********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AdvocateId = { "AdvocateId", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAdvocate, AdvocateId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AdvocateId_MetaData), NewProp_AdvocateId_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_MonitoredPairs_Inner = { "MonitoredPairs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_MonitoredPairs = { "MonitoredPairs", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAdvocate, MonitoredPairs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MonitoredPairs_MetaData), NewProp_MonitoredPairs_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxMonitoringCapacity = { "MaxMonitoringCapacity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAdvocate, MaxMonitoringCapacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxMonitoringCapacity_MetaData), NewProp_MaxMonitoringCapacity_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_State_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_State = { "State", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAdvocate, State), Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_State_MetaData), NewProp_State_MetaData) }; // d5bdbb10731c45d8e6dcf3d6265b950e09a8c837
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AdvocateId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MonitoredPairs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MonitoredPairs,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxMonitoringCapacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_State_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_State,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAdvocate Property Definitions ***********************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"NLTAdvocate",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAdvocate>(),
	alignof(FNLTAdvocate),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAdvocate;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAdvocate(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAdvocate.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAdvocate.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAdvocate, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAdvocate"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAdvocate.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAdvocate.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAdvocate.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAdvocate.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAdvocate ********************************************************

// ********** Begin Class UNLTFusionRoleManager Function AssignPairToAdvocate **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_AssignPairToAdvocate_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventAssignPairToAdvocate_Parms
	{
		FName PairId;
		FName AdvocateId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function AssignPairToAdvocate constinit property declarations ******************
	static const UECodeGen_Private::FNamePropertyParams NewProp_PairId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AdvocateId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function AssignPairToAdvocate constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function AssignPairToAdvocate Property Definitions *****************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PairId = { "PairId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventAssignPairToAdvocate_Parms, PairId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AdvocateId = { "AdvocateId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventAssignPairToAdvocate_Parms, AdvocateId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PairId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AdvocateId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function AssignPairToAdvocate Property Definitions *******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "AssignPairToAdvocate", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventAssignPairToAdvocate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventAssignPairToAdvocate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_AssignPairToAdvocate(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execAssignPairToAdvocate)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_PairId);
	P_GET_PROPERTY(FNameProperty,Z_Param_AdvocateId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AssignPairToAdvocate(Z_Param_PairId,Z_Param_AdvocateId);
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function AssignPairToAdvocate ************************

// ********** Begin Class UNLTFusionRoleManager Function CreateAdvocate ****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_CreateAdvocate_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventCreateAdvocate_Parms
	{
		FName AdvocateId;
		FName ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreateAdvocate constinit property declarations ************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AdvocateId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreateAdvocate constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreateAdvocate Property Definitions ***********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AdvocateId = { "AdvocateId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventCreateAdvocate_Parms, AdvocateId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventCreateAdvocate_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AdvocateId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function CreateAdvocate Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "CreateAdvocate", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventCreateAdvocate_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventCreateAdvocate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_CreateAdvocate(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execCreateAdvocate)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_AdvocateId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FName*)Z_Param__Result=P_THIS->CreateAdvocate(Z_Param_AdvocateId);
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function CreateAdvocate ******************************

// ********** Begin Class UNLTFusionRoleManager Function CreatePair ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_CreatePair_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventCreatePair_Parms
	{
		FName AvatarId;
		FName AideId;
		FName ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function CreatePair constinit property declarations ****************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AvatarId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_AideId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function CreatePair constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function CreatePair Property Definitions ***************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AvatarId = { "AvatarId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventCreatePair_Parms, AvatarId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AideId = { "AideId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventCreatePair_Parms, AideId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventCreatePair_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function CreatePair Property Definitions *****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "CreatePair", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventCreatePair_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventCreatePair_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_CreatePair(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execCreatePair)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_AvatarId);
	P_GET_PROPERTY(FNameProperty,Z_Param_AideId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FName*)Z_Param__Result=P_THIS->CreatePair(Z_Param_AvatarId,Z_Param_AideId);
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function CreatePair **********************************

// ********** Begin Class UNLTFusionRoleManager Function DestroyPair *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_DestroyPair_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventDestroyPair_Parms
	{
		FName PairId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function DestroyPair constinit property declarations ***************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_PairId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DestroyPair constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DestroyPair Property Definitions **************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PairId = { "PairId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventDestroyPair_Parms, PairId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PairId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DestroyPair Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "DestroyPair", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventDestroyPair_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventDestroyPair_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_DestroyPair(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execDestroyPair)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_PairId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DestroyPair(Z_Param_PairId);
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function DestroyPair *********************************

// ********** Begin Class UNLTFusionRoleManager Function GetAdvocateCount **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_GetAdvocateCount_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventGetAdvocateCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetAdvocateCount constinit property declarations **********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAdvocateCount constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAdvocateCount Property Definitions *********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventGetAdvocateCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAdvocateCount Property Definitions ***********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "GetAdvocateCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventGetAdvocateCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventGetAdvocateCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_GetAdvocateCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execGetAdvocateCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetAdvocateCount();
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function GetAdvocateCount ****************************

// ********** Begin Class UNLTFusionRoleManager Function GetPair ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_GetPair_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventGetPair_Parms
	{
		FName PairId;
		FNLTFusionPair OutPair;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPair constinit property declarations *******************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_PairId;
	static const UECodeGen_Private::FStructPropertyParams NewProp_OutPair;
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((NLTFusionRoleManager_eventGetPair_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPair constinit property declarations *********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPair Property Definitions ******************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PairId = { "PairId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventGetPair_Parms, PairId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_OutPair = { "OutPair", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventGetPair_Parms, OutPair), Z_Construct_UScriptStruct_FNLTFusionPair, METADATA_PARAMS(0, nullptr) }; // cd03fb197c6b996a6c56f4aa5e15ce1a6202e767
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(NLTFusionRoleManager_eventGetPair_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PairId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OutPair,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPair Property Definitions ********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "GetPair", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventGetPair_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventGetPair_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_GetPair(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execGetPair)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_PairId);
	P_GET_STRUCT_REF(FNLTFusionPair,Z_Param_Out_OutPair);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->GetPair(Z_Param_PairId,Z_Param_Out_OutPair);
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function GetPair *************************************

// ********** Begin Class UNLTFusionRoleManager Function GetPairCount ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_GetPairCount_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventGetPairCount_Parms
	{
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPairCount constinit property declarations **************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPairCount constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPairCount Property Definitions *************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventGetPairCount_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPairCount Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "GetPairCount", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventGetPairCount_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventGetPairCount_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_GetPairCount(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execGetPairCount)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetPairCount();
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function GetPairCount ********************************

// ********** Begin Class UNLTFusionRoleManager Function Tick **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UNLTFusionRoleManager_Tick_Statics
struct UHT_STATICS
{
	struct NLTFusionRoleManager_eventTick_Parms
	{
		float DeltaTime;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Roles" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function Tick constinit property declarations **********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeltaTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Tick constinit property declarations ************************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Tick Property Definitions *********************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeltaTime = { "DeltaTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(NLTFusionRoleManager_eventTick_Parms, DeltaTime), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeltaTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function Tick Property Definitions ***********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UNLTFusionRoleManager, nullptr, "Tick", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTFusionRoleManager_eventTick_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTFusionRoleManager_eventTick_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UNLTFusionRoleManager_Tick(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UNLTFusionRoleManager::execTick)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_DeltaTime);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Tick(Z_Param_DeltaTime);
	P_NATIVE_END;
}
// ********** End Class UNLTFusionRoleManager Function Tick ****************************************

// ********** Begin Class UNLTFusionRoleManager ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UNLTFusionRoleManager_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Roles/NLTFusionRoleManager.h" },
		{ "ModuleRelativePath", "Public/Roles/NLTFusionRoleManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNLTFusionRoleManager constinit property declarations ********************
// ********** End Class UNLTFusionRoleManager constinit property declarations **********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("AssignPairToAdvocate"), .Pointer = &UNLTFusionRoleManager::execAssignPairToAdvocate },
		{ .NameUTF8 = UTF8TEXT("CreateAdvocate"), .Pointer = &UNLTFusionRoleManager::execCreateAdvocate },
		{ .NameUTF8 = UTF8TEXT("CreatePair"), .Pointer = &UNLTFusionRoleManager::execCreatePair },
		{ .NameUTF8 = UTF8TEXT("DestroyPair"), .Pointer = &UNLTFusionRoleManager::execDestroyPair },
		{ .NameUTF8 = UTF8TEXT("GetAdvocateCount"), .Pointer = &UNLTFusionRoleManager::execGetAdvocateCount },
		{ .NameUTF8 = UTF8TEXT("GetPair"), .Pointer = &UNLTFusionRoleManager::execGetPair },
		{ .NameUTF8 = UTF8TEXT("GetPairCount"), .Pointer = &UNLTFusionRoleManager::execGetPairCount },
		{ .NameUTF8 = UTF8TEXT("Tick"), .Pointer = &UNLTFusionRoleManager::execTick },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_AssignPairToAdvocate, "AssignPairToAdvocate" }, // 9ce3eda3315575db59484eb638f625df1fc964a3
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_CreateAdvocate, "CreateAdvocate" }, // 6412348f0e22768d5948be1ae017ac50c73d5acb
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_CreatePair, "CreatePair" }, // 1eb0f2ac00f4aafea0c10b2c1470abadbe556989
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_DestroyPair, "DestroyPair" }, // e42ea113bc1af69c3476e24390539024cef0062a
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_GetAdvocateCount, "GetAdvocateCount" }, // 6e14a74a29e3dc6b13421bdee8c3c1b4411e1ad9
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_GetPair, "GetPair" }, // 84246c9d9f23283c5517018310a8db6c01a3bd96
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_GetPairCount, "GetPairCount" }, // 7c1b7aaf95fd9bfc70c944b3a5649070f7401600
		{ &Z_Construct_UFunction_UNLTFusionRoleManager_Tick, "Tick" }, // 86a7376bc44f9f96a24656386927410465af614d
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLTFusionRoleManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UWorldSubsystem,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UNLTFusionRoleManager,
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
static void UNLTFusionRoleManager_StaticRegisterNativesUNLTFusionRoleManager()
{
	UClass* Class = UNLTFusionRoleManager::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UNLTFusionRoleManager;
UClass* Z_Construct_UClass_UNLTFusionRoleManager(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UNLTFusionRoleManager;
		if (!Z_Registration_Info_UClass_UNLTFusionRoleManager.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTFusionRoleManager"),
				Z_Registration_Info_UClass_UNLTFusionRoleManager.InnerSingleton,
				UNLTFusionRoleManager_StaticRegisterNativesUNLTFusionRoleManager,
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
		return Z_Registration_Info_UClass_UNLTFusionRoleManager.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UNLTFusionRoleManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLTFusionRoleManager.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLTFusionRoleManager.OuterSingleton;
}
#undef UHT_STATICS
UNLTFusionRoleManager::UNLTFusionRoleManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNLTFusionRoleManager);
UNLTFusionRoleManager::~UNLTFusionRoleManager() {}
// ********** End Class UNLTFusionRoleManager ******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ENLTFusionRoleState, TEXT("ENLTFusionRoleState"), &ZRIE_ENLTFusionRoleState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3585981200U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTFusionPair, Z_Construct_UScriptStruct_FNLTFusionPair_Statics::NewStructOps, TEXT("NLTFusionPair"),&Z_Registration_Info_UScriptStruct_FNLTFusionPair, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTFusionPair), 3439590169U) },
		{ Z_Construct_UScriptStruct_FNLTAdvocate, Z_Construct_UScriptStruct_FNLTAdvocate_Statics::NewStructOps, TEXT("NLTAdvocate"),&Z_Registration_Info_UScriptStruct_FNLTAdvocate, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAdvocate), 342001586U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLTFusionRoleManager, TEXT("UNLTFusionRoleManager"), &Z_Registration_Info_UClass_UNLTFusionRoleManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLTFusionRoleManager), 3301930144U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Roles_NLTFusionRoleManager_h__Script_WorldEngine_76f4fedf70ca3a86c83ebc1dca3d1776c2bf8b29{
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
