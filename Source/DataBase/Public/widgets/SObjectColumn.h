#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Runtime/SlateCore/Public/Widgets/SCompoundWidget.h"
#include "DataTab.h"
#include "Runtime/AssetRegistry/Public/AssetData.h"


DECLARE_DELEGATE_TwoParams(FOnObjectChanged, const FText&, const UObject*);

class SObjectColumn : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SObjectColumn)
		: _DataTableStyle(&FDataTableStyle::GetDefault())
	{}

	SLATE_ARGUMENT(FText, Value)
	SLATE_ARGUMENT(const FDataTableStyle*, DataTableStyle)
	SLATE_ARGUMENT(UClass*, FilterClass)
	SLATE_EVENT(FOnObjectChanged, OnObjectChange)
	SLATE_END_ARGS()


	FString GameObjectPath;

	const FDataTableStyle* DataTableStyle;
	UClass* FilterClass;

	FOnObjectChanged OnObjectChange;

	void OnObjectChanged(const FAssetData& InAssetData);
	FString GetLastPagePath() const;

public:

	void Construct(const FArguments& InArgs);
	~SObjectColumn();


};