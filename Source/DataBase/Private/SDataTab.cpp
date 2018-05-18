#include "SDataTab.h"
#include "Runtime/Slate/Public/Widgets/Views/SHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "SDataTabHeader.h"

void SDataTab::UpdateWidget()
{
	Header->ClearColumns();
	for (int32 i = 0; i < ColumnDescriptions.Num(); i++)
	{
// 		FString ID = "Header_" + FString::FromInt(i);
// 		Header->AddColumn(
// 			SHeaderRow::Column(FName(*ID))
// 			.FillWidth(ColumnDescriptions[i].ColumnWidth)
// 			.HeaderContent()
// 			[
// 				SNew(SDataTabHeader)
// 				.VarName(ColumnDescriptions[i].FieldName)
// 				.TextColor(HeaderStyle.Get()->TextColorAndOpacity)
// 				.FontInfo(HeaderStyle.Get()->Font)
// 				.Justification(HeaderStyle.Get()->Justification)
// 				.Style(&HeaderStyle.Get()->Header)
// 			]
// 		);
	}
}

void SDataTab::Construct(const FArguments& InArgs)
{
	HeaderStyle = InArgs._HeaderStyle;
	ColumnDescriptions = InArgs._ColumnDescriptions;

	ChildSlot[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		[
			SAssignNew(Header,SHeaderRow)
		]
	];

	UpdateWidget();
}

SDataTab::~SDataTab()
{

}

