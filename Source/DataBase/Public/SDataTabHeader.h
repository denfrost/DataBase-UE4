#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataTab.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

class SDataTabHeader : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDataTabHeader)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
		, _VarName(FText::FromString("None"))
	{}

	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(FText, VarName)

	SLATE_END_ARGS()

public:

	TSharedPtr<class STextBlock> TextBlock;
	const FDataTableStyle* DataTableStyle;
	FText VariableName;

	void Construct(const FArguments& InArgs);
	~SDataTabHeader();
};