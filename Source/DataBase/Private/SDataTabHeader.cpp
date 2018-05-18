#include "SDataTabHeader.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"


void SDataTabHeader::Construct(const FArguments& InArgs)
{
	Style = InArgs._Style;
	VariableName = InArgs._VarName;
	TextColor = InArgs._TextColor;
	FontInfo = InArgs._FontInfo;
	Justification = InArgs._Justification;

	ChildSlot[

		SNew(SBorder)
			.BorderImage(Style)
			.Padding(FMargin(0, 0, 0, 0))
			[
				SAssignNew(TextBlock, STextBlock)
				.Text(VariableName)
				.ColorAndOpacity(TextColor)
			]
	];

	TextBlock->SetFont(FontInfo);
	TextBlock->SetJustification(Justification);
}

SDataTabHeader::~SDataTabHeader()
{

}
