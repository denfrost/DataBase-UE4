#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"

class SDataTabHeader;
class SDataTableRow;

DECLARE_DELEGATE_ThreeParams(FOnDataTableChanged, const int32&, const int32&, const FString&);

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
	SLATE_EVENT(FOnDataTableChanged, OnDataTableChanged)
	SLATE_ARGUMENT(TWeakObjectPtr<class UDataObject>, DataObject)
	SLATE_ARGUMENT(bool, Editable)
	SLATE_END_ARGS()

private:

	FOnDataTableChanged OnDataTableChanged;
	TWeakObjectPtr<class UDataObject> CurrentDataObject;
	bool bIsEditable;

	TSharedPtr<class SDTHeaderRow> Header;
	const FDataTableStyle* DataTableStyle;
	
	TSharedPtr<class SScrollBox> RowContainer;
	TArray<TSharedPtr<SDTHeaderRow>> Rows;
	
	
	TArray<FDataTableFieldDescription> Fields;

	void OnRowChanged(const int32& RowIndex, const int32& ColumnIndex, const FString& Value);

public:
	//DataTab
	virtual void UpdateWidget();
	void SetFields(const TArray<FDataTableFieldDescription>& InFields);
	void AddRow(TArray<FString>& Values,const bool& bUseWidgets,const bool& bIsEditable);

	void Construct(const FArguments& InArgs);
	~SDataTab();
};