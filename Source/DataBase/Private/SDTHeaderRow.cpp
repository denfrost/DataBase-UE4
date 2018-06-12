#include "SDTHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Widgets/Layout/SSplitter.h"
#include "SDTColumn.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

// void SDTHeaderRow::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
// {
// 	
// 	if (bPressed)
// 	{
// 		Tempo += InDeltaTime;
// 		
// 	}
// 	else
// 	{
// 		if (Tempo > 0 && Tempo < .4f)
// 		{
// 			Tempo = 0;
// 			OnRowClicked.ExecuteIfBound(RowIndex, Values);
// 		}
// 	}
// 	
// }
// 
// 
// FReply SDTHeaderRow::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
// {
// 	if (bIsEditable) return  FReply::Handled();
// 
// 	if (IsEnabled() && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent()))
// 	{
// 		Tempo = 0;
// 		bPressed = true;
// 		if (!bIsMaster)
// 		{
// 			BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Pressed);
// 		}
// 		Invalidate(EInvalidateWidget::Layout);
// 		return FReply::Handled().CaptureMouse(AsShared());
// 	}
// 	return FReply::Handled();
// }
// 
// FReply SDTHeaderRow::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
// {
// 	if (bIsEditable) return  FReply::Handled();
// 
// 	
// 	if (IsEnabled() && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent()))
// 	{
// 		bPressed = false;
// 		if (!bIsMaster)
// 		{
// 			FVector2D Pos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
// 			if (Pos.X > 0 && Pos.Y > 0)
// 			{
// 				BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Hovered);
// 			}
// 			else
// 			{
// 				BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Normal);
// 			}
// 			
// 		}
// 		return FReply::Handled();
// 	}
// 	return FReply::Handled();
// }

// void SDTHeaderRow::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
// {
// 	if (bIsEditable) return;
// 
// 	if (!bIsMaster && !bIsEditable)
// 	{
// 		BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Hovered);
// 	}
// }
// 
// void SDTHeaderRow::OnMouseLeave(const FPointerEvent& MouseEvent)
// {
// 	if (bIsEditable) return;
// 
// 	if (!bIsMaster && !bIsEditable)
// 	{
// 		BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Normal);
// 	}
// }
// 

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

		SHorizontalBox::FSlot& PosSlot = MainContainer->AddSlot().Padding((bIsMaster) ? DataTableStyle->HeaderStyle.Margin : DataTableStyle->BodyStyle.GeneralMargin);

		
		FString FormattedText;
		if (bIsMaster)
		{
			FormattedText = ProcessTextSize(Fields[i].FieldName.ToString(), maxTextSize);
		}
		else
		{
			FormattedText = ProcessTextSize(Values[i], maxTextSize);
		}

		TSharedPtr<SDTColumn> Col;
		PosSlot[
			SAssignNew(Col,SDTColumn)
				.Value(FText::FromString(FormattedText))
				.DataTableStyle(DataTableStyle)
				.Editable(bIsEditable)
				.ColumnIndex(i)
				.OnColumnChanged(this, &SDTHeaderRow::OnColumnChanged)
				.bIsMaster(bIsMaster)
		];

		ColumnIDs.Add(i);
		Columns.Add(Col);
	}

	if (bIsMaster)
	{
		/*BackgroundBorder->SetBorderImage(&DataTableStyle->HeaderStyle.HeaderBrush);*/
	}
	else
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

void SDTHeaderRow::OnColumnChanged(const int32& ColumnIndex, const FString& Value)
{
	if (OnDTRowChanged.IsBound())
	{
		OnDTRowChanged.ExecuteIfBound(RowIndex, ColumnIndex, Value);
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
	while (out.Len() < Size)
	{
		out += " ";
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

