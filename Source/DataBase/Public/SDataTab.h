#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"

class SDataTabHeader;

class DATABASE_API SDataTab : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDataTab)
		: _HeaderStyle()
		, _ColumnDescriptions()
	{}
	/** Header Styler*/
	SLATE_ARGUMENT(const FDataTableHeaderStyle*, HeaderStyle)
	SLATE_ARGUMENT(TArray<FDataTableColumnDescription>, ColumnDescriptions)
	SLATE_END_ARGS()

public:

	TSharedPtr<class SHeaderRow> Header;
	const FDataTableHeaderStyle* HeaderStyle;
	TArray<FDataTableColumnDescription> ColumnDescriptions;

	//DataTab
	virtual void UpdateWidget();

	void Construct(const FArguments& InArgs);
	~SDataTab();
};