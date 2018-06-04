#include "DTFunctionLibrary.h"

void UDTFunctionLibrary::GetRowAsStruct(UObject* WorldContextObject, UDataObject* InDT, FRowData InRow, UScriptStruct* OutRow/*, UScriptStruct*& Return*/)
{
// 	if (!InDT) return;
// 
// 	
// 	int32 index = -1;
// 	for (TFieldIterator<UProperty> It(OutRow); It; ++It)
// 	{
// 		index++;
// 		UProperty* Property = *It;
// 		if (Property)
// 		{
// 			UE_LOG(LogTemp, Log, TEXT("name %s"),*Property->GetName());
// 
// 			if (InDT->Fields.IsValidIndex(index) && InRow.Inputs.IsValidIndex(index))
// 			{
// 				switch (InDT->Fields[index].Type)
// 				{
// 				case EDataTableTypes::Boolean:
// 				{
// 					break;
// 				}
// 				case EDataTableTypes::Floating:
// 				{
// 					float valFloat = FCString::Atof(*InRow.Inputs[index]);
// 					break;
// 				}
// 				case EDataTableTypes::Integer:
// 				{
// 					if (UIntProperty* IntProperty = Cast<UIntProperty>(Property))
// 					{
// 						UE_LOG(LogTemp, Log, TEXT("int"));
// 						int32 valInt = FCString::Atoi(*InRow.Inputs[index]);
// 						IntProperty->SetPropertyValue_InContainer(OutRow, valInt);
// 					}
// 					break;
// 				}
// 				case EDataTableTypes::String:
// 				{
// 
// 					break;
// 				}
// 				default:
/*					break;*/
// 				}
// 
// 				
// 			}
// 		}
// 	}
	
}
