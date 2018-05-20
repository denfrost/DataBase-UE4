#include "SStringColumn.h"
#include "Runtime/Slate/Public/Widgets/Input/SEditableTextBox.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"

void SStringColumn::OnTextCommitted(const FText& InText, ETextCommit::Type CommitedType)
{
	OnColumnChanged.ExecuteIfBound( ColumnIndex, InText.ToString());
}

void SStringColumn::Construct(const FArguments& InArgs)
{
	Style = InArgs._Style;
	Value = InArgs._Value;
	bIsEditable = InArgs._Editable;
	OnColumnChanged = InArgs._OnColumnChanged;
	ColumnIndex = InArgs._ColumnIndex;

	TSharedPtr<SWidget> Widget;
	if (bIsEditable)
	{
		SAssignNew(Widget, SEditableTextBox)
/*			.Style(&Style->TextBoxStyle)*/
			.Text(Value)
			.OnTextCommitted(this, &SStringColumn::OnTextCommitted);
	}
	else
	{
		SAssignNew(Widget, STextBlock)
			.Text(Value);
	}

	ChildSlot[
		Widget->AsShared()
	];
}

SStringColumn::~SStringColumn()
{

}

