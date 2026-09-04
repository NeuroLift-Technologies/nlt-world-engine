// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWorldEngine_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature(ETypeConstructPhase);
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnAuthoritativeTick__DelegateSignature(ETypeConstructPhase);
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnClockRateChanged__DelegateSignature(ETypeConstructPhase);
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnRoomStateChanged__DelegateSignature(ETypeConstructPhase);
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationEvent__DelegateSignature(ETypeConstructPhase);
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationModeChanged__DelegateSignature(ETypeConstructPhase);
	WORLDENGINE_API UFunction* Z_Construct_UDelegateFunction_WorldEngine_OnSimulationTick__DelegateSignature(ETypeConstructPhase);
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_WorldEngine;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_WorldEngine(ETypeConstructPhase)
	{
		if (!Z_Registration_Info_UPackage__Script_WorldEngine.OuterSingleton)
		{
		static FTypeConstructFunc* SingletonFuncArray[] = {
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_UNLTEpisodeManager_OnEpisodeComplete__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_WorldEngine_OnAuthoritativeTick__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_WorldEngine_OnClockRateChanged__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_WorldEngine_OnRoomStateChanged__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_WorldEngine_OnSimulationEvent__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_WorldEngine_OnSimulationModeChanged__DelegateSignature,
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_WorldEngine_OnSimulationTick__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/WorldEngine",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x7A25E59B,
			0xD9E5F85F,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_WorldEngine.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_WorldEngine.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_WorldEngine(Z_Construct_UPackage__Script_WorldEngine, TEXT("/Script/WorldEngine"), Z_Registration_Info_UPackage__Script_WorldEngine, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x7A25E59B, 0xD9E5F85F));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
