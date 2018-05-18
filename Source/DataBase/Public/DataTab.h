#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "DataObject.h"
#include "DataTab.generated.h"




USTRUCT(BlueprintType)
struct FDataTableHeaderStyle
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateColor TextColorAndOpacity;

	/** The font to render the text with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Header;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		TEnumAsByte<ETextJustify::Type> Justification;

	
	FDataTableHeaderStyle()
	{
		TextColorAndOpacity = FSlateColor(FLinearColor::White);
		Header.TintColor = FSlateColor(FLinearColor::Black);
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		Font = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));
	}
};

USTRUCT(BlueprintType)
struct FDataTableStyle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Pressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Hovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Disabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush SliderNormal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush SliderPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush SliderHovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush SliderDisabled;

};



UCLASS()
class UDataTab : public UWidget
{
	GENERATED_BODY()

public:
	UDataTab();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	TSharedPtr<class SDataTab> DataTable;
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table")
		FDataTableHeaderStyle HeaderStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table")
		FDataTableStyle DataTableStyle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table")
		TArray<FDataTableColumnDescription> HeaderColumns;


	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

};
