#include "SDataTabHeader.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"


void SDataTabHeader::Construct(const FArguments& InArgs)
{
	DataTableStyle = InArgs._DataTableStyle;
	VariableName = InArgs._VarName;

	ChildSlot[

		SNew(SBorder)
/*			.BorderImage(&DataTableStyle.HeaderStyle->HeaderBrush)*/
/*			.Padding(HeaderStyle->Margin)*/
			[
				SAssignNew(TextBlock, STextBlock)
				.Text(VariableName)
/*				.ColorAndOpacity(HeaderStyle->TextColorAndOpacity)*/
			]
	];

// 	TextBlock->SetFont(HeaderStyle->Font);
// 	TextBlock->SetJustification(HeaderStyle->Justification);
}

SDataTabHeader::~SDataTabHeader()
{

}
