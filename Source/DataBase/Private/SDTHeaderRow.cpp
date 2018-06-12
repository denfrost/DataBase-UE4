#include "SDTHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Widgets/Layout/SSplitter.h"
#include "SDTColumn.h"

// FReply SDTHeaderRow::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
// {
// 	if (bIsEditable) return  FReply::Handled();
// 
// 	if (IsEnabled() && (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || InMouseEvent.IsTouchEvent()))
// 	{
// 		if (!bIsMaster)
// 		{
// 			BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Pressed);
// 		}
// 		OnRowDoubleClicked.ExecuteIfBound(RowIndex, Values);
// 		return FReply::Handled();
// 	}
// 	return FReply::Unhandled();
// }

void SDTHeaderRow::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	
	if (bPressed)
	{
		Tempo += InDeltaTime;
		
	}
	else
	{
		if (Tempo > 0 && Tempo < .4f)
		{
			Tempo = 0;
			OnRowClicked.ExecuteIfBound(RowIndex, Values);
		}
	}
	
}


FReply SDTHeaderRow::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bIsEditable) return  FReply::Handled();

	if (IsEnabled() && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent()))
	{
		Tempo = 0;
		bPressed = true;
		if (!bIsMaster)
		{
			BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Pressed);
		}
		Invalidate(EInvalidateWidget::Layout);
		return FReply::Handled().CaptureMouse(AsShared());
	}
	return FReply::Handled();
}

FReply SDTHeaderRow::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bIsEditable) return  FReply::Handled();

	
	if (IsEnabled() && (MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton || MouseEvent.IsTouchEvent()))
	{
		bPressed = false;
		if (!bIsMaster)
		{
			FVector2D Pos = MyGeometry.AbsoluteToLocal(MouseEvent.GetScreenSpacePosition());
			if (Pos.X > 0 && Pos.Y > 0)
			{
				BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Hovered);
			}
			else
			{
				BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Normal);
			}
			
		}
		return FReply::Handled();
	}
	return FReply::Handled();
}

void SDTHeaderRow::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (bIsEditable) return;

	if (!bIsMaster && !bIsEditable)
	{
		BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Hovered);
	}
}

void SDTHeaderRow::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	if (bIsEditable) return;

	if (!bIsMaster && !bIsEditable)
	{
		BackgroundBorder->SetBorderImage(&DataTableStyle->BodyStyle.Normal);
	}
}


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
		
		TSharedPtr<SDTColumn> Col;
		PosSlot[
			SAssignNew(Col,SDTColumn)
				.Value((bIsMaster) ? Fields[i].FieldName : FText::FromString(Values[i]))
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
		BackgroundBorder->SetBorderImage(&DataTableStyle->HeaderStyle.HeaderBrush);
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

	ChildSlot
		[
			SAssignNew(BackgroundBorder, SBorder)
			.HAlign(HAlign_Fill)
			.BorderImage((bIsMaster) ? &DataTableStyle->HeaderStyle.HeaderBrush : &DataTableStyle->BodyStyle.Normal)
			[
				SAssignNew(MainContainer, SHorizontalBox)
			]
		];

/*	UpdateWidget();*/
}

SDTHeaderRow::~SDTHeaderRow()
{

}

