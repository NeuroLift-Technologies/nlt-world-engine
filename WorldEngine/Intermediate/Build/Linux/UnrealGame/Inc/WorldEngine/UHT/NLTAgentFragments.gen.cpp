// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/NLTAgentFragments.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTAgentFragments() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FIntVector(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
MASSCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMassFragment(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentIntent(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentNeed(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_ENLTAgentRole(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentBehaviorFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentCognitiveFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentIdentityFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentIntentFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentLocationFragment(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentNeedsFragment(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FNLTAgentIdentityFragment *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentIdentityFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentIdentityFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentIdentityFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProfileId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TeamId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsSelected_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VisualCustomizationId_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentIdentityFragment constinit property declarations *********
	static const UECodeGen_Private::FNamePropertyParams NewProp_AgentId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Role;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ProfileId;
	static const UECodeGen_Private::FNamePropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FIntPropertyParams NewProp_TeamId;
	static void NewProp_bIsSelected_SetBit(void* Obj)
	{
		((FNLTAgentIdentityFragment*)Obj)->bIsSelected = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSelected;
	static const UECodeGen_Private::FIntPropertyParams NewProp_VisualCustomizationId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentIdentityFragment constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentIdentityFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTAgentIdentityFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTAgentIdentityFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTAgentIdentityFragment Property Definitions ********************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AgentId = { "AgentId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIdentityFragment, AgentId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentId_MetaData), NewProp_AgentId_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIdentityFragment, Role), Z_Construct_UEnum_WorldEngine_ENLTAgentRole, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) }; // a15cdb4d293d5445794fbe0b12a625f42b91da5d
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ProfileId = { "ProfileId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIdentityFragment, ProfileId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProfileId_MetaData), NewProp_ProfileId_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIdentityFragment, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_TeamId = { "TeamId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIdentityFragment, TeamId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TeamId_MetaData), NewProp_TeamId_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIsSelected = { "bIsSelected", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FNLTAgentIdentityFragment), &UHT_STATICS::NewProp_bIsSelected_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsSelected_MetaData), NewProp_bIsSelected_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_VisualCustomizationId = { "VisualCustomizationId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIdentityFragment, VisualCustomizationId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VisualCustomizationId_MetaData), NewProp_VisualCustomizationId_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ProfileId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TeamId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIsSelected,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_VisualCustomizationId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentIdentityFragment Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTAgentIdentityFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentIdentityFragment>(),
	alignof(FNLTAgentIdentityFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentIdentityFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentIdentityFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentIdentityFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentIdentityFragment *******************************************

// ********** Begin ScriptStruct FNLTAgentLocationFragment *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentLocationFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentLocationFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentLocationFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Position_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Heading_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPosition_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorldCell_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsMoving_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentLocationFragment constinit property declarations *********
	static const UECodeGen_Private::FStructPropertyParams NewProp_Position;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Heading;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetPosition;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorldCell;
	static void NewProp_bIsMoving_SetBit(void* Obj)
	{
		((FNLTAgentLocationFragment*)Obj)->bIsMoving = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsMoving;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentLocationFragment constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentLocationFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTAgentLocationFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTAgentLocationFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTAgentLocationFragment Property Definitions ********************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Position = { "Position", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentLocationFragment, Position), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Position_MetaData), NewProp_Position_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Heading = { "Heading", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentLocationFragment, Heading), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Heading_MetaData), NewProp_Heading_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentLocationFragment, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TargetPosition = { "TargetPosition", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentLocationFragment, TargetPosition), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPosition_MetaData), NewProp_TargetPosition_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_WorldCell = { "WorldCell", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentLocationFragment, WorldCell), Z_Construct_UScriptStruct_FIntVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorldCell_MetaData), NewProp_WorldCell_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIsMoving = { "bIsMoving", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FNLTAgentLocationFragment), &UHT_STATICS::NewProp_bIsMoving_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsMoving_MetaData), NewProp_bIsMoving_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Position,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Heading,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WorldCell,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIsMoving,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentLocationFragment Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTAgentLocationFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentLocationFragment>(),
	alignof(FNLTAgentLocationFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentLocationFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentLocationFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentLocationFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentLocationFragment *******************************************

// ********** Begin ScriptStruct FNLTAgentIntentFragment *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentIntentFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentIntentFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentIntentFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intent_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Priority_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceTick_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetLocation_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetTag_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentIntentFragment constinit property declarations ***********
	static const UECodeGen_Private::FBytePropertyParams NewProp_Intent_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Intent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Priority;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SourceTick;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetLocation;
	static const UECodeGen_Private::FNamePropertyParams NewProp_TargetTag;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentIntentFragment constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentIntentFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTAgentIntentFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTAgentIntentFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTAgentIntentFragment Property Definitions **********************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Intent_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Intent = { "Intent", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIntentFragment, Intent), Z_Construct_UEnum_WorldEngine_ENLTAgentIntent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intent_MetaData), NewProp_Intent_MetaData) }; // 510d8e28c4d53ed4cb1edb895bfe266a65787360
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Priority = { "Priority", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIntentFragment, Priority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Priority_MetaData), NewProp_Priority_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SourceTick = { "SourceTick", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIntentFragment, SourceTick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceTick_MetaData), NewProp_SourceTick_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TargetLocation = { "TargetLocation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIntentFragment, TargetLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetLocation_MetaData), NewProp_TargetLocation_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_TargetTag = { "TargetTag", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentIntentFragment, TargetTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetTag_MetaData), NewProp_TargetTag_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Intent_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Intent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Priority,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SourceTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetTag,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentIntentFragment Property Definitions ************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTAgentIntentFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentIntentFragment>(),
	alignof(FNLTAgentIntentFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentIntentFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentIntentFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentIntentFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentIntentFragment *********************************************

// ********** Begin ScriptStruct FNLTAgentCognitiveFragment ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentCognitiveFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentCognitiveFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentCognitiveFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Focus_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CognitiveLoad_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stress_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Burnout_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Independence_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FusionReady_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuccessRate_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmotionalState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentCognitiveFragment constinit property declarations ********
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Focus;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CognitiveLoad;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stress;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Burnout;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Independence;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FusionReady;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SuccessRate;
	static const UECodeGen_Private::FNamePropertyParams NewProp_EmotionalState;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentCognitiveFragment constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentCognitiveFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTAgentCognitiveFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTAgentCognitiveFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTAgentCognitiveFragment Property Definitions *******************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Focus = { "Focus", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, Focus), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Focus_MetaData), NewProp_Focus_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CognitiveLoad = { "CognitiveLoad", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, CognitiveLoad), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CognitiveLoad_MetaData), NewProp_CognitiveLoad_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Stress = { "Stress", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, Stress), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stress_MetaData), NewProp_Stress_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Burnout = { "Burnout", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, Burnout), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Burnout_MetaData), NewProp_Burnout_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Independence = { "Independence", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, Independence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Independence_MetaData), NewProp_Independence_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FusionReady = { "FusionReady", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, FusionReady), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FusionReady_MetaData), NewProp_FusionReady_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SuccessRate = { "SuccessRate", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, SuccessRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuccessRate_MetaData), NewProp_SuccessRate_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_EmotionalState = { "EmotionalState", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentCognitiveFragment, EmotionalState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmotionalState_MetaData), NewProp_EmotionalState_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Focus,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CognitiveLoad,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Stress,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Burnout,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Independence,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FusionReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SuccessRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EmotionalState,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentCognitiveFragment Property Definitions *********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTAgentCognitiveFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentCognitiveFragment>(),
	alignof(FNLTAgentCognitiveFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentCognitiveFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentCognitiveFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentCognitiveFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentCognitiveFragment ******************************************

// ********** Begin ScriptStruct FNLTAgentNeedsFragment ********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentNeedsFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentNeedsFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentNeedsFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryNeed_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryNeed_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Urgency_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentNeedsFragment constinit property declarations ************
	static const UECodeGen_Private::FBytePropertyParams NewProp_PrimaryNeed_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PrimaryNeed;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SecondaryNeed_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SecondaryNeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Urgency;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentNeedsFragment constinit property declarations **************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentNeedsFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTAgentNeedsFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTAgentNeedsFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTAgentNeedsFragment Property Definitions ***********************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_PrimaryNeed_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_PrimaryNeed = { "PrimaryNeed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentNeedsFragment, PrimaryNeed), Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryNeed_MetaData), NewProp_PrimaryNeed_MetaData) }; // 345bcb711db8b50a21de46ae83aa1b8526889732
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SecondaryNeed_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_SecondaryNeed = { "SecondaryNeed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentNeedsFragment, SecondaryNeed), Z_Construct_UEnum_WorldEngine_ENLTAgentNeed, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondaryNeed_MetaData), NewProp_SecondaryNeed_MetaData) }; // 345bcb711db8b50a21de46ae83aa1b8526889732
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Urgency = { "Urgency", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentNeedsFragment, Urgency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Urgency_MetaData), NewProp_Urgency_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PrimaryNeed_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PrimaryNeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SecondaryNeed_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SecondaryNeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Urgency,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentNeedsFragment Property Definitions *************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTAgentNeedsFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentNeedsFragment>(),
	alignof(FNLTAgentNeedsFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentNeedsFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentNeedsFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentNeedsFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentNeedsFragment **********************************************

// ********** Begin ScriptStruct FNLTAgentBehaviorFragment *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FNLTAgentBehaviorFragment_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FNLTAgentBehaviorFragment>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNLTAgentBehaviorFragment); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsExecutingBehavior_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentState_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BehaviorStartTick_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoachingCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/Agents/NLTAgentFragments.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNLTAgentBehaviorFragment constinit property declarations *********
	static void NewProp_bIsExecutingBehavior_SetBit(void* Obj)
	{
		((FNLTAgentBehaviorFragment*)Obj)->bIsExecutingBehavior = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsExecutingBehavior;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentState;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BehaviorStartTick;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CoachingCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNLTAgentBehaviorFragment constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLTAgentBehaviorFragment>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FNLTAgentBehaviorFragment>() == std::is_polymorphic<FMassFragment>(), "USTRUCT FNLTAgentBehaviorFragment cannot be polymorphic unless super FMassFragment is polymorphic");

// ********** Begin ScriptStruct FNLTAgentBehaviorFragment Property Definitions ********************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bIsExecutingBehavior = { "bIsExecutingBehavior", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FNLTAgentBehaviorFragment), &UHT_STATICS::NewProp_bIsExecutingBehavior_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsExecutingBehavior_MetaData), NewProp_bIsExecutingBehavior_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CurrentState = { "CurrentState", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentBehaviorFragment, CurrentState), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentState_MetaData), NewProp_CurrentState_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_BehaviorStartTick = { "BehaviorStartTick", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentBehaviorFragment, BehaviorStartTick), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BehaviorStartTick_MetaData), NewProp_BehaviorStartTick_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_CoachingCount = { "CoachingCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(FNLTAgentBehaviorFragment, CoachingCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoachingCount_MetaData), NewProp_CoachingCount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bIsExecutingBehavior,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentState,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BehaviorStartTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CoachingCount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FNLTAgentBehaviorFragment Property Definitions **********************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	Z_Construct_UScriptStruct_FMassFragment,
	&NewStructOps,
	"NLTAgentBehaviorFragment",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FNLTAgentBehaviorFragment>(),
	alignof(FNLTAgentBehaviorFragment),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment;
UScriptStruct* Z_Construct_UScriptStruct_FNLTAgentBehaviorFragment(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLTAgentBehaviorFragment, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("NLTAgentBehaviorFragment"));
		}
		return Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FNLTAgentBehaviorFragment *******************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentFragments_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FNLTAgentIdentityFragment, Z_Construct_UScriptStruct_FNLTAgentIdentityFragment_Statics::NewStructOps, TEXT("NLTAgentIdentityFragment"),&Z_Registration_Info_UScriptStruct_FNLTAgentIdentityFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentIdentityFragment), 14605255U) },
		{ Z_Construct_UScriptStruct_FNLTAgentLocationFragment, Z_Construct_UScriptStruct_FNLTAgentLocationFragment_Statics::NewStructOps, TEXT("NLTAgentLocationFragment"),&Z_Registration_Info_UScriptStruct_FNLTAgentLocationFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentLocationFragment), 1688518075U) },
		{ Z_Construct_UScriptStruct_FNLTAgentIntentFragment, Z_Construct_UScriptStruct_FNLTAgentIntentFragment_Statics::NewStructOps, TEXT("NLTAgentIntentFragment"),&Z_Registration_Info_UScriptStruct_FNLTAgentIntentFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentIntentFragment), 1135873412U) },
		{ Z_Construct_UScriptStruct_FNLTAgentCognitiveFragment, Z_Construct_UScriptStruct_FNLTAgentCognitiveFragment_Statics::NewStructOps, TEXT("NLTAgentCognitiveFragment"),&Z_Registration_Info_UScriptStruct_FNLTAgentCognitiveFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentCognitiveFragment), 2892575562U) },
		{ Z_Construct_UScriptStruct_FNLTAgentNeedsFragment, Z_Construct_UScriptStruct_FNLTAgentNeedsFragment_Statics::NewStructOps, TEXT("NLTAgentNeedsFragment"),&Z_Registration_Info_UScriptStruct_FNLTAgentNeedsFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentNeedsFragment), 1923170835U) },
		{ Z_Construct_UScriptStruct_FNLTAgentBehaviorFragment, Z_Construct_UScriptStruct_FNLTAgentBehaviorFragment_Statics::NewStructOps, TEXT("NLTAgentBehaviorFragment"),&Z_Registration_Info_UScriptStruct_FNLTAgentBehaviorFragment, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLTAgentBehaviorFragment), 714907525U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTAgentFragments_h__Script_WorldEngine_436423921e20ce8416b88035316de6b58a506859{
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
