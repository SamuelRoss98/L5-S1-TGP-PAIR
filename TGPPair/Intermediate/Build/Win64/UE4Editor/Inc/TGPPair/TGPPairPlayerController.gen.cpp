// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TGPPair/TGPPairPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTGPPairPlayerController() {}
// Cross Module References
	TGPPAIR_API UClass* Z_Construct_UClass_ATGPPairPlayerController_NoRegister();
	TGPPAIR_API UClass* Z_Construct_UClass_ATGPPairPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_TGPPair();
// End Cross Module References
	void ATGPPairPlayerController::StaticRegisterNativesATGPPairPlayerController()
	{
	}
	UClass* Z_Construct_UClass_ATGPPairPlayerController_NoRegister()
	{
		return ATGPPairPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_ATGPPairPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATGPPairPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_TGPPair,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATGPPairPlayerController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TGPPairPlayerController.h" },
		{ "ModuleRelativePath", "TGPPairPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATGPPairPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATGPPairPlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATGPPairPlayerController_Statics::ClassParams = {
		&ATGPPairPlayerController::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x008002A4u,
		nullptr, 0,
		nullptr, 0,
		"Game",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ATGPPairPlayerController_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ATGPPairPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATGPPairPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATGPPairPlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATGPPairPlayerController, 1504169610);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATGPPairPlayerController(Z_Construct_UClass_ATGPPairPlayerController, &ATGPPairPlayerController::StaticClass, TEXT("/Script/TGPPair"), TEXT("ATGPPairPlayerController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATGPPairPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
