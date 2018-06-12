#include "DTFunctionLibrary.h"

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
