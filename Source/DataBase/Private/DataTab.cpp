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

void UDataTab::SetRowStyleOverride(int32 Index, const FDataTableStyleOverride& InStyle)
{
	if (DataTable.IsValid())
	{
		DataTable->SetRowStyleOverride(Index,InStyle);
	}
}

TSharedRef<SWidget> UDataTab::RebuildWidget()
{
	if (DataObject && !DataObject->IsPendingKill())
	{
		DataTable = SNew(SDataTab)
			.DataTableStyle(&DataTableStyle)
			.ColumnDescriptions(DataObject->Fields)
			.DataObject(DataObject)
			.Editable(false);
	}
	else
	{
		DataTable = SNew(SDataTab)
			.DataTableStyle(&DataTableStyle)
			.DataObject(DataObject)
			.Editable(false);
	}
	return DataTable->AsShared();
}

