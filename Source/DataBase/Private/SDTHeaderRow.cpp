#include "SDTHeaderRow.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Widgets/Layout/SSplitter.h"

void SDTHeaderRow::SetFields(const TArray<FDataTableFieldDescription>& InFields, const TArray<FString>& InValues)
{
	ClearColumns();
	Values = InValues;
	Fields = InFields;
	ensure(Values.Num() == Fields.Num());
	for (int32 ID = 0; ID < Values.Num(); ID++)
	{
// 		AddColumn(
// 			ID
// 			, SNew(SDataTabHeader)
// 			.VarName(Fields[ID].FieldName)
// 			.DataTableStyle(DataTableStyle)
// 		);
	}
}

void SDTHeaderRow::ClearColumns()
{
	ColumnIDs.Empty();
	MainContainer->ClearChildren();

	if (bIsHumanEditable)
	{
		SHorizontalBox::FSlot& PosSlot = MainContainer->AddSlot().Padding(0);
		//PosSlot.AutoHeight();
		PosSlot[
			SAssignNew(Container, SSplitter)
		];
	}
}

void SDTHeaderRow::AddColumn(int32 ID, TSharedRef<SWidget> Widget)
{
	ensure(!ColumnIDs.Contains(ID));

	if (bIsHumanEditable && Container.IsValid())
	{
		SSplitter::FSlot& PosSlot = Container->AddSlot();
		//PosSlot.AutoHeight();
		PosSlot[
			Widget
		];
	}
	else
	{
		SHorizontalBox::FSlot& PosSlot = MainContainer->AddSlot();
		//PosSlot.AutoHeight();
		PosSlot[
			Widget
		];
	}
	
}

void SDTHeaderRow::Construct(const FArguments& InArgs)
{
	ID = InArgs._ID;
	Values = InArgs._Values;
	Fields = InArgs._Fields;
	DataTableStyle = InArgs._DataTableStyle;
	bIsHumanEditable = InArgs._HumanEditable;

	TSharedPtr<SWidget> Widget;
	if (bIsHumanEditable)
	{
		SAssignNew(Container, SSplitter)
			.PhysicalSplitterHandleSize(0)
			.HitDetectionSplitterHandleSize(0)
			.MinimumSlotHeight(0);

		Widget = Container;
	}
	else
	{
		Widget = SNew(SHorizontalBox);
	}

	ChildSlot
		[

			SAssignNew(MainContainer, SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Fill)
			.Padding(FMargin(0,0,10,0))
			[
				Widget->AsShared()
			]
		];
}

SDTHeaderRow::~SDTHeaderRow()
{

}

