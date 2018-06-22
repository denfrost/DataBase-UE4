#pragma once
#include "EngineMinimal.h"
#include "JsonFunctionLibrary.generated.h"


USTRUCT(BlueprintType)
struct FJsonValueBP
{
	GENERATED_BODY()

public:
	TSharedPtr<FJsonValue> Value;
	FJsonValueBP() {}
};

USTRUCT(BlueprintType)
struct FJsonData
{
	GENERATED_BODY()

public:

	TSharedPtr<FJsonObject> Json;
	// 	TSharedPtr<FJsonValue> Value;

	FJsonData() {}

	static const FJsonData& GetDefault() {
		static FJsonData Default;
		return Default;
	};
};

UCLASS()
class UJsonFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//JSON BEGIN

	UFUNCTION(BlueprintPure, Category = "JSON")
		static TArray<FJsonValueBP> GetJsonArrayField(UPARAM(ref)FJsonData& Container, const FString& Field);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static FJsonData ValueAsJsonObject(UPARAM(ref)FJsonValueBP& InValue);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static FJsonData GetJsonField(UPARAM(ref)FJsonData& Container, const FString& Field);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static bool GetJsonBoolean(UPARAM(ref)FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static FString GetJsonString(UPARAM(ref)FJsonData& Container, const FString& InField);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static int32 GetJsonInt(UPARAM(ref) FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static float GetJsonFloat(UPARAM(ref)FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static FJsonData GetJsonObject(UPARAM(ref)FJsonData& Container, const FString& Field);


	UFUNCTION(BlueprintPure, Category = "JSON")
		static	FJsonData constructJsonFromString(const FString& jsonAsString)
	{

		TSharedRef< TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(jsonAsString);
		FJsonData Json;
		if (FJsonSerializer::Deserialize(JsonReader, Json.Json) && Json.Json.IsValid())
		{
			return Json;
		}
		return FJsonData::GetDefault();
	}


};