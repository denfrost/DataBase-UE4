#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataTab.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_TwoParams(FOnColumnChanged, const int32&, const FString&);

class SDTColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDTColumn)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
		, _Editable(false)
		, _bIsMaster(false)
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_ARGUMENT(int32, ColumnIndex)
	SLATE_ARGUMENT(bool, bIsMaster)
	SLATE_EVENT(FOnColumnChanged, OnColumnChanged)

	SLATE_END_ARGS()

public:
	FText Value;
	const FDataTableStyle* DataTableStyle;
	bool bIsEditable;
	bool bIsMaster;
	int32 RowIndex;
	int32 ColumnIndex;
	TSharedPtr<class STextBlock> TextBox;
	TSharedPtr<class SEditableTextBox> EditableTexBox;

	FOnColumnChanged OnColumnChanged;

private:
	void OnTextCommitted(const FText& InText, ETextCommit::Type CommitedType);
public:
	void SetFontAndColor(const FDataTableStyleOverride& InDTStyleOverride);
	void Construct(const FArguments& InArgs);
	~SDTColumn();
};