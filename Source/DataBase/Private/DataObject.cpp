#include "DataObject.h"


UDataObject::UDataObject()
{
	Fields.Init(FDataTableFieldDescription(), 1);
}

void UDataObject::UpdateRowsAfterFields()
{
	for (auto& Row : Data)
	{
		while (Row.Inputs.Num() != Fields.Num())
		{
			if (Row.Inputs.Num() > Fields.Num())
			{
				Row.Inputs.RemoveAt(Row.Inputs.Num() - 1);
			}
			else if (Row.Inputs.Num() < Fields.Num())
			{
				Row.Inputs.Add("");
			}
		}
	}
}

void UDataObject::ClearDataTable()
{
	Data.Empty();
}

EDataTableStatus UDataObject::AddRowInfo(const FRowData& InRow)
{
	if (InRow.Inputs.Num() == Fields.Num())
	{
		Data.Add(InRow);
		return EDataTableStatus::Ok;
	}

	if (InRow.Inputs.Num() > Fields.Num())
	{
		FRowData Temp;
		for (int32 i = 0; i < Fields.Num(); i++)
		{
			Temp.Inputs.Add(InRow.Inputs[i]);
		}
		Data.Add(Temp);
		return EDataTableStatus::OkPlusExtra;
	}

	return EDataTableStatus::Fail;
}

void UDataObject::CastUpdate()
{
	if (OnDataTableUpdate.IsBound())
	{
		OnDataTableUpdate.Broadcast(true);
	}
}

void UDataObject::ValuesToRowData(const TArray<FString> Values, FRowData& OutData)
{
	OutData.Inputs = Values;
}

FString UDataObject::GetCSVPath(bool bOnlyName /*= true*/)
{
	if (bOnlyName)
	{
		FString Output;
		CSVPath.FilePath.Split("/", nullptr, &Output, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		return Output;
	}
	return CSVPath.FilePath;
}




