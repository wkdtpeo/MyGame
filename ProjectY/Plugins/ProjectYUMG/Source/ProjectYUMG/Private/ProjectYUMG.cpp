// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectYUMG.h"
#include "FKeyStringDetailCustomization.h"

#define LOCTEXT_NAMESPACE "FProjectYUMGModule"

void FProjectYUMGModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	{
		PropertyModule.RegisterCustomClassLayout("KeyString", FOnGetDetailCustomizationInstance::CreateStatic(&FKeyStringDetailCustomization::MakeInstance));
	}
}

void FProjectYUMGModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	{
		PropertyModule.UnregisterCustomPropertyTypeLayout("KeyString");
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FProjectYUMGModule, ProjectYUMG)