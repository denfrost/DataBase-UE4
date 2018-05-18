// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DataBaseEditor.h"
#include "Developer/AssetTools/Public/IAssetTools.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Developer/AssetTools/Public/AssetToolsModule.h"
#include "AssetTypeActions_DataBase.h"
#include "Runtime/SlateCore/Public/Styling/SlateStyleRegistry.h"
#define LOCTEXT_NAMESPACE "FDataBaseEditorModule"

void FDataBaseEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	TSharedPtr<FAssetTypeActions_DataObject> AssetTypeActionsDataObject = MakeShareable(new FAssetTypeActions_DataObject());
	AssetTools.RegisterAssetTypeActions(AssetTypeActionsDataObject.ToSharedRef());
}

void FDataBaseEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDataBaseEditorModule, DataBaseEditor)