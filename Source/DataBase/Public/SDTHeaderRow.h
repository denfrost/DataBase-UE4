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
		
	SLATE_END_ARGS()

private:
	TArray<FString> Values;
	TArray<FDataTableFieldDescription> Fields;
	FOnDTRowChanged OnDTRowChanged;

	const FDataTableStyle* DataTableStyle;
	int32 RowIndex;
	bool bIsEditable;
	bool bIsMaster;

	TSharedPtr<class SBorder> BackgroundBorder;
	TSharedPtr<class SHorizontalBox> MainContainer;
	TArray<TSharedPtr<class SDTColumn>> Columns;
	TArray<int32> ColumnIDs;

	void OnColumnChanged(const int32& ColumnIndex, const FString& Value);

public:
	
	//BEGIN SWidget
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	//END SWidget

	void SetColumns(const TArray<FDataTableFieldDescription>& InFields, const TArray<FString>& InValues);
	void UpdateWidget();
	void ClearColumns();
	void OverrideColumnStyle(const FDataTableStyleOverride& InStyle);
	

	void Construct(const FArguments& InArgs);
	~SDTHeaderRow();
};
