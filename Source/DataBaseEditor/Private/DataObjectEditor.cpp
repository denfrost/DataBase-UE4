#include "DataObjectEditor.h"
#include "DataObject.h"
#include "Editor.h"
#include "LevelEditor.h"
#include "SlateBasics.h"
#include "SlateStyle.h"
#include "Editor/EditorStyle/Public/EditorStyleSet.h"
#include "Editor/PropertyEditor/Public/IDetailsView.h"
#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "SDataTab.h"

namespace EditableDataObjectToolKit
{
	static const FName AppIdentifier("DataObjectEditorID");
	static const FName DataTableTab("MainFrameID");
	static const FName DetailsViewTab("DetailsViewTabID");
}


FDataObjectEditor::FDataObjectEditor()
{

}

FDataObjectEditor::~FDataObjectEditor()
{
	FEditorDelegates::OnAssetPostImport.RemoveAll(this);
	GEditor->UnregisterForUndo(this);
}

void FDataObjectEditor::InitDataObject(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UDataObject* ObjectToEdit)
{
	DataObject = ObjectToEdit;
	GEditor->RegisterForUndo(this);
	BindCommands();

	//Create Details View Interface
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);
	DataObjectDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DataObjectDetailsView->SetObject(DataObject);

	//Bind On Property Changed
	DataObjectDetailsView->OnFinishedChangingProperties().AddSP(this, &FDataObjectEditor::OnPropertyChanged);


	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_DataObjectEditor_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.66f)
				->Split
				(
					// tool bar
					FTabManager::NewStack()
					->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.01f)

				)
				->Split
				(
					FTabManager::NewSplitter()
					->SetOrientation(Orient_Horizontal)
					->SetSizeCoefficient(.8f)
					->Split
					(
						// Main Editor
						FTabManager::NewStack()
						->AddTab(EditableDataObjectToolKit::DataTableTab, ETabState::OpenedTab)
						->SetHideTabWell(true)
					)
					->Split
					(
						// Main Editor
						FTabManager::NewStack()
						->AddTab(EditableDataObjectToolKit::DetailsViewTab, ETabState::OpenedTab)
						->SetHideTabWell(true)
					)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(
		Mode,
		InitToolkitHost,
		EditableDataObjectToolKit::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		ObjectToEdit
	);

	ExtendToolBar();
	RegenerateMenusAndToolbars();
}

FString FDataObjectEditor::GetDocumentationLink() const
{
	return FString(TEXT("Engine/Content/Types/EditableMeshAssets/Properties/Interface"));
}

bool FDataObjectEditor::OnRequestClose()
{
	if (DataObject != nullptr)
	{
		//close this garbage here
	}
	return FAssetEditorToolkit::OnRequestClose();
}

void FDataObjectEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(FText::FromString("Data Table Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);

	//Register Data table palette tab
	TabManager->RegisterTabSpawner(EditableDataObjectToolKit::DataTableTab, FOnSpawnTab::CreateSP(this, &FDataObjectEditor::HandleTabManagerSpawnTab, EditableDataObjectToolKit::DataTableTab))
		.SetDisplayName(FText::FromString("MainEditor"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	//Register Details palette tab
	TabManager->RegisterTabSpawner(EditableDataObjectToolKit::DetailsViewTab, FOnSpawnTab::CreateSP(this, &FDataObjectEditor::HandleTabManagerSpawnTab, EditableDataObjectToolKit::DetailsViewTab))
		.SetDisplayName(FText::FromString("Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));
}

void FDataObjectEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);
	TabManager->UnregisterTabSpawner(EditableDataObjectToolKit::DataTableTab);
	TabManager->UnregisterTabSpawner(EditableDataObjectToolKit::DetailsViewTab);
}

void FDataObjectEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(DataObject);
}

FText FDataObjectEditor::GetBaseToolkitName() const
{
	return FText::FromString("Data Object Editor");
}

FName FDataObjectEditor::GetToolkitFName() const
{
	return FName("DataObjectEditor");
}

FLinearColor FDataObjectEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

FString FDataObjectEditor::GetWorldCentricTabPrefix() const
{
	return "Data Object";
}

void FDataObjectEditor::PostUndo(bool bSuccess)
{

}

void FDataObjectEditor::PostRedo(bool bSuccess)
{
	PostUndo(bSuccess);
}

void FDataObjectEditor::BindCommands()
{

}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void FDataObjectEditor::ExtendToolBar()
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(this, &FDataObjectEditor::FillToolbar, GetToolkitCommands())
	);

	AddToolbarExtender(ToolbarExtender);
}

void FDataObjectEditor::FillToolbar(FToolBarBuilder& ToolbarBuilder, const TSharedRef<FUICommandList> ToolkitCommands)
{
	ToolbarBuilder.BeginSection("Import options");
	{
		//Import from CSV file
		FUIAction ImportCSV(FExecuteAction::CreateSP(this, &FDataObjectEditor::ImportFromCSV));
		ToolbarBuilder.AddToolBarButton(ImportCSV, TEXT("Import from CSV"), FText::FromString("FromCSV"), FText::FromString("Import data directly from a csv table"));

		//Add New row
		FUIAction AddNewRow(FExecuteAction::CreateSP(this, &FDataObjectEditor::AddNewRow));
		ToolbarBuilder.AddToolBarButton(AddNewRow, TEXT("Add Row"), FText::FromString("Add Row"), FText::FromString("Add A new row to your table"));
	}
	ToolbarBuilder.EndSection();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FDataObjectEditor::ImportFromCSV()
{
	UE_LOG(LogTemp, Log, TEXT("yeah"));
}


void FDataObjectEditor::AddNewRow()
{
	ensure(DataObject && DataTableView.IsValid());
	TArray<FString> RowEmptyValues;
	RowEmptyValues.Init("", DataObject->Fields.Num());
	DataTableView->AddRow(RowEmptyValues, DataObject->bUseCustomWidgets,true);

	//Add new empty Data to Our Object
	FRowData NewDataRow;
	NewDataRow.Inputs = RowEmptyValues;
	DataObject->Data.Add(NewDataRow);

	DataObject->MarkPackageDirty();
}

TSharedRef<SDockTab> FDataObjectEditor::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	

	if (TabIdentifier == EditableDataObjectToolKit::DataTableTab)
	{
		DataTableView = SNew(SDataTab)
			.ColumnDescriptions(DataObject->Fields)
			.OnDataTableChanged(this, &FDataObjectEditor::OnDataTableChanged)
			.DataObject(DataObject)
			.Editable(false);

		return SNew(SDockTab)
			.TabRole(ETabRole::PanelTab)
			[
				DataTableView.ToSharedRef()
			];
	}

	if (TabIdentifier == EditableDataObjectToolKit::DetailsViewTab)
	{
		return SNew(SDockTab)
			.TabRole(ETabRole::PanelTab)
			[
				DataObjectDetailsView.ToSharedRef()
			];
	}
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;
	return SNew(SDockTab)
	.TabRole(ETabRole::PanelTab)
	[
		TabWidget.ToSharedRef()
	];
}

TSharedRef<SWidget> FDataObjectEditor::GenPrimitivesTab()
{
	TSharedPtr<FUICommandList> commands;

	FToolBarBuilder ToolbarBuilder(commands, FMultiBoxCustomization::None);
	//ToolbarBuilder.AddWidget(GenShelfButton());
	return ToolbarBuilder.MakeWidget();
}

void FDataObjectEditor::OnPropertyChanged(const FPropertyChangedEvent& PropertyChangedEvet)
{
	ensure(DataObject && DataTableView.IsValid());

	DataTableView->SetFields(DataObject->Fields);
	DataObject->MarkPackageDirty();
}

void FDataObjectEditor::OnDataTableChanged(const int32& RowIndex, const int32& ColumnIndex, const FString& Value)
{
	if (DataObject && DataObject->Data.IsValidIndex(RowIndex) && DataObject->Data[RowIndex].Inputs.IsValidIndex(ColumnIndex))
	{
		DataObject->Data[RowIndex].Inputs[ColumnIndex] = Value;
		DataObject->MarkPackageDirty();
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("Invalid Entry Row: %i , Column: %i , Value: %s"), RowIndex, ColumnIndex, *Value);
}

