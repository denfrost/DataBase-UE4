#include "DataTab.h"
#include "SDataTab.h"


UDataTab::UDataTab()
{
	HeaderColumns.Init(FDataTableColumnDescription(), 1);
}

#if WITH_EDITOR
void UDataTab::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (DataTable.IsValid())
	{
		DataTable->UpdateWidget();
		UE_LOG(LogTemp, Log, TEXT("update"));
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
	DataTable = SNew(SDataTab)
		.HeaderStyle(&HeaderStyle)
		.ColumnDescriptions(HeaderColumns);

	return DataTable->AsShared();
}

