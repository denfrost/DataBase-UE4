#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataObject.generated.h"

UENUM(BlueprintType)
enum class EDataTableTypes : uint8
{
	Boolean,
	String,
	Floating,
	Integer,
	UEObject,
};

USTRUCT(BlueprintType)
struct FDataTableFieldDescription
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Variable Name for this column"))
		FText FieldName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Determine which type of data should be this column"))
		EDataTableTypes Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "if is hidden this will not be draw in the UMG"))
		bool bHidden;

	FDataTableFieldDescription()
	{
		FieldName = FText::FromString("None");
		Type = EDataTableTypes::String;
		bHidden = false;
	}
};

USTRUCT(BlueprintType)
struct FRowData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table Options") 
		TArray<FString> Inputs;
};


USTRUCT(BlueprintType)
struct FJsonData
{
	GENERATED_BODY()

public:

	TSharedPtr<FJsonObject> Json;
// 	TSharedPtr<FJsonValue> Value;

	FJsonData(){}

	static const FJsonData& GetDefault() {
		static FJsonData Default;
		return Default;
	};
};


USTRUCT(BlueprintType)
struct FJsonValueBP
{
	GENERATED_BODY()

public:
	TSharedPtr<FJsonValue> Value;
	FJsonValueBP() {}
};

UENUM(BlueprintType)
enum class EDataTableStatus : uint8
{
	Ok,
	OkPlusExtra,
	Fail,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateDataTable , bool, bStatus);

UCLASS(Blueprintable)
class DATABASE_API UDataObject : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
		FString JsonString;

public:

	UDataObject();

	UPROPERTY(BlueprintReadOnly, Category = "Data Table")
		TArray<FRowData> Data;

	UPROPERTY(EditAnywhere, Category = "Data Table Options")
		UScriptStruct* Struct;

	UPROPERTY(EditAnywhere, Category = "Data Table Options", meta = (ToolTip = "Whenever we want to use custom widget for variables types"))
		bool bUseCustomWidgets;

	UPROPERTY(EditAnywhere, Category = "Data Table Options", meta = (ToolTip = "Search criteria tell your UI how to display the info, usually searching for fields if variable A = price your search critaria can be $20000"))
		TArray<FString> SearchTags;

	UPROPERTY(EditAnywhere, Category = "Data Table Options")
		TArray<FDataTableFieldDescription> Fields;


	void UpdateRowsAfterFields();

	//Data Manipulation
	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void ClearDataTable();

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		EDataTableStatus AddRowInfo(const FRowData& InRow);

	UFUNCTION(BlueprintCallable, Category = "DataTable")
		void CastUpdate();

	UFUNCTION(BlueprintPure, Category = "DataTable")
		static void ValuesToRowData(const TArray<FString> Values, FRowData& OutData);

	UPROPERTY(BlueprintAssignable, Category = "DataTable")
		FUpdateDataTable OnDataTableUpdate;

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
		static	FJsonData constructJsonFromString(const FString& jsonAsString )
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