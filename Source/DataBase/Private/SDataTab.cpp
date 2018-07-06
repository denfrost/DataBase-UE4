#include "SDataTab.h"
#include "SDTHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScrollBox.h"
#include "DTFunctionLibrary.h"

void SDataTab::OnRowChanged(const int32& RowIndex, const int32& ColumnIndex, const FString& Value, const UObject* NewObjReference)
{
	OnDataTableChanged.ExecuteIfBound(RowIndex, ColumnIndex, Value, NewObjReference);
}

void SDataTab::OnRowClicked(const int32& RowIndex, const TArray<FString>& Values)
{
	OnRowClick.ExecuteIfBound(RowIndex, Values);
}

void SDataTab::OnRowDoubleClicked(const int32& RowIndex, const TArray<FString>& Values)
{
	OnRowDoubleClick.ExecuteIfBound(RowIndex, Values);
}


void SDataTab::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//later with can implemented the criteria here, for now is going to be in one single frame
}

void SDataTab::UpdateWidget()
{
	Header->SetColumns(Fields, TArray<FString>());
	if (CurrentDataObject.IsValid())
	{
		Rows.Empty();
		RowContainer->ClearChildren();
		for (int32 i = 0; i < CurrentDataObject->Data.Num(); i++)
		{
			AddRow(CurrentDataObject->Data[i].Inputs, bIsEditable);
		}
	}
}

void SDataTab::SetFields(const TArray<FDataTableFieldDescription>& InFields)
{
	Fields = InFields;
	if (CurrentDataObject.IsValid())
	{
		CurrentDataObject->UpdateRowsAfterFields();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SDataTab::SetFields No DataObject Assigned"));
	}
	UpdateWidget();
}

void SDataTab::AddRow(TArray<FString>& Values, const bool& IsEditable)
{
	check(RowContainer.IsValid());

	if (Values.Num() < Fields.Num())
	{
		while (Values.Num() < Fields.Num())
		{
			Values.Add("");
		}
	}

	int32 RowIndex = Rows.Num();

	TSharedPtr<SDTHeaderRow> NewRow;
	SScrollBox::FSlot& PosSlot = RowContainer->AddSlot().Padding(DataTableStyle->BodyStyle.GeneralMargin);
	PosSlot[

		SAssignNew(NewRow, SDTHeaderRow)
			.Values(Values)
			.DataTableStyle(DataTableStyle)
			.RowIndex(RowIndex)
			.Fields(Fields)
			.Editable(IsEditable)
			.bIsMaster(false)
			.OnDTRowChanged(this, &SDataTab::OnRowChanged)
			.OnRowClicked(this, &SDataTab::OnRowClicked)
			.OnRowDoubleClicked(this, &SDataTab::OnRowDoubleClicked)
	];
	
	check(NewRow.IsValid());
	Rows.Add(NewRow);
	NewRow->UpdateWidget();
}

FReply SDataTab::OnClick()
{
	UE_LOG(LogTemp, Warning, TEXT("yeah"));
	return FReply::Handled();
}


void SDataTab::SetRowStyleOverride(const int32& Index, const FDataTableStyleOverride& InStyle)
{
	if (Rows.IsValidIndex(Index))
	{
		Rows[Index]->OverrideColumnStyle(InStyle);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("SDataTab::SetRowStyleOverride  Invalid Row Index"));
}

void SDataTab::AddSearchCriteria(const TArray<FDTCriteria>& NewCriteria)
{
	bIsSearching = true;
	/*UE_LOG(LogTemp, Warning, TEXT("new criteria received column %i Criteria %s"), ColumnIndex, *Criteria);*/
	//one single frame criteria

	for (int32 i = 0; i < CurrentDataObject->Data.Num(); i++)
	{
		if (UDTFunctionLibrary::IsValidCriteria(CurrentDataObject->Data[i].Inputs, NewCriteria))
		{
			Rows[i]->SetVisibility(EVisibility::Collapsed);
		}
		else
		{
			Rows[i]->SetVisibility(EVisibility::Visible);
		}
	}
}

void SDataTab::ClearCriteria()
{
	bIsSearching = false;
	for (auto& row : Rows)
	{
		row->SetVisibility(EVisibility::Visible);
	}
}

void SDataTab::Construct(const FArguments& InArgs)
{
	OnDataTableChanged = InArgs._OnDataTableChanged;
	CurrentDataObject = InArgs._DataObject;
	bIsEditable = InArgs._Editable;
	DataTableStyle = InArgs._DataTableStyle;
	Fields = InArgs._ColumnDescriptions;
	OnRowClick = InArgs._OnRowClicked;
	OnRowDoubleClick = InArgs._OnRowDoubleClicked;

	bIsSearching = false;

	ChildSlot[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.AutoHeight()
		[
			SAssignNew(Header, SDTHeaderRow)
				.DataTableStyle(DataTableStyle)
				.Editable(bIsEditable)
				.Fields(Fields)
				.bIsMaster(true)
		]
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(RowContainer, SScrollBox)
			.Style(&FCoreStyle::Get().GetWidgetStyle<FScrollBoxStyle>("ScrollBox"))
			.ScrollBarStyle(&DataTableStyle->BodyStyle.ScrollBarStyle)
			.ScrollBarVisibility(EVisibility::Visible)
		]
	];

	RowContainer->SetScrollBarAlwaysVisible(true);
	UpdateWidget();
}

SDataTab::~SDataTab()
{

}

