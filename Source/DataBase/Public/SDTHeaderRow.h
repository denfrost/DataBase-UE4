#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataTab.h"
#include "DataObject.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_ThreeParams(FOnDTRowChanged, const int32&, const int32&, const FString&)

class SDTHeaderRow : public SCompoundWidget
{

	SLATE_BEGIN_ARGS(SDTHeaderRow)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
		, _ID(-1)
		, _HumanEditable(false)
	{}
	/** Header Styler*/
	SLATE_ARGUMENT(TArray<FString>, Values)
	SLATE_ARGUMENT(TArray<FDataTableFieldDescription>, Fields)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(bool, HumanEditable)
	SLATE_ARGUMENT(int32, ID)
	SLATE_EVENT(FOnDTRowChanged, OnDTRowChanged)
		
	SLATE_END_ARGS()

private:
	TArray<FString> Values;
	TArray<FDataTableFieldDescription> Fields;
	FOnDTRowChanged OnDTRowChanged;

	const FDataTableStyle* DataTableStyle;
	int32 ID;
	bool bIsHumanEditable;

	TSharedPtr<class SHorizontalBox> MainContainer;
	TSharedPtr<class SSplitter> Container;
	TArray<int32> ColumnIDs;

	void AddColumn(int32 ID, TSharedRef<SWidget> Widget);

public:
	

	void SetFields(const TArray<FDataTableFieldDescription>& InFields, const TArray<FString>& InValues);
	void ClearColumns();
	

	void Construct(const FArguments& InArgs);
	~SDTHeaderRow();
};
