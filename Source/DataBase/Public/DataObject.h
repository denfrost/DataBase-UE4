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

	FDataTableFieldDescription()
	{
		FieldName = FText::FromString("None");
		Type = EDataTableTypes::String;
	}
};

USTRUCT(BlueprintType)
struct FRowData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table Options") 
		TArray<FString> Inputs;
};


USTRUCT(BlueprintType)
struct FJsonData
{
	GENERATED_BODY()

public:

	TSharedPtr<FJsonObject> Json;
	TSharedPtr<FJsonValue> Value;

	FJsonData(){}

	static const FJsonData& GetDefault() {
		static FJsonData Default;
		return Default;
	};
};

UCLASS(Blueprintable)
class DATABASE_API UDataObject : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
		FString JsonString;

public:

	UDataObject();

	UPROPERTY()
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

	//JSON BEGIN

	UFUNCTION(BlueprintPure, Category = "JSON")
		static TArray<FJsonData> GetArrayField(UPARAM(ref)FJsonData& Container, const FString& Field);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static FJsonData GetField(UPARAM(ref)FJsonData& Container, const FString& Field);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static bool GetBoolean(UPARAM(ref)FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static FString GetString(UPARAM(ref)FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static int32 GetInt(UPARAM(ref) FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static float GetFloat(UPARAM(ref)FJsonData& Container);

	UFUNCTION(BlueprintPure, Category = "JSON")
		static UObject* GetUObject(UPARAM(ref)FJsonData& Container);







};