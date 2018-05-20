#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataTab.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_TwoParams(FOnColumnChanged, const int32&, const FString&);

class SStringColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SStringColumn)
		: _Style(&FDataTableStyle::GetDefault())
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(const FDataTableStyle*, Style)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_ARGUMENT(int32, ColumnIndex)
	SLATE_EVENT(FOnColumnChanged, OnColumnChanged)

	SLATE_END_ARGS()

public:
	FText Value;
	const FDataTableStyle* Style;
	bool bIsEditable;
	int32 RowIndex;
	int32 ColumnIndex;

	FOnColumnChanged OnColumnChanged;

private:
	void OnTextCommitted(const FText& InText, ETextCommit::Type CommitedType);

public:
	void Construct(const FArguments& InArgs);
	~SStringColumn();
};