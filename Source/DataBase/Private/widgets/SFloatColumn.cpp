#include "SFloatColumn.h"
#include "Runtime/Slate/Public/Widgets/Input/SSpinBox.h"
SFloatColumn::~SFloatColumn()
{

}

void SFloatColumn::Construct(const FArguments& InArgs)
{
	FText InValue = InArgs._Value;
	DataTableStyle = InArgs._DataTableStyle;
	OnTextCommitted = InArgs._OnTextCommitted;

	Value = FCString::Atof(*InValue.ToString());

	ChildSlot[
		SAssignNew(SpinBox, SSpinBox<float>)
			.Value(Value)
			.Style(&DataTableStyle->SpinBoxStyle)
			.OnValueCommitted(this, &SFloatColumn::OnValueChanged)
			.MinValue(-32000)
			.MaxValue(32000)
	];

}

void SFloatColumn::OnValueChanged(float InValue, ETextCommit::Type)
{
	FText NewValue = FText::FromString(FString::SanitizeFloat(InValue));
	OnTextCommitted.ExecuteIfBound(NewValue, ETextCommit::OnEnter);
}

