// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/GCObject.h"
#include "Input/Reply.h"
#include "Widgets/SWidget.h"
#include "Editor/UnrealEd/Public/EditorUndoClient.h"
#include "Editor/UnrealEd/Public/Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"
#include "IDetailsView.h"

class SDockableTab;
class STextBlock;
class STextureEditorViewport;
class UFactory;
class UTexture;
class UDataObject;

/**
* Implements an Editor toolkit for textures.
*/
class FDataObjectEditor
	: public FAssetEditorToolkit
	, public FEditorUndoClient
	, public FGCObject
{
public:
	FDataObjectEditor();
	virtual ~FDataObjectEditor();

public:
	/**
	* Edits the specified Texture object.
	*
	* @param Mode The tool kit mode.
	* @param InitToolkitHost
	* @param ObjectToEdit The texture object to edit.
	*/
	void InitDataObject(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UDataObject* ObjectToEdit);

public:
	//~ FAssetEditorToolkit interface
	virtual FString GetDocumentationLink() const override;
	virtual bool OnRequestClose() override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;


public:
	//~ FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
public:
	// IToolkit interface
	virtual FText GetBaseToolkitName() const override;
	virtual FName GetToolkitFName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

protected:
	// FEditorUndoClient interface
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

protected:

	/* Binds the UI commands to delegates.*/
	void BindCommands();

	/* Build Main Menu toolbar for Editable mesh editor*/
	void ExtendToolBar();


private:
	// Widget Creators Begin

	/* Handler for every tab generation*/
	TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);

	/* Generate shelf Primitives*/
	TSharedRef<SWidget> GenPrimitivesTab();

private:


	/** The Texture asset being inspected */
	UDataObject* DataObject;

	TSharedPtr<class IDetailsView> DataObjectDetailsView;
	TSharedPtr<class SDataTab> DataTableView;

private:
	void FillToolbar(FToolBarBuilder& ToolbarBuilder, const TSharedRef<FUICommandList> ToolkitCommands);

	void ImportFromCSV();
	void AddNewRow();

private:

	//Binds
	void OnPropertyChanged(const FPropertyChangedEvent& PropertyChangedEvet);
	void OnDataTableChanged(const int32& RowIndex, const int32& ColumnIndex, const FString& Value);

};