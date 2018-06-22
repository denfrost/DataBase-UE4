// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DataObjectEditor_Style.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "SlateGameResources.h"
#include "IPluginManager.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Runtime/Projects/Public/Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FDataObjectEditorStyle::MenuStyleInstance = NULL;




void FDataObjectEditorStyle::Initialize()
{
	if (!MenuStyleInstance.IsValid())
	{
		MenuStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*MenuStyleInstance);
	}
}

void FDataObjectEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*MenuStyleInstance);
	ensure(MenuStyleInstance.IsUnique());
	MenuStyleInstance.Reset();
}

const ISlateStyle& FDataObjectEditorStyle::Get()
{
	return *MenuStyleInstance;
}

FName FDataObjectEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DataObjectEditorStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH(RelativePath, ...)	FSlateImageBrush(StyleRef->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define TTF_CORE_FONT( RelativePath, ... ) FSlateFontInfo( StyleRef->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleRef->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

TSharedRef<FSlateStyleSet> FDataObjectEditorStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = MakeShareable(new FSlateStyleSet(FDataObjectEditorStyle::GetStyleSetName()));
	StyleRef->SetContentRoot(IPluginManager::Get().FindPlugin("DataBase")->GetBaseDir() / TEXT("Resources/"));

	StyleRef->Set("csv.up", new IMAGE_BRUSH("T_CSVIconUpload_128", FVector2D(48, 48))); // csv load icon
	StyleRef->Set("csv.down", new IMAGE_BRUSH("T_CSVIconDownload_128", FVector2D(48, 48))); // csv export icon

	StyleRef->Set("dt.addrow", new IMAGE_BRUSH("T_DataObjectAddRow_218", FVector2D(48, 48))); // csv export icon
	return StyleRef;
}
#undef IMAGE_BRUSH






