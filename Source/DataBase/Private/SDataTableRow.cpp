#include "SDataTableRow.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"

void SDataTableRow::Construct(const FArguments& InArgs)
{
	Style = InArgs._Style;
	Value = InArgs._Value;
	TextColor = InArgs._TextColor;
	FontInfo = InArgs._FontInfo;
	Justification = InArgs._Justification;

	ChildSlot[

		SNew(SBorder)
			.BorderImage(Style)
			.Padding(FMargin(0, 0, 0, 0))
			[
				SAssignNew(TextBlock, STextBlock)
				.Text(FText::FromString(Value))
				.ColorAndOpacity(TextColor)
			]
	];

	TextBlock->SetFont(FontInfo);
	TextBlock->SetJustification(Justification);
}

SDataTableRow::~SDataTableRow()
{

}

