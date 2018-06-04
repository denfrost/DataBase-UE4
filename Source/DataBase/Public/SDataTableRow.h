#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

class SDataTableRow : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDataTableRow)
		: _Style()
	{}

	SLATE_ATTRIBUTE(const FSlateBrush*, Style)
	SLATE_ARGUMENT(FString, Value)
	SLATE_ARGUMENT(FSlateColor, TextColor)
	SLATE_ARGUMENT(FSlateFontInfo, FontInfo)
	SLATE_ARGUMENT(ETextJustify::Type, Justification)

	SLATE_END_ARGS()

public:

	TSharedPtr<class STextBlock> TextBlock;
	ETextJustify::Type Justification;
	TAttribute< const FSlateBrush* > Style;

	FString Value;
	FSlateColor TextColor;
	FSlateFontInfo FontInfo;

	void Construct(const FArguments& InArgs);
	~SDataTableRow();
};