#include "DataObject.h"


UDataObject::UDataObject()
{
	Fields.Init(FDataTableFieldDescription(), 1);
	bUseCustomWidgets = true;
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

TArray<FJsonValueBP> UDataObject::GetJsonArrayField(UPARAM(ref) FJsonData& Container, const FString& Field)
{
	if (Container.Json.IsValid())
	{
		TArray<FJsonValueBP> NewValues;
		TArray<TSharedPtr<FJsonValue>> objArray = Container.Json->GetArrayField(Field);

		for (int32 i = 0; i < objArray.Num(); i++)
		{
			FJsonValueBP NewValue;
			NewValue.Value = objArray[i];
			NewValues.Add(NewValue);
		}
		return NewValues;
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getArrayField) no valid json object to extract field"));
	return TArray<FJsonValueBP>();
}

FJsonData UDataObject::ValueAsJsonObject(FJsonValueBP& InValue)
{
	if (InValue.Value.IsValid())
	{
		FJsonData NewJson;
		NewJson.Json = InValue.Value->AsObject();
		return NewJson;
	}
	return FJsonData::GetDefault();
}

FJsonData UDataObject::GetJsonField(UPARAM(ref) FJsonData& Container, const FString& Field)
{
	if (Container.Json.IsValid())
	{
		FJsonData SubJson;
		SubJson.Json = Container.Json->GetObjectField(Field);
		return SubJson;
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getField) no valid json object to extract field"));
	return FJsonData::GetDefault();
}

FJsonData UDataObject::GetJsonObject(UPARAM(ref) FJsonData& Container, const FString& Field)
{
	if (Container.Json.IsValid())
	{
		for (auto& in : Container.Json->Values)
		{
			FJsonData NewJson;
			NewJson.Json = in.Value->AsObject();
			return NewJson;
			break;
		}
	}
	return FJsonData::GetDefault();
}

FString UDataObject::GetJsonString(UPARAM(ref)FJsonData& Container, const FString& InField)
{
	if (Container.Json.IsValid())
	{
		FString Value;
		if (Container.Json->TryGetStringField(InField, Value))
		{
			return Value;
		}
		return "";

// 		for (auto& in : Container.Json->Values)
// 		{
// 			UE_LOG(LogTemp, Warning, TEXT("value yeah %s"), *in.Key);
// 		}
	}

	// 	if (Container.Value.IsValid())
	// 	{
	// 		FString output;
	// 		if (Container.Value->TryGetString(output))
	// 		{
	// 			return output;
	// 		}
	// 		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid value in this json"));
	// 		return "";
	// 	}
	// 	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid json object to extract string"));
	return "";
}

bool UDataObject::GetJsonBoolean(UPARAM(ref) FJsonData& Container)
{
// 	if (Container.Value.IsValid())
// 	{
// 		bool output;
// 		if (Container.Value->TryGetBool(output))
// 		{
// 			return output;
// 		}
// 		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid value in this json"));
// 		return "";
// 	}
// 	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid json object to extract string"));
	return false;
}



int32 UDataObject::GetJsonInt(UPARAM(ref) FJsonData& Container)
{
// 	if (Container.Value.IsValid())
// 	{
// 		int32 output;
// 		if (Container.Value->TryGetNumber(output))
// 		{
// 			return output;
// 		}
// 		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getInt) no valid value in this json"));
// 		return -1;
// 	}
// 	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getInt) no valid json object to extract integer"));
	return -1;
}

float UDataObject::GetJsonFloat(UPARAM(ref) FJsonData& Container)
{
// 	if (Container.Value.IsValid())
// 	{
// 		double output;
// 		if (Container.Value->TryGetNumber(output))
// 		{
// 			return (float)output;
// 		}
// 		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid value in this json"));
// 		return -1.f;
// 	}
// 	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid json object to extract float"));
	return -1.f;
}



