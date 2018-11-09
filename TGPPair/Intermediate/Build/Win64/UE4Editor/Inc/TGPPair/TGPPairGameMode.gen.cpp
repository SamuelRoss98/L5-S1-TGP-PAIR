// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "TGPPair/TGPPairGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTGPPairGameMode() {}
// Cross Module References
	TGPPAIR_API UClass* Z_Construct_UClass_ATGPPairGameMode_NoRegister();
	TGPPAIR_API UClass* Z_Construct_UClass_ATGPPairGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_TGPPair();
// End Cross Module References
	void ATGPPairGameMode::StaticRegisterNativesATGPPairGameMode()
	{
	}
	UClass* Z_Construct_UClass_ATGPPairGameMode_NoRegister()
	{
		return ATGPPairGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ATGPPairGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ATGPPairGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_TGPPair,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ATGPPairGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "TGPPairGameMode.h" },
		{ "ModuleRelativePath", "TGPPairGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ATGPPairGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ATGPPairGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ATGPPairGameMode_Statics::ClassParams = {
		&ATGPPairGameMode::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x008802A8u,
		nullptr, 0,
		nullptr, 0,
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_ATGPPairGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_ATGPPairGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ATGPPairGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ATGPPairGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ATGPPairGameMode, 1543451578);
	static FCompiledInDefer Z_CompiledInDefer_UClass_ATGPPairGameMode(Z_Construct_UClass_ATGPPairGameMode, &ATGPPairGameMode::StaticClass, TEXT("/Script/TGPPair"), TEXT("ATGPPairGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ATGPPairGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
