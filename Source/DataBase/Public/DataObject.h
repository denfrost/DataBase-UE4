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

	FDataTableColumnDescription()
	{
		FieldName = FText::FromString("None");
		Type = EDataTableTypes::String;
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

	UPROPERTY(EditAnywhere, Category = "Data Table Options", meta = (ToolTip = "Whenever we want to use custom widget for variables types"))
		bool bUseCustomWidgets;

	UPROPERTY(EditAnywhere, Category = "Data Table Options", meta = (ToolTip = "Search criteria tell your UI how to display the info, usually searching for fields if variable A = price your search critaria can be $20000"))
		TArray<FString> SearchTags;

	UPROPERTY(EditAnywhere, Category = "Data Table Options")
		TArray<FDataTableColumnDescription> Fields;

};