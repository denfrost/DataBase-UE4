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

TArray<FJsonData> UDataObject::GetArrayField(UPARAM(ref) FJsonData& Container, const FString& Field)
{
	if (Container.Json.IsValid())
	{
		TArray<FJsonData> NewObjs;
		TArray<TSharedPtr<FJsonValue>> objArray = Container.Json->GetArrayField(Field);
		for (int32 i = 0; i < objArray.Num(); i++)
		{
			FJsonData newObject;
			newObject.Json = Container.Json->GetObjectField(Field);
			newObject.Value = objArray[i];
			NewObjs.Add(newObject);
		}
		return NewObjs;
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getArrayField) no valid json object to extract field"));
	return TArray<FJsonData>();
}

FJsonData UDataObject::GetField(UPARAM(ref) FJsonData& Container, const FString& Field)
{
	if (Container.Json.IsValid())
	{
		FJsonData SubJson;
		SubJson.Json = Container.Json->GetObjectField(Field);
		SubJson.Value = Container.Json->TryGetField(Field);
		return SubJson;
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getField) no valid json object to extract field"));
	return FJsonData::GetDefault();
}

bool UDataObject::GetBoolean(UPARAM(ref) FJsonData& Container)
{
	if (Container.Value.IsValid())
	{
		bool output;
		if (Container.Value->TryGetBool(output))
		{
			return output;
		}
		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid value in this json"));
		return "";
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid json object to extract string"));
	return false;
}

FString UDataObject::GetString(UPARAM(ref)FJsonData& Container)
{
	if (Container.Value.IsValid())
	{
		FString output;
		if (Container.Value->TryGetString(output))
		{
			return output;
		}
		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid value in this json"));
		return "";
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid json object to extract string"));
	return "";
}

int32 UDataObject::GetInt(UPARAM(ref) FJsonData& Container)
{
	if (Container.Value.IsValid())
	{
		int32 output;
		if (Container.Value->TryGetNumber(output))
		{
			return output;
		}
		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getInt) no valid value in this json"));
		return -1;
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getInt) no valid json object to extract integer"));
	return -1;
}

float UDataObject::GetFloat(UPARAM(ref) FJsonData& Container)
{
	if (Container.Value.IsValid())
	{
		double output;
		if (Container.Value->TryGetNumber(output))
		{
			return (float)output;
		}
		UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid value in this json"));
		return -1.f;
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR : (UJJSON::getString) no valid json object to extract float"));
	return -1.f;
}

UObject* UDataObject::GetUObject(UPARAM(ref) FJsonData& Container)
{
	return nullptr;
}

