#include "SDTColumn.h"
#include "Runtime/Slate/Public/Widgets/Input/SEditableTextBox.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Layout/SScaleBox.h"
#include "SBooleanColumn.h"
#include "SIntegerColumn.h"
#include "SFloatColumn.h"
#include "SObjectColumn.h"

void SDTColumn::OnTextCommitted(const FText& InText, ETextCommit::Type CommitedType)
{
	OnColumnChanged.ExecuteIfBound(ColumnIndex, InText.ToString(), nullptr);
}

void SDTColumn::OnObjectChanged(const FText& InText, const UObject* NewObjectRef)
{
	OnColumnChanged.ExecuteIfBound(ColumnIndex, InText.ToString(), NewObjectRef);
}

TSharedPtr<SWidget> SDTColumn::GenerateEditWidget(EDataTableTypes InType, const FText& InValue)
{
	if (bIsMaster)
	{
		InType = EDataTableTypes::String;
	}

	TSharedPtr<SWidget> Widget;
	switch (InType)
	{
	case EDataTableTypes::Boolean:
		SAssignNew(Widget, SBooleanColumn)
			.DataTableStyle(&FDataTableStyle::GetDefault())
			.OnTextCommitted(this, &SDTColumn::OnTextCommitted)
			.Value(InValue);
		break;
	case EDataTableTypes::String:
		SAssignNew(Widget, SEditableTextBox)
			.Style(&FDataTableEditableTextStyle::GetDefault().EditableTextStyle)
			.OnTextCommitted(this, &SDTColumn::OnTextCommitted)
			.Text(InValue);
		break;
	case EDataTableTypes::Floating:
		SAssignNew(Widget, SFloatColumn)
			.DataTableStyle(&FDataTableStyle::GetDefault())
			.OnTextCommitted(this, &SDTColumn::OnTextCommitted)
			.Value(InValue);
		break;
	case EDataTableTypes::Integer:
		SAssignNew(Widget, SIntegerColumn)
			.DataTableStyle(&FDataTableStyle::GetDefault())
			.OnTextCommitted(this, &SDTColumn::OnTextCommitted)
			.Value(InValue);
		break;
	case EDataTableTypes::UEObject:
		SAssignNew(Widget, SObjectColumn)
			.DataTableStyle(&FDataTableStyle::GetDefault())
			.OnObjectChange(this, &SDTColumn::OnObjectChanged)
			.FilterClass(FilterClass)
			.Value(InValue);
		break;
	default:
		SAssignNew(Widget, SEditableTextBox)
			.Style(&FDataTableEditableTextStyle::GetDefault().EditableTextStyle)
			.OnTextCommitted(this, &SDTColumn::OnTextCommitted)
			.Text(InValue);
		break;
	}

	return Widget;
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
	Type = InArgs._Type;
	bIsEditable = InArgs._Editable;
	OnColumnChanged = InArgs._OnColumnChanged;
	ColumnIndex = InArgs._ColumnIndex;
	bIsMaster = InArgs._bIsMaster;
	FilterClass = InArgs._FilterClass;

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
			GenerateEditWidget(Type, Value)->AsShared()
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

