#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataTab.h"
#include "DataObject.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_FourParams(FOnDTRowChanged, const int32&, const int32&, const FString&, const UObject* )
DECLARE_DELEGATE_TwoParams(FOnRowClicked, const int32&,const TArray<FString>&)

class SDTHeaderRow : public SCompoundWidget
{

	SLATE_BEGIN_ARGS(SDTHeaderRow)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
		, _RowIndex(-1)
		, _Editable(false)
		, _bIsMaster(false)
	{}
	/** Header Styler*/
	SLATE_ARGUMENT(TArray<FString>, Values)
	SLATE_ARGUMENT(TArray<FDataTableFieldDescription>, Fields)
	SLATE_ARGUMENT(bool, bIsMaster)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_ARGUMENT(int32, RowIndex)
	SLATE_EVENT(FOnDTRowChanged, OnDTRowChanged)
	SLATE_EVENT(FOnRowClicked, OnRowClicked)
	SLATE_EVENT(FOnRowClicked, OnRowDoubleClicked)
		
	SLATE_END_ARGS()

private:
	TArray<FString> Values;
	TArray<FDataTableFieldDescription> Fields;
	FOnDTRowChanged OnDTRowChanged;
	FOnRowClicked OnRowClicked;
	FOnRowClicked OnRowDoubleClicked;

	const FDataTableStyle* DataTableStyle;
	int32 RowIndex;
	bool bIsEditable;
	bool bIsMaster;

	TSharedPtr<class SBorder> BackgroundBorder;
	TSharedPtr<class SHorizontalBox> MainContainer;
	TArray<TSharedPtr<class SDTColumn>> Columns;
	TArray<int32> ColumnIDs;

	void OnColumnChanged(const int32& ColumnIndex, const FString& Value, const UObject* NewObjReference);
	FReply OnRowBtnClicked();

	int32 getLargestValueTextSize();
	FString ProcessTextSize(const FString& InText, const int32& Size);

public:
	
	bool CheckCriteria(const FDTCriteria& InCriteria);
	void SetColumns(const TArray<FDataTableFieldDescription>& InFields, const TArray<FString>& InValues);
	void UpdateWidget();
	void ClearColumns();
	void OverrideColumnStyle(const FDataTableStyleOverride& InStyle);
	

	void Construct(const FArguments& InArgs);
	~SDTHeaderRow();
};
