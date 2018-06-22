#include "JsonFunctionLibrary.h"

TArray<FJsonValueBP> UJsonFunctionLibrary::GetJsonArrayField(UPARAM(ref) FJsonData& Container, const FString& Field)
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

FJsonData UJsonFunctionLibrary::ValueAsJsonObject(FJsonValueBP& InValue)
{
	if (InValue.Value.IsValid())
	{
		FJsonData NewJson;
		NewJson.Json = InValue.Value->AsObject();
		return NewJson;
	}
	return FJsonData::GetDefault();
}

FJsonData UJsonFunctionLibrary::GetJsonField(UPARAM(ref) FJsonData& Container, const FString& Field)
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

FJsonData UJsonFunctionLibrary::GetJsonObject(UPARAM(ref) FJsonData& Container, const FString& Field)
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

FString UJsonFunctionLibrary::GetJsonString(UPARAM(ref)FJsonData& Container, const FString& InField)
{
	if (Container.Json.IsValid())
	{
		FString Value;
		if (Container.Json->TryGetStringField(InField, Value))
		{
			return Value;
		}
		return "";
	}
	return "";
}

bool UJsonFunctionLibrary::GetJsonBoolean(UPARAM(ref) FJsonData& Container)
{

	return false;
}



int32 UJsonFunctionLibrary::GetJsonInt(UPARAM(ref) FJsonData& Container)
{

	return -1;
}

float UJsonFunctionLibrary::GetJsonFloat(UPARAM(ref) FJsonData& Container)
{

	return -1.f;
}