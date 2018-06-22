#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"
#include "Runtime/SlateCore/Public/Textures/SlateIcon.h"

/**  */
class FDataObjectEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();

	static FName GetStyleSetName();


	// Creates the Style Set.
	static TSharedRef<class FSlateStyleSet> Create();

	// Singleton instance used for our Style Set.
	static TSharedPtr<class FSlateStyleSet> MenuStyleInstance;


};