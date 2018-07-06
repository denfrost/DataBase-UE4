#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"
#include "Public/Framework/SlateDelegates.h"

class SFloatColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SFloatColumn)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_EVENT(FOnTextCommitted, OnTextCommitted)
	SLATE_END_ARGS()


	float Value = 0;

	TSharedPtr<class SSpinBox<float>> SpinBox;
	const FDataTableStyle* DataTableStyle;

	FOnTextCommitted OnTextCommitted;

public:

	void Construct(const FArguments& InArgs);
	~SFloatColumn();

	void OnValueChanged(float InValue, ETextCommit::Type);

};