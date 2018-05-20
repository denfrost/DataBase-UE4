#include "DataTab.h"
#include "SDataTab.h"

// const FName FDataTableHeaderStyle::TypeName(TEXT("FDataTableHeaderStyle"));


UDataTab::UDataTab()
{

}

#if WITH_EDITOR
void UDataTab::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (DataTable.IsValid() && DataObject && !DataObject->IsPendingKill())
	{
		DataTable->SetFields(DataObject->Fields);
	}
}

const FText UDataTab::GetPaletteCategory()
{
	return FText::FromString("Custom widgets");
}

#endif

void UDataTab::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	if (DataTable.IsValid())
	{
		DataTable.Reset();
	}
}

void UDataTab::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

TSharedRef<SWidget> UDataTab::RebuildWidget()
{
	if (DataObject && !DataObject->IsPendingKill())
	{
		DataTable = SNew(SDataTab)
			.DataTableStyle(&DataTableStyle)
			.ColumnDescriptions(DataObject->Fields)
			.DataObject(DataObject)
			.Editable(true);
	}
	else
	{
		DataTable = SNew(SDataTab)
			.DataTableStyle(&DataTableStyle)
			.DataObject(DataObject)
			.Editable(true);
	}
	return DataTable->AsShared();
}

