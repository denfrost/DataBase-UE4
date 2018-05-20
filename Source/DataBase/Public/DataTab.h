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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FMargin Margin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FMargin ContentMargin;

	/** The font to render the text with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush HeaderBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		TEnumAsByte<ETextJustify::Type> Justification;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		float HandlerSize;
};

USTRUCT(BlueprintType)
struct FDataTableBodyStyle
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FMargin GeneralMargin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FMargin SlotMargin;

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

	UPROPERTY()
		FEditableTextBoxStyle TextBoxStyle;
};

USTRUCT(BlueprintType)
struct FDataTableStyle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FDataTableHeaderStyle HeaderStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FDataTableBodyStyle BodyStyle;

	FDataTableStyle()
	{
		HeaderStyle.HandlerSize = 1;
		HeaderStyle.ContentMargin = FMargin(0);
		HeaderStyle.Margin = FMargin(1, 1, 1, 1);
		HeaderStyle.TextColorAndOpacity = FSlateColor(FLinearColor::White);
		HeaderStyle.HeaderBrush.TintColor = FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1));
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		HeaderStyle.Font = FSlateFontInfo(RobotoFontObj.Object, 12, FName("Bold"));
		HeaderStyle.Justification = ETextJustify::Center;


		BodyStyle.GeneralMargin = FMargin(0);
		BodyStyle.SlotMargin = FMargin(0);
		BodyStyle.Normal.TintColor = FSlateColor(FLinearColor(0, 0, 0, 0));
		BodyStyle.Hovered.TintColor = FSlateColor(FLinearColor(.5f, .5f, .5f, .5f));

		BodyStyle.TextBoxStyle.BackgroundImageNormal.TintColor = BodyStyle.Normal.TintColor;
		BodyStyle.TextBoxStyle.ForegroundColor = FSlateColor(FLinearColor(1, 1, 1, 1));
		BodyStyle.TextBoxStyle.BackgroundImageHovered.TintColor = BodyStyle.Hovered.TintColor;
		BodyStyle.TextBoxStyle.BackgroundImageFocused.TintColor = FSlateColor(FLinearColor(.2f, .2f, .2f, .2f));
	}

	static const FDataTableStyle& GetDefault() {
		static FDataTableStyle Default;
		return Default;
	};
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
		UDataObject* DataObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table")
		FDataTableStyle DataTableStyle;


	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

};
