#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataObject.h"
#include "DataTab.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_ThreeParams(FOnRowChanged, const int32&, const int32&, const FString&)

class SDataTableRow : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDataTableRow)
		: _Style()
	{}

	SLATE_ARGUMENT(TArray<FString>, Values)
	SLATE_ARGUMENT(const FDataTableStyle*, Style)
	SLATE_ARGUMENT(int32, Index)
	SLATE_ARGUMENT(TArray<FDataTableFieldDescription>, Fields)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_EVENT(FOnRowChanged, OnRowChanged)


	SLATE_END_ARGS()

private:
	FOnRowChanged OnRowChanged;

public:
	TArray<FString> Values;
	const FDataTableStyle* Style;
	int32 RowIndex;
	TArray<FDataTableFieldDescription> Fields;
	bool bIsEditable;

	TSharedPtr<class SDTHeaderRow> Row;

	void UpdateRow(const TArray<FString> InValues);

	void OnColumnChanged( const int32& ColumnIndex, const FString& Value);

public:
	void Construct(const FArguments& InArgs);
	~SDataTableRow();
};