// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/NLTTrainingManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeNLTTrainingManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
LEARNINGAGENTS_API UClass* Z_Construct_UClass_ULearningAgentsCritic(ETypeConstructPhase);
LEARNINGAGENTS_API UClass* Z_Construct_UClass_ULearningAgentsManager(ETypeConstructPhase);
LEARNINGAGENTS_API UClass* Z_Construct_UClass_ULearningAgentsPolicy(ETypeConstructPhase);
LEARNINGAGENTSTRAINING_API UClass* Z_Construct_UClass_ULearningAgentsPPOTrainer(ETypeConstructPhase);
LEARNINGAGENTSTRAINING_API UClass* Z_Construct_UClass_ULearningAgentsTrainingEnvironment(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTTrainingManager(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAideInteractor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTAvatarInteractor(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UNLTEpisodeManager(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_ANLTTrainingManager(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ANLTTrainingManager Function GetPairedAvatarId ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ANLTTrainingManager_GetPairedAvatarId_Statics
struct UHT_STATICS
{
	struct NLTTrainingManager_eventGetPairedAvatarId_Parms
	{
		int32 AideAgentId;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function GetPairedAvatarId constinit property declarations *********************
	static const UECodeGen_Private::FIntPropertyParams NewProp_AideAgentId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetPairedAvatarId constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetPairedAvatarId Property Definitions ********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AideAgentId = { "AideAgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTTrainingManager_eventGetPairedAvatarId_Parms, AideAgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTTrainingManager_eventGetPairedAvatarId_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideAgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetPairedAvatarId Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ANLTTrainingManager, nullptr, "GetPairedAvatarId", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTTrainingManager_eventGetPairedAvatarId_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTTrainingManager_eventGetPairedAvatarId_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ANLTTrainingManager_GetPairedAvatarId(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ANLTTrainingManager::execGetPairedAvatarId)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_AideAgentId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->GetPairedAvatarId(Z_Param_AideAgentId);
	P_NATIVE_END;
}
// ********** End Class ANLTTrainingManager Function GetPairedAvatarId *****************************

// ********** Begin Class ANLTTrainingManager Function SetPairMapping ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ANLTTrainingManager_SetPairMapping_Statics
struct UHT_STATICS
{
	struct NLTTrainingManager_eventSetPairMapping_Parms
	{
		int32 AideAgentId;
		int32 AvatarAgentId;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "LearningAgents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Pair mapping: Aide AgentId -> Avatar AgentId\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pair mapping: Aide AgentId -> Avatar AgentId" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetPairMapping constinit property declarations ************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_AideAgentId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AvatarAgentId;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetPairMapping constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetPairMapping Property Definitions ***********************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AideAgentId = { "AideAgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTTrainingManager_eventSetPairMapping_Parms, AideAgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_AvatarAgentId = { "AvatarAgentId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(NLTTrainingManager_eventSetPairMapping_Parms, AvatarAgentId), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideAgentId,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarAgentId,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetPairMapping Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ANLTTrainingManager, nullptr, "SetPairMapping", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::NLTTrainingManager_eventSetPairMapping_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::NLTTrainingManager_eventSetPairMapping_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ANLTTrainingManager_SetPairMapping(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ANLTTrainingManager::execSetPairMapping)
{
	P_GET_PROPERTY(FIntProperty,Z_Param_AideAgentId);
	P_GET_PROPERTY(FIntProperty,Z_Param_AvatarAgentId);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetPairMapping(Z_Param_AideAgentId,Z_Param_AvatarAgentId);
	P_NATIVE_END;
}
// ********** End Class ANLTTrainingManager Function SetPairMapping ********************************

// ********** Begin Class ANLTTrainingManager ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ANLTTrainingManager_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IncludePath", "Agents/NLTTrainingManager.h" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AgentManager_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvatarInteractor_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AideInteractor_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Policy_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Critic_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TrainingEnvironment_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Trainer_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EpisodeManager_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxAgentNum_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TickInterval_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRunInference_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRunTraining_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxEpisodeSteps_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/NLTTrainingManager.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class ANLTTrainingManager constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AgentManager;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AvatarInteractor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_AideInteractor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Policy;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Critic;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TrainingEnvironment;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Trainer;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EpisodeManager;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxAgentNum;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TickInterval;
	static void NewProp_bRunInference_SetBit(void* Obj)
	{
		((ANLTTrainingManager*)Obj)->bRunInference = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRunInference;
	static void NewProp_bRunTraining_SetBit(void* Obj)
	{
		((ANLTTrainingManager*)Obj)->bRunTraining = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRunTraining;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxEpisodeSteps;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ANLTTrainingManager constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetPairedAvatarId"), .Pointer = &ANLTTrainingManager::execGetPairedAvatarId },
		{ .NameUTF8 = UTF8TEXT("SetPairMapping"), .Pointer = &ANLTTrainingManager::execSetPairMapping },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ANLTTrainingManager_GetPairedAvatarId, "GetPairedAvatarId" }, // bcafa86b08cbd6a7d60c9f5506673112f5aa8324
		{ &Z_Construct_UFunction_ANLTTrainingManager_SetPairMapping, "SetPairMapping" }, // d815bc87b064e90315e9da756f8744352785b484
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ANLTTrainingManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ANLTTrainingManager Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AgentManager = { "AgentManager", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, AgentManager), Z_Construct_UClass_ULearningAgentsManager, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AgentManager_MetaData), NewProp_AgentManager_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AvatarInteractor = { "AvatarInteractor", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, AvatarInteractor), Z_Construct_UClass_UNLTAvatarInteractor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvatarInteractor_MetaData), NewProp_AvatarInteractor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_AideInteractor = { "AideInteractor", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, AideInteractor), Z_Construct_UClass_UNLTAideInteractor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AideInteractor_MetaData), NewProp_AideInteractor_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Policy = { "Policy", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, Policy), Z_Construct_UClass_ULearningAgentsPolicy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Policy_MetaData), NewProp_Policy_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Critic = { "Critic", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, Critic), Z_Construct_UClass_ULearningAgentsCritic, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Critic_MetaData), NewProp_Critic_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TrainingEnvironment = { "TrainingEnvironment", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, TrainingEnvironment), Z_Construct_UClass_ULearningAgentsTrainingEnvironment, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TrainingEnvironment_MetaData), NewProp_TrainingEnvironment_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Trainer = { "Trainer", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, Trainer), Z_Construct_UClass_ULearningAgentsPPOTrainer, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Trainer_MetaData), NewProp_Trainer_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_EpisodeManager = { "EpisodeManager", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, EpisodeManager), Z_Construct_UClass_UNLTEpisodeManager, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EpisodeManager_MetaData), NewProp_EpisodeManager_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxAgentNum = { "MaxAgentNum", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, MaxAgentNum), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxAgentNum_MetaData), NewProp_MaxAgentNum_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_TickInterval = { "TickInterval", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, TickInterval), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TickInterval_MetaData), NewProp_TickInterval_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRunInference = { "bRunInference", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTTrainingManager), &UHT_STATICS::NewProp_bRunInference_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRunInference_MetaData), NewProp_bRunInference_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bRunTraining = { "bRunTraining", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ANLTTrainingManager), &UHT_STATICS::NewProp_bRunTraining_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRunTraining_MetaData), NewProp_bRunTraining_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxEpisodeSteps = { "MaxEpisodeSteps", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ANLTTrainingManager, MaxEpisodeSteps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxEpisodeSteps_MetaData), NewProp_MaxEpisodeSteps_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AgentManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AvatarInteractor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AideInteractor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Policy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Critic,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TrainingEnvironment,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Trainer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EpisodeManager,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxAgentNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TickInterval,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRunInference,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bRunTraining,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxEpisodeSteps,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ANLTTrainingManager Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ANLTTrainingManager,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ANLTTrainingManager_StaticRegisterNativesANLTTrainingManager()
{
	UClass* Class = ANLTTrainingManager::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ANLTTrainingManager;
UClass* Z_Construct_UClass_ANLTTrainingManager(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ANLTTrainingManager;
		if (!Z_Registration_Info_UClass_ANLTTrainingManager.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("NLTTrainingManager"),
				Z_Registration_Info_UClass_ANLTTrainingManager.InnerSingleton,
				ANLTTrainingManager_StaticRegisterNativesANLTTrainingManager,
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
		return Z_Registration_Info_UClass_ANLTTrainingManager.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ANLTTrainingManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ANLTTrainingManager.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ANLTTrainingManager.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ANLTTrainingManager);
ANLTTrainingManager::~ANLTTrainingManager() {}
// ********** End Class ANLTTrainingManager ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ANLTTrainingManager, TEXT("ANLTTrainingManager"), &Z_Registration_Info_UClass_ANLTTrainingManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ANLTTrainingManager), 2613938238U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_NLTTrainingManager_h__Script_WorldEngine_9bbdf811d4d354b2e301fb5cd8f2befcf99c268f{
	TEXT("/Script/WorldEngine"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
