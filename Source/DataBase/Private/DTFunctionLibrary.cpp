#include "DTFunctionLibrary.h"

bool UDTFunctionLibrary::LoadCSV(UDataObject* DataToFill, const FString& InFile, bool bSkipFirstLine, bool bCastOnUpdate)
{

	if (FPaths::FileExists(InFile) && InFile.Contains(".csv") && DataToFill)
	{
		
		FString Text;
		if (FFileHelper::LoadFileToString(Text, *InFile))
		{
			DataToFill->ClearDataTable();

			TArray<FString> lines;
			const FString csvDelimiter = ",";
			int32 lineCount = Text.ParseIntoArrayLines(lines);

			int32 firstIndex = bSkipFirstLine ? 1 : 0;

			for (int32 i = firstIndex; i < lines.Num(); i++)
			{
				FRowData Row;
				lines[i].ParseIntoArray(Row.Inputs, *csvDelimiter, false);
				EDataTableStatus status = DataToFill->AddRowInfo(Row);
				if (status == EDataTableStatus::Fail)
				{
					UE_LOG(LogTemp, Warning, TEXT("fail adding row to this data table line: %i"), i);
				}
			}

			if (DataToFill->OnDataTableUpdate.IsBound()  && bCastOnUpdate)
			{
				DataToFill->OnDataTableUpdate.Broadcast(true);
			}
			return true;
		}
	}
	return false;
}

bool UDTFunctionLibrary::ExportCSV(UDataObject* DataObject, const FString& ResultFile)
{
	if (DataObject)
	{
		FString Output;
		//Add header line
		for (int32 i = 0; i < DataObject->Fields.Num(); i++)
		{
			if (i < DataObject->Fields.Num() - 1)
			{
				Output += DataObject->Fields[i].FieldName.ToString() + ",";
				continue;
			}
			Output += DataObject->Fields[i].FieldName.ToString() + "\n";
		}
		
		//Add every line
		for (int32 i = 0; i < DataObject->Data.Num(); i++)
		{
			for (int32 j = 0; j < DataObject->Data[i].Inputs.Num(); j++)
			{
				if (j < DataObject->Data[i].Inputs.Num() - 1)
				{
					Output += DataObject->Data[i].Inputs[j] + ",";
					continue;
				}
				Output += DataObject->Data[i].Inputs[j] + "\n";
			}
		}

		//salvar el archivo
		return FFileHelper::SaveStringToFile(Output, *ResultFile);
	}
	return false;
}

bool UDTFunctionLibrary::IsValidCriteria(const TArray<FString>& Values, const TArray<FDTCriteria>& NewCriteria)
{
	for (auto& crit : NewCriteria)
	{
		if (!Values.IsValidIndex(crit.ColumnIndex)) continue;

		if (crit.bIsNumeric)
		{
			float valueFloat = FCString::Atof(*Values[crit.ColumnIndex]);
			if (valueFloat > crit.NumericThreshold.X && valueFloat < crit.NumericThreshold.Y){
			}
			else
			{
				return true;
			}
		}
		else
		{
			for (auto& CritVals : crit.Criterias)
			{
				if (Values[crit.ColumnIndex].Contains(CritVals))
				{
						return true;
				}
			}
		}
		
	}

	return false;
}

void UDTFunctionLibrary::GetRowAsStruct(UObject* WorldContextObject, UDataObject* InDT, FRowData InRow, UScriptStruct* OutRow/*, UScriptStruct*& Return*/)
{
	check(0);
}
