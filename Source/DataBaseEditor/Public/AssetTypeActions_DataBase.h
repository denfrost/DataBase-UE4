#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "DataObject.h"
#include "Developer/AssetTools/Public/AssetTypeActions_Base.h"


class FMenuBuilder;

class FAssetTypeActions_DataObject : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_DataObject", "Data Object"); }
	virtual FColor GetTypeColor() const override { return FColor(163, 255, 64); }
	virtual UClass* GetSupportedClass() const override { return UDataObject::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual bool CanFilter() override { return false; }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
	virtual bool IsImportedAsset() const override { return false; }
	//	virtual void GetResolvedSourceFilePaths(const TArray<UObject*>& TypeAssets, TArray<FString>& OutSourceFilePaths) const override;

private:
	void CreateCSV();

};