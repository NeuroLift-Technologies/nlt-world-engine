// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Scenarios/UScenarioLibrary.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeUScenarioLibrary() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase);
WORLDENGINE_API UEnum* Z_Construct_UEnum_WorldEngine_EScenarioCategory(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioLibrary(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioDataAsset(ETypeConstructPhase);
WORLDENGINE_API UClass* Z_Construct_UClass_UScenarioLibrary(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UScenarioLibrary Function GetAllScenarios ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UScenarioLibrary_GetAllScenarios_Statics
struct UHT_STATICS
{
	struct ScenarioLibrary_eventGetAllScenarios_Parms
	{
		TArray<UScenarioDataAsset*> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns all UScenarioDataAsset assets found on disk. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns all UScenarioDataAsset assets found on disk." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetAllScenarios constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetAllScenarios constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetAllScenarios Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, 0, Z_Construct_UClass_UScenarioDataAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ScenarioLibrary_eventGetAllScenarios_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetAllScenarios Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UScenarioLibrary, nullptr, "GetAllScenarios", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::ScenarioLibrary_eventGetAllScenarios_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::ScenarioLibrary_eventGetAllScenarios_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UScenarioLibrary_GetAllScenarios(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UScenarioLibrary::execGetAllScenarios)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<UScenarioDataAsset*>*)Z_Param__Result=UScenarioLibrary::GetAllScenarios();
	P_NATIVE_END;
}
// ********** End Class UScenarioLibrary Function GetAllScenarios **********************************

// ********** Begin Class UScenarioLibrary Function GetScenarioById ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UScenarioLibrary_GetScenarioById_Statics
struct UHT_STATICS
{
	struct ScenarioLibrary_eventGetScenarioById_Parms
	{
		FName Id;
		UScenarioDataAsset* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Finds a scenario by its unique ScenarioId, or nullptr if not found. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Finds a scenario by its unique ScenarioId, or nullptr if not found." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetScenarioById constinit property declarations ***********************
	static const UECodeGen_Private::FNamePropertyParams NewProp_Id;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetScenarioById constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetScenarioById Property Definitions **********************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ScenarioLibrary_eventGetScenarioById_Parms, Id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ScenarioLibrary_eventGetScenarioById_Parms, ReturnValue), Z_Construct_UClass_UScenarioDataAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Id,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetScenarioById Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UScenarioLibrary, nullptr, "GetScenarioById", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::ScenarioLibrary_eventGetScenarioById_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::ScenarioLibrary_eventGetScenarioById_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UScenarioLibrary_GetScenarioById(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UScenarioLibrary::execGetScenarioById)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_Id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UScenarioDataAsset**)Z_Param__Result=UScenarioLibrary::GetScenarioById(Z_Param_Id);
	P_NATIVE_END;
}
// ********** End Class UScenarioLibrary Function GetScenarioById **********************************

// ********** Begin Class UScenarioLibrary Function GetScenariosByCategory *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UScenarioLibrary_GetScenariosByCategory_Statics
struct UHT_STATICS
{
	struct ScenarioLibrary_eventGetScenariosByCategory_Parms
	{
		EScenarioCategory Cat;
		TArray<UScenarioDataAsset*> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns all scenarios matching the given category. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns all scenarios matching the given category." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function GetScenariosByCategory constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Cat_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Cat;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function GetScenariosByCategory constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function GetScenariosByCategory Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_Cat_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams UHT_STATICS::NewProp_Cat = { "Cat", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, nullptr, nullptr, 1, STRUCT_OFFSET(ScenarioLibrary_eventGetScenariosByCategory_Parms, Cat), Z_Construct_UEnum_WorldEngine_EScenarioCategory, METADATA_PARAMS(0, nullptr) }; // 433ccdc0e3c8bafbec82407eab2ec539992811ce
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, 0, Z_Construct_UClass_UScenarioDataAsset, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ScenarioLibrary_eventGetScenariosByCategory_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cat_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Cat,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function GetScenariosByCategory Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UScenarioLibrary, nullptr, "GetScenariosByCategory", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::ScenarioLibrary_eventGetScenariosByCategory_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::ScenarioLibrary_eventGetScenariosByCategory_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UScenarioLibrary_GetScenariosByCategory(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UScenarioLibrary::execGetScenariosByCategory)
{
	P_GET_ENUM(EScenarioCategory,Z_Param_Cat);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<UScenarioDataAsset*>*)Z_Param__Result=UScenarioLibrary::GetScenariosByCategory(EScenarioCategory(Z_Param_Cat));
	P_NATIVE_END;
}
// ********** End Class UScenarioLibrary Function GetScenariosByCategory ***************************

// ********** Begin Class UScenarioLibrary Function LoadAllScenariosFromDisk ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UScenarioLibrary_LoadAllScenariosFromDisk_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "NLT|Scenario" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Forces a synchronous scan of the asset registry for all scenario assets. */" },
#endif
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Forces a synchronous scan of the asset registry for all scenario assets." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function LoadAllScenariosFromDisk constinit property declarations **************
// ********** End Function LoadAllScenariosFromDisk constinit property declarations ****************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UScenarioLibrary, nullptr, "LoadAllScenariosFromDisk", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UScenarioLibrary_LoadAllScenariosFromDisk(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(UScenarioLibrary::execLoadAllScenariosFromDisk)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	UScenarioLibrary::LoadAllScenariosFromDisk();
	P_NATIVE_END;
}
// ********** End Class UScenarioLibrary Function LoadAllScenariosFromDisk *************************

// ********** Begin Class UScenarioLibrary *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UScenarioLibrary_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Static library for discovering and loading UScenarioDataAsset instances from disk.\n * Provides Blueprint-callable access to the scenario catalog without requiring\n * manual asset references in Blueprints or C++.\n */" },
#endif
		{ "IncludePath", "Scenarios/UScenarioLibrary.h" },
		{ "ModuleRelativePath", "Public/Scenarios/UScenarioLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Static library for discovering and loading UScenarioDataAsset instances from disk.\nProvides Blueprint-callable access to the scenario catalog without requiring\nmanual asset references in Blueprints or C++." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UScenarioLibrary constinit property declarations *************************
// ********** End Class UScenarioLibrary constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("GetAllScenarios"), .Pointer = &UScenarioLibrary::execGetAllScenarios },
		{ .NameUTF8 = UTF8TEXT("GetScenarioById"), .Pointer = &UScenarioLibrary::execGetScenarioById },
		{ .NameUTF8 = UTF8TEXT("GetScenariosByCategory"), .Pointer = &UScenarioLibrary::execGetScenariosByCategory },
		{ .NameUTF8 = UTF8TEXT("LoadAllScenariosFromDisk"), .Pointer = &UScenarioLibrary::execLoadAllScenariosFromDisk },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UScenarioLibrary_GetAllScenarios, "GetAllScenarios" }, // 741ff2621cccdfe4c32d7c33b95e90807bbb3ca1
		{ &Z_Construct_UFunction_UScenarioLibrary_GetScenarioById, "GetScenarioById" }, // 5a7448578138940c0de151a6e9eff752996562d8
		{ &Z_Construct_UFunction_UScenarioLibrary_GetScenariosByCategory, "GetScenariosByCategory" }, // 31182bb4f02ded2ce1d098a05161df1d1d5235db
		{ &Z_Construct_UFunction_UScenarioLibrary_LoadAllScenariosFromDisk, "LoadAllScenariosFromDisk" }, // d3827fa3c267ef2ea05ccaa19705d85c8edd4b5e
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UScenarioLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UBlueprintFunctionLibrary,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_WorldEngine,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UScenarioLibrary,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UScenarioLibrary_StaticRegisterNativesUScenarioLibrary()
{
	UClass* Class = UScenarioLibrary::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UScenarioLibrary;
UClass* Z_Construct_UClass_UScenarioLibrary(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UScenarioLibrary;
		if (!Z_Registration_Info_UClass_UScenarioLibrary.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("ScenarioLibrary"),
				Z_Registration_Info_UClass_UScenarioLibrary.InnerSingleton,
				UScenarioLibrary_StaticRegisterNativesUScenarioLibrary,
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
		return Z_Registration_Info_UClass_UScenarioLibrary.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UScenarioLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UScenarioLibrary.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UScenarioLibrary.OuterSingleton;
}
#undef UHT_STATICS
UScenarioLibrary::UScenarioLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UScenarioLibrary);
UScenarioLibrary::~UScenarioLibrary() {}
// ********** End Class UScenarioLibrary ***********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h__Script_WorldEngine_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UScenarioLibrary, TEXT("UScenarioLibrary"), &Z_Registration_Info_UClass_UScenarioLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UScenarioLibrary), 1737478917U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Desktop_nlt_repos_nlt_world_engine_WorldEngine_Source_WorldEngine_Public_Scenarios_UScenarioLibrary_h__Script_WorldEngine_32051ebf8fc95bcf532feeb3aa30635fec7fc101{
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
