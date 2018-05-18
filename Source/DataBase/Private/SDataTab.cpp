#include "SDataTab.h"
#include "Runtime/Slate/Public/Widgets/Views/SHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "SDataTabHeader.h"

void SDataTab::UpdateWidget()
{
	ensure(Header.IsValid());
	ensure(HeaderStyle);

	Header->ClearColumns();
	for (int32 i = 0; i < ColumnDescriptions.Num(); i++)
	{
		FString ID = "Header_" + FString::FromInt(i);
		Header->AddColumn(
			SHeaderRow::Column(FName(*ID))
			.FillWidth(ColumnDescriptions[i].ColumnWidth)
			.HeaderContent()
			[
				SNew(SDataTabHeader)
				.VarName(ColumnDescriptions[i].FieldName)
				.TextColor(HeaderStyle->TextColorAndOpacity)
				.FontInfo(HeaderStyle->Font)
				.Justification(HeaderStyle->Justification)
				.Style(&HeaderStyle->Header)
			]
		);
	}
}

void SDataTab::Construct(const FArguments& InArgs)
{
	HeaderStyle = InArgs._HeaderStyle;
	if (!HeaderStyle)
	{
		HeaderStyle = &FDataTableHeaderStyle::GetDefault();
	}

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

