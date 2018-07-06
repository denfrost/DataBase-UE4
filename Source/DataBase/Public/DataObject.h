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

 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "pick a class to filter when you use object"))
		TSubclassOf<UObject> ObjectFilter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table", meta = (ToolTip = "if is hidden this will not be draw in the UMG"))
		bool bHidden;

	FDataTableFieldDescription()
	{
		FieldName = FText::FromString("None");
		Type = EDataTableTypes::String;
		bHidden = false;
		ObjectFilter = UObject::StaticClass();
	}
};

USTRUCT(BlueprintType)
struct FRowData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table Options") 
		TArray<FString> Inputs;

	UPROPERTY(BlueprintReadOnly, Category = "Data Table Options")
		TArray<UObject*> References;

	UPROPERTY(BlueprintReadOnly, Category = "Data Table Options")
		TArray<int32> IndexReferences;
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

	UPROPERTY(EditAnywhere, Category = "CSV Options")
		FFilePath CSVPath;

	UPROPERTY(EditAnywhere, Category = "CSV Options")
		bool bSaveFileOnSave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table Options")
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

	UFUNCTION(BlueprintPure, Category = "DataTable")
		FString GetCSVPath(bool bOnlyName = true);

	UPROPERTY(BlueprintAssignable, Category = "DataTable")
		FUpdateDataTable OnDataTableUpdate;



	FString GetCSVPathFile(FString* Folder, FString* FileName);




};