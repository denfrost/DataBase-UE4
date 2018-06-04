#include "K2Node_GetRowData.h"
#include "Editor/BlueprintGraph/Classes/EdGraphSchema_K2.h"
#include "DTFunctionLibrary.h"
#include "Editor/BlueprintGraph/Public/BlueprintNodeSpawner.h"
#define LOCTEXT_NAMESPACE "K2Node_GetRowData"

struct UK2Node_GetRowDataHelper
{
	static FName DataObjectPinName;
	static FName RowPinName;
};

FName UK2Node_GetRowDataHelper::DataObjectPinName(*LOCTEXT("InDTPinName", "InDT").ToString());
FName UK2Node_GetRowDataHelper::RowPinName(*LOCTEXT("InRowPinName", "InRow").ToString());

UK2Node_GetRowData::UK2Node_GetRowData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
/*	NodeTooltip = LOCTEXT("NodeTooltip", "Creates a new Item Data");*/
}

void UK2Node_GetRowData::AllocateDefaultPins()
{
	const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

	// Add execution pins
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	// Add DataTable pin
	UEdGraphPin* DataTablePin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UDataObject::StaticClass(), UK2Node_GetRowDataHelper::DataObjectPinName);

	// Add RawData
	UEdGraphPin* RowDataStruct = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FRowData::StaticStruct(), UK2Node_GetRowDataHelper::RowPinName);

	// Result pin
	UEdGraphPin* ResultPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, UEdGraphSchema_K2::PN_ReturnValue);

	Super::AllocateDefaultPins();
}

FText UK2Node_GetRowData::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Get Row As Struct 1000");
}

FText UK2Node_GetRowData::GetTooltipText() const
{
	return FText::FromString("get your data as a fancy struct, your struct should be defined in your data object");
}

FSlateIcon UK2Node_GetRowData::GetIconAndTint(FLinearColor& OutColor) const
{
	OutColor = GetNodeTitleColor();
	static FSlateIcon Icon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
	return Icon;
}

void UK2Node_GetRowData::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
}

void UK2Node_GetRowData::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	// actions get registered under specific object-keys; the idea is that 
	// actions might have to be updated (or deleted) if their object-key is  
	// mutated (or removed)... here we use the node's class (so if the node 
	// type disappears, then the action should go with it)
	UClass* ActionKey = GetClass();
	// to keep from needlessly instantiating a UBlueprintNodeSpawner, first   
	// check to make sure that the registrar is looking for actions of this type
	// (could be regenerating actions for a specific asset, and therefore the 
	// registrar would only accept actions corresponding to that asset)
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}


FText UK2Node_GetRowData::GetMenuCategory() const
{
	return FText::FromString("Data Table");
}

#undef LOCTEXT_NAMESPACE