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

void UDataTab::AddSearchCriteria(const TArray<FDTCriteria>& NewCriteria)
{
	if (DataTable.IsValid())
	{
		DataTable->AddSearchCriteria(NewCriteria);
	}
}

void UDataTab::ClearSearchCriteria()
{
	if (DataTable.IsValid())
	{
		DataTable->ClearCriteria();
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
			.Editable(false)
			.OnRowClicked(BIND_UOBJECT_DELEGATE(FOnDTRowClicked, OnRowClicked))
			.OnRowDoubleClicked(BIND_UOBJECT_DELEGATE(FOnDTRowClicked, OnRowDoubleClicked));
	}
	else
	{
		DataTable = SNew(SDataTab)
			.DataTableStyle(&DataTableStyle)
			.DataObject(DataObject)
			.Editable(false)
			.OnRowClicked(BIND_UOBJECT_DELEGATE(FOnDTRowClicked, OnRowClicked))
			.OnRowDoubleClicked(BIND_UOBJECT_DELEGATE(FOnDTRowClicked, OnRowDoubleClicked));
	}
	return DataTable->AsShared();
}

void UDataTab::OnRowClicked(const int32& RowIndex, const TArray<FString>& Values)
{
	if (OnDataTableRowClicked.IsBound())
	{
		OnDataTableRowClicked.Broadcast(RowIndex, Values);
	}
}

void UDataTab::OnRowDoubleClicked(const int32& RowIndex, const TArray<FString>& Values)
{
	if (OnDataTableRowDoubleClicked.IsBound())
	{
		OnDataTableRowDoubleClicked.Broadcast(RowIndex, Values);
	}
}

