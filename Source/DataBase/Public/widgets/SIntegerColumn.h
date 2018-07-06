#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"
#include "Public/Framework/SlateDelegates.h"

class SIntegerColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SIntegerColumn)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_EVENT(FOnTextCommitted, OnTextCommitted)
	SLATE_END_ARGS()


	int32 Value = 0;

	TSharedPtr<class SSpinBox<int32>> SpinBox;
	const FDataTableStyle* DataTableStyle;

	FOnTextCommitted OnTextCommitted;

public:

	void Construct(const FArguments& InArgs);
	~SIntegerColumn();

	void OnValueChanged(int32 InValue, ETextCommit::Type);

};