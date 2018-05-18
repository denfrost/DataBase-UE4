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
struct FDataTableColumnDescription
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Variable Name for this column"))
		FText FieldName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Determine which type of data should be this column"))
		EDataTableTypes Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Allow drop box to limit your finidings"))
		float ColumnWidth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "true if you only want string like std xlxs formats/basic data tables or false if you want special widgets"))
		bool bUseOnlyStrings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Allow drop box to limit your finidings"))
		bool bAllowSearch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "Criteria field to be match with your data table, if your criteria match your value then you will conserver visible this on your Data Table widget"))
		TArray<FString> SearchCriteria;

	FDataTableColumnDescription()
	{
		FieldName = FText::FromString("None");
		Type = EDataTableTypes::String;
		bUseOnlyStrings = true;
		bAllowSearch = false;
		ColumnWidth = 1.f;
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

UCLASS(Blueprintable)
class DATABASE_API UDataObject : public UObject
{
	GENERATED_BODY()

public:

	UDataObject();

	UPROPERTY()
		TArray<FRowData> Data;

	UPROPERTY(EditAnywhere, Category = "Data Table Options")
		UScriptStruct* Struct;

	UPROPERTY(EditAnywhere, Category = "Data Table Options")
		TArray<FDataTableColumnDescription> Fields;


};