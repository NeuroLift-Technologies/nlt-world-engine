// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Audio/SoundscapeDataAsset.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSoundscapeDataAsset() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UPrimaryDataAsset(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USoundAttenuation(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USoundWave(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FSoundscapeBedLayer(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_USoundscapeDataAsset(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_USoundscapeDataAsset(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FSoundscapeBedLayer ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FSoundscapeBedLayer_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FSoundscapeBedLayer>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FSoundscapeBedLayer); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Configuration for one soundscape bed layer.\n * Each layer is a looping ambient sound whose volume and pitch\n * are modulated by the scenario stress level (0..1).\n */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Configuration for one soundscape bed layer.\nEach layer is a looping ambient sound whose volume and pitch\nare modulated by the scenario stress level (0..1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundWave_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** The sound wave asset to play (looping). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "The sound wave asset to play (looping)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseVolume_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Base volume multiplier when stress = 0 (0..1). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Base volume multiplier when stress = 0 (0..1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxVolume_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Volume at maximum stress (0..1). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Volume at maximum stress (0..1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BasePitch_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMax", "2.0" },
		{ "ClampMin", "0.5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pitch multiplier at stress = 0. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pitch multiplier at stress = 0." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxPitch_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMax", "2.0" },
		{ "ClampMin", "0.5" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pitch multiplier at max stress. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pitch multiplier at max stress." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LocalOffset_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Local offset from the soundscape origin where this bed sits (cm). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Local offset from the soundscape origin where this bed sits (cm)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Attenuation_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Attenuation settings for spatialized beds (nullptr = 2D/global). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Attenuation settings for spatialized beds (nullptr = 2D/global)." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FSoundscapeBedLayer constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SoundWave;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BaseVolume;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxVolume;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BasePitch;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxPitch;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LocalOffset;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Attenuation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FSoundscapeBedLayer constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSoundscapeBedLayer>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FSoundscapeBedLayer Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SoundWave = { "SoundWave", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, SoundWave), Z_Construct_UClass_USoundWave, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundWave_MetaData), NewProp_SoundWave_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BaseVolume = { "BaseVolume", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, BaseVolume), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseVolume_MetaData), NewProp_BaseVolume_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxVolume = { "MaxVolume", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, MaxVolume), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxVolume_MetaData), NewProp_MaxVolume_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_BasePitch = { "BasePitch", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, BasePitch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BasePitch_MetaData), NewProp_BasePitch_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxPitch = { "MaxPitch", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, MaxPitch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxPitch_MetaData), NewProp_MaxPitch_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_LocalOffset = { "LocalOffset", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, LocalOffset), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LocalOffset_MetaData), NewProp_LocalOffset_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Attenuation = { "Attenuation", nullptr, (EPropertyFlags)0x0114000000000015, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FSoundscapeBedLayer, Attenuation), Z_Construct_UClass_USoundAttenuation, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Attenuation_MetaData), NewProp_Attenuation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoundWave,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BaseVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxVolume,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BasePitch,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxPitch,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LocalOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Attenuation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FSoundscapeBedLayer Property Definitions ****************************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
	nullptr,
	&NewStructOps,
	"SoundscapeBedLayer",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FSoundscapeBedLayer>(),
	alignof(FSoundscapeBedLayer),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer;
UScriptStruct* Z_Construct_UScriptStruct_FSoundscapeBedLayer(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSoundscapeBedLayer, (UObject*)Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase::Outer), TEXT("SoundscapeBedLayer"));
		}
		return Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FSoundscapeBedLayer *************************************************

// ********** Begin Class USoundscapeDataAsset *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_USoundscapeDataAsset_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Data asset defining the full soundscape for a scenario level.\n * Layers: HVAC hum, fridge murmur, clock tick, distant murmur.\n * Mute = dead world (no scenario active). Unmute = occupied world.\n */" },
#endif
		{ "IncludePath", "Audio/SoundscapeDataAsset.h" },
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Data asset defining the full soundscape for a scenario level.\nLayers: HVAC hum, fridge murmur, clock tick, distant murmur.\nMute = dead world (no scenario active). Unmute = occupied world." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoundscapeId_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Unique identifier for this soundscape (e.g. \"Workplace_Default\"). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Unique identifier for this soundscape (e.g. \"Workplace_Default\")." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DisplayName_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Display name. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Display name." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HVACLayer_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** HVAC hum layer \xe2\x80\x94 low-frequency mechanical drone. Volume rises with stress. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "HVAC hum layer \xe2\x80\x94 low-frequency mechanical drone. Volume rises with stress." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FridgeLayer_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fridge murmur layer \xe2\x80\x94 gentle intermittent hum. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fridge murmur layer \xe2\x80\x94 gentle intermittent hum." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ClockLayer_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Clock tick layer \xe2\x80\x94 rhythmic ticking. Pitch rises with stress. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Clock tick layer \xe2\x80\x94 rhythmic ticking. Pitch rises with stress." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MurmurLayer_MetaData[] = {
		{ "Category", "Soundscape" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distant murmur layer \xe2\x80\x94 background voices/machinery. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distant murmur layer \xe2\x80\x94 background voices/machinery." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FullStressThreshold_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Stress at which all beds reach max intensity (0..1). */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stress at which all beds reach max intensity (0..1)." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FadeInDuration_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fade-in duration in seconds when soundscape activates. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fade-in duration in seconds when soundscape activates." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FadeOutDuration_MetaData[] = {
		{ "Category", "Soundscape" },
		{ "ClampMin", "0.0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Fade-out duration in seconds when soundscape deactivates. */" },
#endif
		{ "ModuleRelativePath", "Public/Audio/SoundscapeDataAsset.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Fade-out duration in seconds when soundscape deactivates." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class USoundscapeDataAsset constinit property declarations *********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_SoundscapeId;
	static const UECodeGen_Private::FTextPropertyParams NewProp_DisplayName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_HVACLayer;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FridgeLayer;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ClockLayer;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MurmurLayer;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FullStressThreshold;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FadeInDuration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FadeOutDuration;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class USoundscapeDataAsset constinit property declarations ***********************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USoundscapeDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class USoundscapeDataAsset Property Definitions ********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_SoundscapeId = { "SoundscapeId", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, SoundscapeId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoundscapeId_MetaData), NewProp_SoundscapeId_MetaData) };
const UECodeGen_Private::FTextPropertyParams UHT_STATICS::NewProp_DisplayName = { "DisplayName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Text, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, DisplayName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DisplayName_MetaData), NewProp_DisplayName_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_HVACLayer = { "HVACLayer", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, HVACLayer), Z_Construct_UScriptStruct_FSoundscapeBedLayer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HVACLayer_MetaData), NewProp_HVACLayer_MetaData) }; // 1c1d0f74d5d6e82f6ef3dd311d60ab2532c76f35
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FridgeLayer = { "FridgeLayer", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, FridgeLayer), Z_Construct_UScriptStruct_FSoundscapeBedLayer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FridgeLayer_MetaData), NewProp_FridgeLayer_MetaData) }; // 1c1d0f74d5d6e82f6ef3dd311d60ab2532c76f35
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ClockLayer = { "ClockLayer", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, ClockLayer), Z_Construct_UScriptStruct_FSoundscapeBedLayer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ClockLayer_MetaData), NewProp_ClockLayer_MetaData) }; // 1c1d0f74d5d6e82f6ef3dd311d60ab2532c76f35
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_MurmurLayer = { "MurmurLayer", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, MurmurLayer), Z_Construct_UScriptStruct_FSoundscapeBedLayer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MurmurLayer_MetaData), NewProp_MurmurLayer_MetaData) }; // 1c1d0f74d5d6e82f6ef3dd311d60ab2532c76f35
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FullStressThreshold = { "FullStressThreshold", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, FullStressThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FullStressThreshold_MetaData), NewProp_FullStressThreshold_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FadeInDuration = { "FadeInDuration", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, FadeInDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FadeInDuration_MetaData), NewProp_FadeInDuration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_FadeOutDuration = { "FadeOutDuration", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(USoundscapeDataAsset, FadeOutDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FadeOutDuration_MetaData), NewProp_FadeOutDuration_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoundscapeId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DisplayName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_HVACLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FridgeLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ClockLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MurmurLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FullStressThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FadeInDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FadeOutDuration,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class USoundscapeDataAsset Property Definitions **********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UPrimaryDataAsset,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_USoundscapeDataAsset,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_USoundscapeDataAsset;
UClass* Z_Construct_UClass_USoundscapeDataAsset(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = USoundscapeDataAsset;
		if (!Z_Registration_Info_UClass_USoundscapeDataAsset.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SoundscapeDataAsset"),
				Z_Registration_Info_UClass_USoundscapeDataAsset.InnerSingleton,
				nullptr,
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
		return Z_Registration_Info_UClass_USoundscapeDataAsset.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_USoundscapeDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USoundscapeDataAsset.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_USoundscapeDataAsset.OuterSingleton;
}
#undef UHT_STATICS
USoundscapeDataAsset::USoundscapeDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, USoundscapeDataAsset);
USoundscapeDataAsset::~USoundscapeDataAsset() {}
// ********** End Class USoundscapeDataAsset *******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FSoundscapeBedLayer, Z_Construct_UScriptStruct_FSoundscapeBedLayer_Statics::NewStructOps, TEXT("SoundscapeBedLayer"),&Z_Registration_Info_UScriptStruct_FSoundscapeBedLayer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSoundscapeBedLayer), 471666548U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USoundscapeDataAsset, TEXT("USoundscapeDataAsset"), &Z_Registration_Info_UClass_USoundscapeDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USoundscapeDataAsset), 2890720339U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Audio_SoundscapeDataAsset_h__Script_WorldEngine_97c5cbe0089566d69da14ff9b2dd26100ef7285f{
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
