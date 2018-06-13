#include "SDTColumn.h"
#include "Runtime/Slate/Public/Widgets/Input/SEditableTextBox.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"

void SDTColumn::OnTextCommitted(const FText& InText, ETextCommit::Type CommitedType)
{
	if (OnColumnChanged.IsBound())
	{
		OnColumnChanged.Execute(ColumnIndex, InText.ToString());
	}
}

void SDTColumn::SetFontAndColor(const FDataTableStyleOverride& InDTStyleOverride)
{
	if (TextBox.IsValid())
	{
		TextBox->SetFont(InDTStyleOverride.Font);
		TextBox->SetJustification(InDTStyleOverride.Justification);
		TextBox->SetColorAndOpacity(InDTStyleOverride.Color);
	}
}

void SDTColumn::Construct(const FArguments& InArgs)
{
	DataTableStyle = InArgs._DataTableStyle;
	Value = InArgs._Value;
	bIsEditable = InArgs._Editable;
	OnColumnChanged = InArgs._OnColumnChanged;
	ColumnIndex = InArgs._ColumnIndex;
	bIsMaster = InArgs._bIsMaster;


	if (!bIsEditable)
	{
		ChildSlot[
			SAssignNew(TextBox, STextBlock).Text(Value)
				.Font((bIsMaster) ? DataTableStyle->HeaderStyle.Font : DataTableStyle->BodyStyle.Font)
				.ColorAndOpacity((bIsMaster) ? DataTableStyle->HeaderStyle.TextColorAndOpacity : DataTableStyle->BodyStyle.TextColorAndOpacity)
		];

		
		TextBox->SetJustification((bIsMaster) ? DataTableStyle->HeaderStyle.Justification : DataTableStyle->BodyStyle.Justification);
	}
	else
	{
		ChildSlot[

			SAssignNew(EditableTextBox, SEditableTextBox)
				.Style(&FDataTableEditableTextStyle::GetDefault().EditableTextStyle)
				.OnTextCommitted(this, &SDTColumn::OnTextCommitted)
				.Text(Value)
		];
	}	
}

FString SDTColumn::GetValueAsString()
{
	return Value.ToString();
}

SDTColumn::~SDTColumn()
{

}

