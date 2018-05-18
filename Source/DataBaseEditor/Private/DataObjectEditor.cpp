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

	//Create Details here


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
	/*	FUIAction CompileFunction(FExecuteAction::CreateSP(this, &FHLSLEditorToolKit::Compile));*/
	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder, const TSharedRef<FUICommandList> ToolkitCommands)
		{

			ToolbarBuilder.BeginSection("Export options");
			{

			}
			ToolbarBuilder.EndSection();
		}
	};


	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	ToolbarExtender->AddToolBarExtension(
		"Asset",
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar, GetToolkitCommands())
	);

	AddToolbarExtender(ToolbarExtender);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION


TSharedRef<SDockTab> FDataObjectEditor::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	

	if (TabIdentifier == EditableDataObjectToolKit::DataTableTab)
	{
		DataTableView = SNew(SDataTab)
			.ColumnDescriptions(DataObject->Fields);

		return SNew(SDockTab)
			.TabRole(ETabRole::PanelTab)
			[
				DataTableView.ToSharedRef()
			];
	}

	if (TabIdentifier == EditableDataObjectToolKit::DetailsViewTab)
	{
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, true);
		DataObjectDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
		DataObjectDetailsView->SetObject(DataObject);
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

