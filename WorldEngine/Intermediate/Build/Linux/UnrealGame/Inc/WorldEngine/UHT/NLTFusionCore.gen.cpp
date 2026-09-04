// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Core/NLTFusionCore.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTFusionCore() {}

// ********** Begin Cross Module References ********************************************************
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentIntent(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentRole(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ESimulationMode(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Enum ENLTAgentRole *************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTAgentRole_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTAgentRole>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTAgentRole(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Advocate.DisplayName", "Advocate" },
		{ "Advocate.Name", "ENLTAgentRole::Advocate" },
		{ "Aide.DisplayName", "Aide" },
		{ "Aide.Name", "ENLTAgentRole::Aide" },
		{ "Avatar.DisplayName", "Avatar" },
		{ "Avatar.Name", "ENLTAgentRole::Avatar" },
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Core/NLTFusionCore.h" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "ENLTAgentRole::None" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTAgentRole::None", (int64)ENLTAgentRole::None },
		{ "ENLTAgentRole::Avatar", (int64)ENLTAgentRole::Avatar },
		{ "ENLTAgentRole::Aide", (int64)ENLTAgentRole::Aide },
		{ "ENLTAgentRole::Advocate", (int64)ENLTAgentRole::Advocate },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTAgentRole",
	"ENLTAgentRole",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTAgentRole;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentRole(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTAgentRole.OuterSingleton)
		{
			ZRIE_ENLTAgentRole.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTAgentRole, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTAgentRole"));
		}
		return ZRIE_ENLTAgentRole.OuterSingleton;
	}
	if (!ZRIE_ENLTAgentRole.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTAgentRole.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTAgentRole.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTAgentRole ***************************************************************

// ********** Begin Enum ESimulationMode ***********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ESimulationMode_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ESimulationMode>()
{
	return Z_Construct_UEnum_WorldEngine_ESimulationMode(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "DeterministicTest.DisplayName", "DeterministicTest" },
		{ "DeterministicTest.Name", "ESimulationMode::DeterministicTest" },
		{ "FastForward.DisplayName", "FastForward" },
		{ "FastForward.Name", "ESimulationMode::FastForward" },
		{ "Headless.DisplayName", "Headless" },
		{ "Headless.Name", "ESimulationMode::Headless" },
		{ "ModuleRelativePath", "Public/Core/NLTFusionCore.h" },
		{ "Paused.DisplayName", "Paused" },
		{ "Paused.Name", "ESimulationMode::Paused" },
		{ "Realtime.DisplayName", "Realtime" },
		{ "Realtime.Name", "ESimulationMode::Realtime" },
		{ "Replay.DisplayName", "Replay" },
		{ "Replay.Name", "ESimulationMode::Replay" },
		{ "SlowMotion.DisplayName", "SlowMotion" },
		{ "SlowMotion.Name", "ESimulationMode::SlowMotion" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ESimulationMode::Realtime", (int64)ESimulationMode::Realtime },
		{ "ESimulationMode::Paused", (int64)ESimulationMode::Paused },
		{ "ESimulationMode::FastForward", (int64)ESimulationMode::FastForward },
		{ "ESimulationMode::SlowMotion", (int64)ESimulationMode::SlowMotion },
		{ "ESimulationMode::Headless", (int64)ESimulationMode::Headless },
		{ "ESimulationMode::Replay", (int64)ESimulationMode::Replay },
		{ "ESimulationMode::DeterministicTest", (int64)ESimulationMode::DeterministicTest },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ESimulationMode",
	"ESimulationMode",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ESimulationMode;
UEnum* Z_Construct_UEnum_WorldEngine_ESimulationMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ESimulationMode.OuterSingleton)
		{
			ZRIE_ESimulationMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ESimulationMode, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ESimulationMode"));
		}
		return ZRIE_ESimulationMode.OuterSingleton;
	}
	if (!ZRIE_ESimulationMode.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ESimulationMode.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ESimulationMode.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ESimulationMode *************************************************************

// ********** Begin Enum ENLTAgentIntent ***********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTAgentIntent_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTAgentIntent>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTAgentIntent(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Coached.DisplayName", "Coached" },
		{ "Coached.Name", "ENLTAgentIntent::Coached" },
		{ "Drifting.DisplayName", "Drifting" },
		{ "Drifting.Name", "ENLTAgentIntent::Drifting" },
		{ "FindQuietPlace.DisplayName", "FindQuietPlace" },
		{ "FindQuietPlace.Name", "ENLTAgentIntent::FindQuietPlace" },
		{ "Hyperfocus.DisplayName", "Hyperfocus" },
		{ "Hyperfocus.Name", "ENLTAgentIntent::Hyperfocus" },
		{ "Idle.DisplayName", "Idle" },
		{ "Idle.Name", "ENLTAgentIntent::Idle" },
		{ "Interact.DisplayName", "Interact" },
		{ "Interact.Name", "ENLTAgentIntent::Interact" },
		{ "ModuleRelativePath", "Public/Core/NLTFusionCore.h" },
		{ "MoveToLocation.DisplayName", "MoveToLocation" },
		{ "MoveToLocation.Name", "ENLTAgentIntent::MoveToLocation" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "ENLTAgentIntent::None" },
		{ "Overwhelmed.DisplayName", "Overwhelmed" },
		{ "Overwhelmed.Name", "ENLTAgentIntent::Overwhelmed" },
		{ "Rest.DisplayName", "Rest" },
		{ "Rest.Name", "ENLTAgentIntent::Rest" },
		{ "Socialize.DisplayName", "Socialize" },
		{ "Socialize.Name", "ENLTAgentIntent::Socialize" },
		{ "Study.DisplayName", "Study" },
		{ "Study.Name", "ENLTAgentIntent::Study" },
		{ "Work.DisplayName", "Work" },
		{ "Work.Name", "ENLTAgentIntent::Work" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTAgentIntent::None", (int64)ENLTAgentIntent::None },
		{ "ENLTAgentIntent::Idle", (int64)ENLTAgentIntent::Idle },
		{ "ENLTAgentIntent::FindQuietPlace", (int64)ENLTAgentIntent::FindQuietPlace },
		{ "ENLTAgentIntent::Work", (int64)ENLTAgentIntent::Work },
		{ "ENLTAgentIntent::Socialize", (int64)ENLTAgentIntent::Socialize },
		{ "ENLTAgentIntent::Rest", (int64)ENLTAgentIntent::Rest },
		{ "ENLTAgentIntent::Study", (int64)ENLTAgentIntent::Study },
		{ "ENLTAgentIntent::MoveToLocation", (int64)ENLTAgentIntent::MoveToLocation },
		{ "ENLTAgentIntent::Interact", (int64)ENLTAgentIntent::Interact },
		{ "ENLTAgentIntent::Coached", (int64)ENLTAgentIntent::Coached },
		{ "ENLTAgentIntent::Overwhelmed", (int64)ENLTAgentIntent::Overwhelmed },
		{ "ENLTAgentIntent::Drifting", (int64)ENLTAgentIntent::Drifting },
		{ "ENLTAgentIntent::Hyperfocus", (int64)ENLTAgentIntent::Hyperfocus },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTAgentIntent",
	"ENLTAgentIntent",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTAgentIntent;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentIntent(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTAgentIntent.OuterSingleton)
		{
			ZRIE_ENLTAgentIntent.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTAgentIntent, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTAgentIntent"));
		}
		return ZRIE_ENLTAgentIntent.OuterSingleton;
	}
	if (!ZRIE_ENLTAgentIntent.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTAgentIntent.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTAgentIntent.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTAgentIntent *************************************************************

// ********** Begin Enum ENLTAgentNeed *************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UEnum_WorldEngine_ENLTAgentNeed_Statics
template<> WORLDENGINE_NON_ATTRIBUTED_API UEnum* StaticEnum<ENLTAgentNeed>()
{
	return Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase::Outer);
}
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
		{ "Food.DisplayName", "Food" },
		{ "Food.Name", "ENLTAgentNeed::Food" },
		{ "ModuleRelativePath", "Public/Core/NLTFusionCore.h" },
		{ "Movement.DisplayName", "Movement" },
		{ "Movement.Name", "ENLTAgentNeed::Movement" },
		{ "None.DisplayName", "None" },
		{ "None.Name", "ENLTAgentNeed::None" },
		{ "Privacy.DisplayName", "Privacy" },
		{ "Privacy.Name", "ENLTAgentNeed::Privacy" },
		{ "Quiet.DisplayName", "Quiet" },
		{ "Quiet.Name", "ENLTAgentNeed::Quiet" },
		{ "Rest.DisplayName", "Rest" },
		{ "Rest.Name", "ENLTAgentNeed::Rest" },
		{ "Social.DisplayName", "Social" },
		{ "Social.Name", "ENLTAgentNeed::Social" },
		{ "Stimulation.DisplayName", "Stimulation" },
		{ "Stimulation.Name", "ENLTAgentNeed::Stimulation" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ENLTAgentNeed::None", (int64)ENLTAgentNeed::None },
		{ "ENLTAgentNeed::Quiet", (int64)ENLTAgentNeed::Quiet },
		{ "ENLTAgentNeed::Rest", (int64)ENLTAgentNeed::Rest },
		{ "ENLTAgentNeed::Social", (int64)ENLTAgentNeed::Social },
		{ "ENLTAgentNeed::Stimulation", (int64)ENLTAgentNeed::Stimulation },
		{ "ENLTAgentNeed::Food", (int64)ENLTAgentNeed::Food },
		{ "ENLTAgentNeed::Movement", (int64)ENLTAgentNeed::Movement },
		{ "ENLTAgentNeed::Privacy", (int64)ENLTAgentNeed::Privacy },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct UHT_STATICS 
const UECodeGen_Private::FEnumParams UHT_STATICS::EnumParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	"ENLTAgentNeed",
	"ENLTAgentNeed",
	UHT_STATICS::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(UHT_STATICS::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	(uint8)UEnum::EUnderlyingType::uint8,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FEnumRegistrationInfo ZRIE_ENLTAgentNeed;
UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!ZRIE_ENLTAgentNeed.OuterSingleton)
		{
			ZRIE_ENLTAgentNeed.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("ENLTAgentNeed"));
		}
		return ZRIE_ENLTAgentNeed.OuterSingleton;
	}
	if (!ZRIE_ENLTAgentNeed.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(ZRIE_ENLTAgentNeed.InnerSingleton, UHT_STATICS::EnumParams);
	}
	return ZRIE_ENLTAgentNeed.InnerSingleton;
}
#undef UHT_STATICS
// ********** End Enum ENLTAgentNeed ***************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTFusionCore_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ Z_Construct_UEnum_WorldEngine_ENLTAgentRole, TEXT("ENLTAgentRole"), &ZRIE_ENLTAgentRole, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2707217229U) },
		{ Z_Construct_UEnum_WorldEngine_ESimulationMode, TEXT("ESimulationMode"), &ZRIE_ESimulationMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2820770846U) },
		{ Z_Construct_UEnum_WorldEngine_ENLTAgentIntent, TEXT("ENLTAgentIntent"), &ZRIE_ENLTAgentIntent, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1359842856U) },
		{ Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, TEXT("ENLTAgentNeed"), &ZRIE_ENLTAgentNeed, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 878431089U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Core_NLTFusionCore_h__Script_WorldEngine_b1da076c6cb7100a26eebf44038916ee42ceaee8{
	TEXT("/Script/WorldEngine"),
	nullptr, 0,
	nullptr, 0,
	UHT_STATICS::EnumInfo, UE_ARRAY_COUNT(UHT_STATICS::EnumInfo),
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
