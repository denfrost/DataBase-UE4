#include "SDataTableRow.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "SDTHeaderRow.h"
#include "SStringColumn.h"

void SDataTableRow::UpdateRow(const TArray<FString> InValues)
{
	Values = InValues;

	ensure(Row.IsValid());
	Row->ClearColumns();

	for (int32 ID = 0; ID < Values.Num(); ID++)
	{
// 		Row->AddColumn(
// 			ID,
// 			SNew(SStringColumn)
// 			.Value(FText::FromString(Values[ID]))
//  			.Style(Style)
//  			.Editable(bIsEditable)
//  			.ColumnIndex(ID)
// 			.OnColumnChanged(this, &SDataTableRow::OnColumnChanged)
// // 			SHeaderRow::Column(FName(*ID))
// // 			.FillWidth(1)
// // 			.HeaderContent()
// // 			[
// // 				SNew(SStringColumn)
// // 				.Value(FText::FromString(Values[i]))
// // 			.Style(Style)
// // 			.Editable(bIsEditable)
// // 			.ColumnIndex(i)
// // 			.OnColumnChanged(this, &SDataTableRow::OnColumnChanged)
// // 			]
// 		);
	}
}

void SDataTableRow::OnColumnChanged( const int32& ColumnIndex, const FString& Value)
{
	OnRowChanged.ExecuteIfBound(RowIndex, ColumnIndex, Value);
}

void SDataTableRow::Construct(const FArguments& InArgs)
{
	Values = InArgs._Values;
	Style = InArgs._Style;
	RowIndex = InArgs._Index;
	Fields = InArgs._Fields;
	bIsEditable = InArgs._Editable;
	OnRowChanged = InArgs._OnRowChanged;

	ChildSlot[

		SNew(SBorder)
/*			.BorderImage(&Style->Normal)*/
			.Padding(FMargin(0, 0, 0, 0))
			[
				SAssignNew(Row,SDTHeaderRow)
			]
	];

	UpdateRow(Values);
}

SDataTableRow::~SDataTableRow()
{

}

