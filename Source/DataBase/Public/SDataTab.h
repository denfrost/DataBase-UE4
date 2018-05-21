#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"

class SDataTabHeader;
class SDataTableRow;

DECLARE_DELEGATE_ThreeParams(FOnDataTableChanged, const int32&, const int32&, const FString&);
DECLARE_DELEGATE_TwoParams(FOnDTRowClicked, const int32&, const TArray<FString>&)

class DATABASE_API SDataTab : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDataTab)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
		, _ColumnDescriptions()
		, _Editable(false)
	{}
	/** Header Styler*/
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(TArray<FDataTableFieldDescription>, ColumnDescriptions)
	SLATE_ARGUMENT(TWeakObjectPtr<class UDataObject>, DataObject)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_EVENT(FOnDataTableChanged, OnDataTableChanged)
	SLATE_EVENT(FOnDTRowClicked, OnRowClicked)
	SLATE_EVENT(FOnDTRowClicked, OnRowDoubleClicked)
	SLATE_END_ARGS()


private:
	FOnDTRowClicked OnRowClick;
	FOnDTRowClicked OnRowDoubleClick;
	FOnDataTableChanged OnDataTableChanged;
	TWeakObjectPtr<class UDataObject> CurrentDataObject;
	bool bIsEditable;

	TSharedPtr<class SDTHeaderRow> Header;
	const FDataTableStyle* DataTableStyle;
	
	TSharedPtr<class SScrollBox> RowContainer;
	TArray<TSharedPtr<SDTHeaderRow>> Rows;
	TArray<FDataTableFieldDescription> Fields;

	void OnRowChanged(const int32& RowIndex, const int32& ColumnIndex, const FString& Value);
	void OnRowClicked(const int32& RowIndex, const TArray<FString>& Values);
	void OnRowDoubleClicked(const int32& RowIndex, const TArray<FString>& Values);

public:
	//DataTab
	virtual void UpdateWidget();
	void SetFields(const TArray<FDataTableFieldDescription>& InFields);
	void AddRow(TArray<FString>& Values,const bool& bUseWidgets,const bool& bIsEditable);

	void SetRowStyleOverride(const int32& Index, const FDataTableStyleOverride& InStyle);

	void Construct(const FArguments& InArgs);
	~SDataTab();
};