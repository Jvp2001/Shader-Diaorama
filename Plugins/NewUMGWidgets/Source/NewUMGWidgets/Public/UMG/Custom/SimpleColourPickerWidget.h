// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "UObject/ObjectMacros.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateTypes.h"
#include "Widgets/SWidget.h"
#include "SimpleColourPickerWidget.generated.h"


/**
 *
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoyColorChangedEvent, const FLinearColor&, NewColor);

/**
 *  Color Picker For You! ♥
 */
UCLASS()
class NEWUMGWIDGETS_API USimpleColourPicker : public UWidget
{
	GENERATED_BODY()

public:

	USimpleColourPicker(const FObjectInitializer& ObjectInitializer);

	/** The currently Chosen Color for this Color Picker! ♥ */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=" Color Picker",meta=(Keywords="getcolor"))
	FLinearColor JoyColor = FLinearColor::Red;

	/** Called whenever the color is changed programmatically or interactively by the user */
	UPROPERTY(BlueprintAssignable, Category=" Color Picker", meta=(DisplayName="OnColorChanged ( Color Picker)"))
	FOnJoyColorChangedEvent OnColorChanged;

	/**
	 * Directly sets the current color, for saving user preferences of chosen color, or loading existing color of an in-game clicked actor!
	 * @param InColor The color to assign to the widget
	 */
	UFUNCTION(BlueprintCallable, Category = " Color Picker",meta=(Keywords="setcolor"))
	void SetJoyColor(FLinearColor NewColor, bool SkipAnimation=false);

	void ColorUpdated(FLinearColor NewValue);

#if WITH_EDITOR
public:

	// UWidget interface
	//virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;
	// End UWidget interface

	// UObject interface
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	// End of UObject interface

#endif

public:

	//~ Begin UWidget Interface
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget

	// UVisual interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End of UVisual interface

protected:
	TSharedPtr<class SSimpleColourPicker> MySlateColorPicker;

};