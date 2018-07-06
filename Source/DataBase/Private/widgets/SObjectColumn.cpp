#include "SObjectColumn.h"

#if WITH_EDITOR
#include "Editor/PropertyEditor/Public/PropertyCustomizationHelpers.h"
#endif



void SObjectColumn::Construct(const FArguments& InArgs)
{
	FText InValue = InArgs._Value;
	DataTableStyle = InArgs._DataTableStyle;
	OnObjectChange = InArgs._OnObjectChange;
	FilterClass = InArgs._FilterClass;
	
	if (!FilterClass)
	{
		FilterClass = UObject::StaticClass();
	}

	if (InValue.ToString().Contains("Game"))
	{
		GameObjectPath = InValue.ToString();
	}
#if WITH_EDITOR
	ChildSlot[
		SNew(SObjectPropertyEntryBox)
		.AllowedClass(FilterClass)
		.OnObjectChanged(this, &SObjectColumn::OnObjectChanged)
		.ObjectPath(this, &SObjectColumn::GetLastPagePath)
	];


#else
	ChildSlot[
		SNew(SHorizontalBox)
	];
#endif
}

FString SObjectColumn::GetLastPagePath() const
{
	return GameObjectPath;
}

void SObjectColumn::OnObjectChanged(const FAssetData& InAssetData)
{
	GameObjectPath = InAssetData.ObjectPath.ToString();
	FText NewValue = FText::FromString(GameObjectPath);
	OnObjectChange.ExecuteIfBound(NewValue, InAssetData.GetAsset());
}

SObjectColumn::~SObjectColumn()
{

}

