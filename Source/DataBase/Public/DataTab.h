#pragma once
#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "DataObject.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"
#include "DataTab.generated.h"




USTRUCT(BlueprintType)
struct FDataTableHeaderStyle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateColor TextColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FMargin Margin;

	/** The font to render the text with */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Appearance)
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush HeaderBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		TEnumAsByte<ETextJustify::Type> Justification;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		float HandlerSize;

	UPROPERTY()
		FEditableTextBoxStyle TextBoxStyle;

	FDataTableHeaderStyle()
	{
		UFont* RobotoFontObj = LoadObject<UFont>(nullptr,TEXT("/Engine/EngineFonts/Roboto"));
		Font = FSlateFontInfo(RobotoFontObj, 12, FName("Bold"));

		TextBoxStyle.BackgroundImageNormal.TintColor = FSlateColor(FLinearColor(0, 0, 0, 1));
		TextBoxStyle.ForegroundColor = FSlateColor(FLinearColor(1, 1, 1, 1));
		TextBoxStyle.BackgroundImageHovered.TintColor = FSlateColor(FLinearColor(.5f, .5f, .5f, .5f));
		TextBoxStyle.BackgroundImageFocused.TintColor = FSlateColor(FLinearColor(.2f, .2f, .2f, .2f));
	}
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
		FSlateColor TextColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		TEnumAsByte<ETextJustify::Type> Justification;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Pressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateBrush Hovered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FScrollBarStyle ScrollBarStyle;


	UPROPERTY()
		FEditableTextBoxStyle TextBoxStyle;
};

USTRUCT(BlueprintType)
struct FDataTableStyleOverride
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateFontInfo Font;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FSlateColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		TEnumAsByte<ETextJustify::Type> Justification;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		int32 ColumnIndex;

	FDataTableStyleOverride()
	{
		UFont* RobotoFontObj = LoadObject<UFont>(nullptr, TEXT("/Engine/EngineFonts/Roboto"));
		Font = FSlateFontInfo(RobotoFontObj, 12, FName("Bold"));

		Color = FSlateColor(FLinearColor::White);
		Justification = ETextJustify::Left;
		ColumnIndex = 0;
	}
};

USTRUCT(BlueprintType)
struct FDataTableStyle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FDataTableHeaderStyle HeaderStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		FDataTableBodyStyle BodyStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
		TArray<FDataTableStyleOverride> BodyStyleColumnsOverrides;

	FDataTableStyle()
	{
// 		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
// 		HeaderFont = FSlateFontInfo(RobotoFontObj.Object, 12, FName("Bold"));


		HeaderStyle.HandlerSize = 1;
		HeaderStyle.Margin = FMargin(1, 1, 1, 1);
		HeaderStyle.TextColorAndOpacity = FSlateColor(FLinearColor::White);
		HeaderStyle.HeaderBrush.TintColor = FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1));
// 		
		HeaderStyle.Justification = ETextJustify::Center;


		BodyStyle.GeneralMargin = FMargin(0);
		BodyStyle.SlotMargin = FMargin(0);
		BodyStyle.TextColorAndOpacity = FSlateColor(FLinearColor(1, 1, 1 ,1));
		UFont* RobotoFontObj = LoadObject<UFont>(nullptr, TEXT("/Engine/EngineFonts/Roboto"));
		BodyStyle.Font = FSlateFontInfo(RobotoFontObj, 12, FName("Bold"));

		BodyStyle.Justification = ETextJustify::Left;
		BodyStyle.Normal.TintColor = FSlateColor(FLinearColor(0, 0, 0, 1));
		BodyStyle.Hovered.TintColor = FSlateColor(FLinearColor(.5f, .5f, .5f, .5f));

		BodyStyle.TextBoxStyle.BackgroundImageNormal.TintColor = BodyStyle.Normal.TintColor;
		BodyStyle.TextBoxStyle.ForegroundColor = FSlateColor(FLinearColor(1, 1, 1, 1));
		BodyStyle.TextBoxStyle.BackgroundImageHovered.TintColor = BodyStyle.Hovered.TintColor;
		BodyStyle.TextBoxStyle.BackgroundImageFocused.TintColor = FSlateColor(FLinearColor(.2f, .2f, .2f, .2f));

		BodyStyleColumnsOverrides = TArray<FDataTableStyleOverride>();
	}

	static const FDataTableStyle& GetDefault() {
		static FDataTableStyle Default;
		return Default;
	};
};

USTRUCT()
struct FDataTableEditableTextStyle
{
	GENERATED_BODY()

public:
	FEditableTextBoxStyle EditableTextStyle;

	FDataTableEditableTextStyle()
	{
		EditableTextStyle = FCoreStyle::Get().GetWidgetStyle< FEditableTextBoxStyle >("NormalEditableTextBox");
		EditableTextStyle.BackgroundImageNormal.TintColor = FSlateColor(FLinearColor(.05f, .05f, .05f, 1));
		EditableTextStyle.ForegroundColor = FSlateColor(FLinearColor(1, 1, 1, 1));
		EditableTextStyle.BackgroundImageHovered.TintColor = FSlateColor(FLinearColor(.5f, .5f, .5f, .5f));
		EditableTextStyle.BackgroundImageFocused.TintColor = FSlateColor(FLinearColor(.2f, .2f, .2f, .2f));
	}

	static const FDataTableEditableTextStyle& GetDefault() {
		static FDataTableEditableTextStyle Default;
		return Default;
	};
};

USTRUCT(BlueprintType)
struct FDTCriteria
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		int32 ColumnIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		TArray<FString> Criterias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		bool bIsNumeric;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
		FVector2D NumericThreshold;


	FDTCriteria()
	{
		ColumnIndex = 0;
		Criterias.Empty();
		bIsNumeric = false;
		NumericThreshold = FVector2D::ZeroVector;
	}
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDataTableRowClicked, int32, Index, TArray<FString>, Values);


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

	UPROPERTY(BlueprintAssignable, Category = "Data Table")
		FOnDataTableRowClicked OnDataTableRowClicked;

	UPROPERTY(BlueprintAssignable, Category = "Data Table")
		FOnDataTableRowClicked OnDataTableRowDoubleClicked;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table")
		UDataObject* DataObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Table")
		FDataTableStyle DataTableStyle;


	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable, Category = "Data Table")
		void SetRowStyleOverride(int32 Index, const FDataTableStyleOverride& InStyle);

	UFUNCTION(BlueprintCallable, Category = "Data Table", meta = (ToolTip = "Hide and unhide rows based on some criterias"))
		void AddSearchCriteria(const TArray<FDTCriteria>& NewCriteria);

	UFUNCTION(BlueprintCallable, Category = "Data Table", meta = (ToolTip = "Clear the criteria will display all info for each row"))
		void ClearSearchCriteria();


protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

private:
	void OnRowClicked(const int32& RowIndex, const TArray<FString>& Values);
	void OnRowDoubleClicked(const int32& RowIndex, const TArray<FString>& Values);
};
