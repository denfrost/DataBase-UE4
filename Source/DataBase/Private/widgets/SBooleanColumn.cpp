#include "SBooleanColumn.h"
#include "Widgets/Input/SCheckBox.h"


void SBooleanColumn::Construct(const FArguments& InArgs)
{
	FText InValue = InArgs._Value;
	DataTableStyle = InArgs._DataTableStyle;
	OnTextCommitted = InArgs._OnTextCommitted;

	if (InValue.ToString().Contains("True"))
	{
		bValue = true;
	}
	else
	{
		int32 intValue = FCString::Atoi(*InValue.ToString());
		bValue = (intValue > 0) ? true : false;
	}
	ECheckBoxState checkState = (bValue) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	ChildSlot[
		SAssignNew(checkBox, SCheckBox).OnCheckStateChanged(this, &SBooleanColumn::OnValueChanged).IsChecked(checkState)
	];
}

SBooleanColumn::~SBooleanColumn()
{

}

void SBooleanColumn::OnValueChanged(ECheckBoxState checkState)
{
	FText NewValue = (checkState == ECheckBoxState::Checked) ? FText::FromString("1") : FText::FromString("0");
	OnTextCommitted.ExecuteIfBound(NewValue, ETextCommit::OnEnter);
}

