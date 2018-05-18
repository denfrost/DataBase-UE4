#include "AssetTypeActions_DataBase.h"
#include "Editor/EditorStyle/Public/EditorStyleSet.h"
#include "DataObjectEditor.h"


void FAssetTypeActions_DataObject::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Create Data Object"),
		FText::FromString("Creates a new Data object able to edit some JSON info."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ClassIcon.Material"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAssetTypeActions_DataObject::CreateCSV),
			FCanExecuteAction()
		)
	);
}

void FAssetTypeActions_DataObject::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		UDataObject* DataObject = Cast<UDataObject>(*ObjIt);
		if (DataObject != NULL)
		{
			TSharedRef<FDataObjectEditor> MeshEditorToolkit = MakeShareable(new FDataObjectEditor());
			MeshEditorToolkit->InitDataObject(Mode, EditWithinLevelEditor, DataObject);
		}
	}
}

void FAssetTypeActions_DataObject::CreateCSV()
{
	UE_LOG(LogTemp, Log, TEXT("Creating new static mesh"));
}