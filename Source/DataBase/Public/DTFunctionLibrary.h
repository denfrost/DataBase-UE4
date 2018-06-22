#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataObject.h"
#include "DataTab.h"
#include "DTFunctionLibrary.generated.h"



UCLASS()
class DATABASE_API UDTFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Data Table")
		static bool LoadCSV(UDataObject* DataToFill, const FString& InFile, bool bSkipFirstLine = true, bool bCastOnUpdate = false);

	UFUNCTION(BlueprintCallable, Category = "Data Table")
		static bool ExportCSV(UDataObject* DataObject, const FString& ResultFile);

	UFUNCTION(BlueprintCallable, Category = "Data Table")
		static bool IsValidCriteria(const TArray<FString>& Values, const TArray<FDTCriteria>& NewCriteria);

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "Data Table", meta = (WorldContext = "WorldContextObject", CustomStructureParam = "OutRow"))//*, BlueprintInternalUseOnly = "true"*/))
		static void GetRowAsStruct(UObject* WorldContextObject, UDataObject* InDT, FRowData InRow, UScriptStruct* OutRow);


	DECLARE_FUNCTION(execGetRowAsStruct)
	{
		P_GET_OBJECT(UObject, WorldContextObject);
		P_GET_OBJECT(UDataObject, InDT);
		P_GET_STRUCT(FRowData, InRow);

		Stack.Step(Stack.Object, NULL);
		UStructProperty* StructProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);
		void* StructPtr = Stack.MostRecentPropertyAddress;

		
		P_FINISH;

		if (!InDT) return;

		int32 i = -1;
		for (TFieldIterator<UProperty> It(StructProperty->Struct); It; ++It)
		{
			i++;
			UProperty* Property = *It;
			if (InDT->Fields.IsValidIndex(i) && InRow.Inputs.IsValidIndex(i))
			{
				switch (InDT->Fields[i].Type)
				{
				case EDataTableTypes::Boolean:
				{
					if (UBoolProperty* BoolProperty = Cast<UBoolProperty>(Property))
					{
						bool valBool = false;
						if (InRow.Inputs[i].Contains("true") || InRow.Inputs[i].Contains("0"))
						{
							valBool = true;
						}
						BoolProperty->SetPropertyValue_InContainer(StructPtr, valBool);
						continue;
					}
					break;
				}
				case EDataTableTypes::Integer:
				{
					if (UIntProperty* IntProperty = Cast<UIntProperty>(Property))
					{
						int32 valInt = FCString::Atoi(*InRow.Inputs[i]);
						IntProperty->SetPropertyValue_InContainer(StructPtr, valInt);
						continue;
					}
					break;
				}
				case EDataTableTypes::Floating:
				{
					if (UFloatProperty* FloatProperty = Cast<UFloatProperty>(Property))
					{
						float valfloat = FCString::Atof(*InRow.Inputs[i]);
						FloatProperty->SetPropertyValue_InContainer(StructPtr, valfloat);
						continue;
					}
					break;
				}
				case EDataTableTypes::String:
				{
					if (UStrProperty* StringProperty = Cast<UStrProperty>(Property))
					{
						StringProperty->SetPropertyValue_InContainer(StructPtr, InRow.Inputs[i]);
						continue;
					}
					break;
				}
				default:
					break;
				}
			}
		}

	}
};
