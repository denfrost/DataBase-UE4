#include "SDTHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Widgets/Layout/SSplitter.h"
#include "SDTColumn.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

bool SDTHeaderRow::CheckCriteria(const FDTCriteria& InCriteria)
{
	if (Columns.IsValidIndex(InCriteria.ColumnIndex))
	{
		for (auto& Crit : InCriteria.Criterias)
		{
			if (Columns[InCriteria.ColumnIndex]->GetValueAsString().Contains(Crit))
			{
				return true;
			}
		}
	}
	return false;
}

void SDTHeaderRow::SetColumns(const TArray<FDataTableFieldDescription>& InFields, const TArray<FString>& InValues)
{
	Values = InValues;
	Fields = InFields;
	UpdateWidget();
}

void SDTHeaderRow::UpdateWidget()
{
	ClearColumns();

	int32 maxTextSize = getLargestValueTextSize();

	for (int32 i = 0; i < Fields.Num(); i++)
	{

		if (!bIsEditable)
		{
			if (Fields[i].bHidden)
			{
				continue;
			}
		}

		ensure(!ColumnIDs.Contains(i));
		if (!Values.IsValidIndex(i))
		{
			Values.Add("");
		}

		SHorizontalBox::FSlot& PosSlot = MainContainer->AddSlot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).Padding((bIsMaster) ? DataTableStyle->HeaderStyle.Margin : DataTableStyle->BodyStyle.GeneralMargin);


		FString FormattedText = (bIsMaster) ? Fields[i].FieldName.ToString() : Values[i];
		TSharedPtr<SDTColumn> Col;
		PosSlot[
			SNew(SScaleBox)
				.SingleLayoutPass(true)
				.Stretch(EStretch::ScaleToFit)
				.StretchDirection(EStretchDirection::Both)
				.VAlign(VAlign_Center)
				.HAlign(HAlign_Fill)
				[
					SAssignNew(Col, SDTColumn)
					.Value(FText::FromString(FormattedText))
					.Type(Fields[i].Type)
					.FilterClass(Fields[i].ObjectFilter)
					.DataTableStyle(DataTableStyle)
					.Editable(bIsEditable)
					.ColumnIndex(i)
					.OnColumnChanged(this, &SDTHeaderRow::OnColumnChanged)
					.bIsMaster(bIsMaster)
				]
		];

		ColumnIDs.Add(i);
		Columns.Add(Col);
	}

	if (!bIsMaster)
	{
		for (int32 i = 0; i < DataTableStyle->BodyStyleColumnsOverrides.Num(); i++)
		{
			OverrideColumnStyle(DataTableStyle->BodyStyleColumnsOverrides[i]);
		}
	}

}

void SDTHeaderRow::ClearColumns()
{
	ColumnIDs.Empty();
	Columns.Empty();
	MainContainer->ClearChildren();
}

void SDTHeaderRow::OverrideColumnStyle(const FDataTableStyleOverride& InStyle)
{
	int32 Index = InStyle.ColumnIndex;
	if (Columns.IsValidIndex(Index))
	{
		Columns[Index]->SetFontAndColor(InStyle);
	}
}

void SDTHeaderRow::OnColumnChanged(const int32& ColumnIndex, const FString& Value, const UObject* NewObjReference)
{
	if (OnDTRowChanged.IsBound())
	{
		OnDTRowChanged.ExecuteIfBound(RowIndex, ColumnIndex, Value, NewObjReference);
	}
}

FReply SDTHeaderRow::OnRowBtnClicked()
{
	OnRowClicked.ExecuteIfBound(RowIndex, Values);
	return FReply::Handled();
}

int32 SDTHeaderRow::getLargestValueTextSize()
{
	int32 size = 0;
	for (int32 i = 0; i < Fields.Num(); i++)
	{
		if (!bIsEditable && Fields[i].bHidden) continue;


		if (bIsMaster)
		{
			if (Fields[i].FieldName.ToString().Len() > size)
			{
				size = Fields[i].FieldName.ToString().Len();
			}
		}
		else
		{
			if (Values[i].Len() > size)
			{
				size = Values[i].Len();
			}
		}
	}
	return size;
}

FString SDTHeaderRow::ProcessTextSize(const FString& InText, const int32& Size)
{
	FString out = InText;
	FString add = " ";
	while (out.Len() < Size * 3)
	{
		out = out  + " ";
	}
	return out;
}

void SDTHeaderRow::Construct(const FArguments& InArgs)
{
	RowIndex = InArgs._RowIndex;
	Values = InArgs._Values;
	Fields = InArgs._Fields;
	DataTableStyle = InArgs._DataTableStyle;
	bIsEditable = InArgs._Editable;
	bIsMaster = InArgs._bIsMaster;
	OnDTRowChanged = InArgs._OnDTRowChanged;
	OnRowClicked = InArgs._OnRowClicked;
	OnRowDoubleClicked = InArgs._OnRowDoubleClicked;



	TSharedPtr<SWidget> Head;
	if (bIsMaster)
	{
		Head = SAssignNew(BackgroundBorder, SBorder)
				.HAlign(HAlign_Fill)
			.BorderImage(&DataTableStyle->HeaderStyle.HeaderBrush)
			[
				SAssignNew(MainContainer, SHorizontalBox)
			];
		
	}
	else
	{
		Head = SNew(SButton)
			.ButtonStyle(&DataTableStyle->BodyStyle.RowButtonStyle)
			.OnClicked(this, &SDTHeaderRow::OnRowBtnClicked)
			.ClickMethod(EButtonClickMethod::PreciseClick)
			.TouchMethod(EButtonTouchMethod::PreciseTap)
			[
				SAssignNew(MainContainer, SHorizontalBox)
			];
	}

	ChildSlot
		[
			Head->AsShared()
		];

/*	UpdateWidget();*/
}

SDTHeaderRow::~SDTHeaderRow()
{

}

