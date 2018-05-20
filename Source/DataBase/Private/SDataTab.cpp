#include "SDataTab.h"
#include "SDTHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "SDataTabHeader.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScrollBox.h"
#include "SDataTableRow.h"

void SDataTab::OnRowChanged(const int32& RowIndex, const int32& ColumnIndex, const FString& Value)
{
	OnDataTableChanged.ExecuteIfBound(RowIndex, ColumnIndex, Value);
}

void SDataTab::UpdateWidget()
{
	ensure(Header.IsValid());
	ensure(DataTableStyle);

	Header->ClearColumns();
	for (int32 ID = 0; ID < Fields.Num(); ID++)
	{
// 		Header->AddColumn(
// 			ID
// 			, SNew(SDataTabHeader)
// 			.VarName(Fields[ID].FieldName)
// 			.DataTableStyle(DataTableStyle)
// 		);
	}

	if (CurrentDataObject.IsValid())
	{
		Rows.Empty();
		RowContainer->ClearChildren();
		for (int32 i = 0; i < CurrentDataObject->Data.Num(); i++)
		{
			AddRow(CurrentDataObject->Data[i].Inputs, CurrentDataObject->bUseCustomWidgets, bIsEditable);
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
		UE_LOG(LogTemp, Error, TEXT("SDataTab::SetFields NO DataObject Assigned"));
	}
	UpdateWidget();
}

void SDataTab::AddRow(TArray<FString>& Values,const bool& bUseWidgets,const bool& bIsEditable)
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
	SScrollBox::FSlot& PosSlot = RowContainer->AddSlot();
	PosSlot[
		SAssignNew(NewRow, SDTHeaderRow)
			.Values(Values)
			.DataTableStyle(&FDataTableStyle::GetDefault())
			.ID(RowIndex)
			.Fields(Fields)
			.OnDTRowChanged(this, &SDataTab::OnRowChanged)
			.HumanEditable(false)
	];

	check(NewRow.IsValid());
	Rows.Add(NewRow);
}

void SDataTab::Construct(const FArguments& InArgs)
{
	OnDataTableChanged = InArgs._OnDataTableChanged;
	CurrentDataObject = InArgs._DataObject;
	bIsEditable = InArgs._Editable;
	DataTableStyle = InArgs._DataTableStyle;
	Fields = InArgs._ColumnDescriptions;

	ChildSlot[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.AutoHeight()
		[
			SAssignNew(Header, SDTHeaderRow)
		]
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SAssignNew(RowContainer, SScrollBox)
			.Style(&FCoreStyle::Get().GetWidgetStyle<FScrollBoxStyle>("ScrollBox"))
			.ScrollBarStyle(&FCoreStyle::Get().GetWidgetStyle<FScrollBarStyle>("ScrollBar"))
			.ScrollBarVisibility(EVisibility::Visible)
		]
	];

	RowContainer->SetScrollBarAlwaysVisible(true);
	UpdateWidget();
}

SDataTab::~SDataTab()
{

}

