#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"

class SDataTabHeader : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SDataTabHeader)
		: _Style()
	{}

	SLATE_ATTRIBUTE(const FSlateBrush*, Style)
	SLATE_ARGUMENT(FText, VarName)
	SLATE_ARGUMENT(FSlateColor, TextColor)
	SLATE_ARGUMENT(FSlateFontInfo, FontInfo)
	SLATE_ARGUMENT(ETextJustify::Type, Justification)

	SLATE_END_ARGS()

public:

	TSharedPtr<class STextBlock> TextBlock;
	ETextJustify::Type Justification;
	TAttribute< const FSlateBrush* > Style;

	FText VariableName;
	FSlateColor TextColor;
	FSlateFontInfo FontInfo;

	void Construct(const FArguments& InArgs);
	~SDataTabHeader();
};