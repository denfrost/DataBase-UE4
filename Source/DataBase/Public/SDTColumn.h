#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataTab.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_ThreeParams(FOnColumnChanged, const int32&, const FString&, const UObject*);

class SDTColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDTColumn)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
		, _Editable(false)
		, _bIsMaster(false)
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(EDataTableTypes, Type)
	SLATE_ARGUMENT(UClass*, FilterClass)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_ARGUMENT(int32, ColumnIndex)
	SLATE_ARGUMENT(bool, bIsMaster)
	SLATE_EVENT(FOnColumnChanged, OnColumnChanged)

	SLATE_END_ARGS()

public:
	FText Value;
	EDataTableTypes Type;
	UClass* FilterClass;

	const FDataTableStyle* DataTableStyle;
	bool bIsEditable;
	bool bIsMaster;
	int32 RowIndex;
	int32 ColumnIndex;
	TSharedPtr<class STextBlock> TextBox;
	TSharedPtr<class SEditableTextBox> EditableTextBox;

	FOnColumnChanged OnColumnChanged;

private:
	void OnTextCommitted(const FText& InText, ETextCommit::Type CommitedType);
	void OnObjectChanged(const FText& InText, const UObject* NewObjectRef);
	TSharedPtr<SWidget> GenerateEditWidget(EDataTableTypes InType, const FText& InValue);

public:
	void SetFontAndColor(const FDataTableStyleOverride& InDTStyleOverride);
	void Construct(const FArguments& InArgs);

	FString GetValueAsString();
	~SDTColumn();
};