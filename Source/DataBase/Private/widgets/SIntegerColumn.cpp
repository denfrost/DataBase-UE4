#include "SIntegerColumn.h"
#include "Runtime/Slate/Public/Widgets/Input/SSpinBox.h"

SIntegerColumn::~SIntegerColumn()
{

}

void SIntegerColumn::Construct(const FArguments& InArgs)
{
	FText InValue = InArgs._Value;
	DataTableStyle = InArgs._DataTableStyle;
	OnTextCommitted = InArgs._OnTextCommitted;

	Value = FCString::Atoi(*InValue.ToString());

	ChildSlot[
		SAssignNew(SpinBox, SSpinBox<int32>)
			.Value(Value)
			.Style(&DataTableStyle->SpinBoxStyle)
			.OnValueCommitted(this, &SIntegerColumn::OnValueChanged)
			.MinValue(-32000)
			.MaxValue(32000)
	];
}



void SIntegerColumn::OnValueChanged(int32 InValue, ETextCommit::Type)
{
	FText NewValue = FText::FromString(FString::FromInt(InValue));
	OnTextCommitted.ExecuteIfBound(NewValue, ETextCommit::OnEnter);
}

