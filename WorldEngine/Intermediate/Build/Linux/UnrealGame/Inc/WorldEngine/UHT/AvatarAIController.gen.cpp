// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Agents/AvatarAIController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeAvatarAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_AAvatarAIController(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_AAvatarAIController(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class AAvatarAIController Function SetLearningAgentsActive *********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_AAvatarAIController_SetLearningAgentsActive_Statics
struct UHT_STATICS
{
	struct AvatarAIController_eventSetLearningAgentsActive_Parms
	{
		bool bActive;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "LearningAgents" },
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function SetLearningAgentsActive constinit property declarations ***************
	static void NewProp_bActive_SetBit(void* Obj)
	{
		((AvatarAIController_eventSetLearningAgentsActive_Parms*)Obj)->bActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetLearningAgentsActive constinit property declarations *****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetLearningAgentsActive Property Definitions **************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bActive = { "bActive", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(AvatarAIController_eventSetLearningAgentsActive_Parms), &UHT_STATICS::NewProp_bActive_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bActive,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetLearningAgentsActive Property Definitions ****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_AAvatarAIController, nullptr, "SetLearningAgentsActive", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::AvatarAIController_eventSetLearningAgentsActive_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::AvatarAIController_eventSetLearningAgentsActive_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_AAvatarAIController_SetLearningAgentsActive(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(AAvatarAIController::execSetLearningAgentsActive)
{
	P_GET_UBOOL(Z_Param_bActive);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SetLearningAgentsActive(Z_Param_bActive);
	P_NATIVE_END;
}
// ********** End Class AAvatarAIController Function SetLearningAgentsActive ***********************

// ********** Begin Class AAvatarAIController ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_AAvatarAIController_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Agents/AvatarAIController.h" },
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WanderRadius_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaitTimeMin_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WaitTimeMax_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AcceptanceRadius_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLearningAgentsActive_MetaData[] = {
		{ "Category", "LearningAgents" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Learning Agents integration\n" },
#endif
		{ "ModuleRelativePath", "Public/Agents/AvatarAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Learning Agents integration" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class AAvatarAIController constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WanderRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaitTimeMin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WaitTimeMax;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AcceptanceRadius;
	static void NewProp_bLearningAgentsActive_SetBit(void* Obj)
	{
		((AAvatarAIController*)Obj)->bLearningAgentsActive = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLearningAgentsActive;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AAvatarAIController constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("SetLearningAgentsActive"), .Pointer = &AAvatarAIController::execSetLearningAgentsActive },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_AAvatarAIController_SetLearningAgentsActive, "SetLearningAgentsActive" }, // bf2c5f46ce8e068c6f89df247db393aae766dd57
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAvatarAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class AAvatarAIController Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WanderRadius = { "WanderRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarAIController, WanderRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WanderRadius_MetaData), NewProp_WanderRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WaitTimeMin = { "WaitTimeMin", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarAIController, WaitTimeMin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaitTimeMin_MetaData), NewProp_WaitTimeMin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WaitTimeMax = { "WaitTimeMax", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarAIController, WaitTimeMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WaitTimeMax_MetaData), NewProp_WaitTimeMax_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AcceptanceRadius = { "AcceptanceRadius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(AAvatarAIController, AcceptanceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AcceptanceRadius_MetaData), NewProp_AcceptanceRadius_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bLearningAgentsActive = { "bLearningAgentsActive", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(AAvatarAIController), &UHT_STATICS::NewProp_bLearningAgentsActive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLearningAgentsActive_MetaData), NewProp_bLearningAgentsActive_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WanderRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WaitTimeMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WaitTimeMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AcceptanceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bLearningAgentsActive,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class AAvatarAIController Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AAIController,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_AAvatarAIController,
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
	0x009002A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void AAvatarAIController_StaticRegisterNativesAAvatarAIController()
{
	UClass* Class = AAvatarAIController::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_AAvatarAIController;
UClass* Z_Construct_UClass_AAvatarAIController(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = AAvatarAIController;
		if (!Z_Registration_Info_UClass_AAvatarAIController.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("AvatarAIController"),
				Z_Registration_Info_UClass_AAvatarAIController.InnerSingleton,
				AAvatarAIController_StaticRegisterNativesAAvatarAIController,
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
		return Z_Registration_Info_UClass_AAvatarAIController.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_AAvatarAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAvatarAIController.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_AAvatarAIController.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AAvatarAIController);
AAvatarAIController::~AAvatarAIController() {}
// ********** End Class AAvatarAIController ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarAIController_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAvatarAIController, TEXT("AAvatarAIController"), &Z_Registration_Info_UClass_AAvatarAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAvatarAIController), 2626483620U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Agents_AvatarAIController_h__Script_WorldEngine_6aef4eafb45e21e3e5826ac070a60354dedc8a99{
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
