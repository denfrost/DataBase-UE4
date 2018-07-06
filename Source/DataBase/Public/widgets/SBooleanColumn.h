#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"


class SBooleanColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SBooleanColumn)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_EVENT(FOnTextCommitted, OnTextCommitted)
	SLATE_END_ARGS()

	
	bool bValue = false;

	TSharedPtr<class SCheckBox> checkBox;
	const FDataTableStyle* DataTableStyle;

	FOnTextCommitted OnTextCommitted;

public:

	void Construct(const FArguments& InArgs);
	~SBooleanColumn();

	void OnValueChanged(ECheckBoxState checkState);

};