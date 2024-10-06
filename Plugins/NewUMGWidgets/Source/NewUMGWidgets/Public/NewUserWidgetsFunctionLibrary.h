// // Fill out your copyright notice in the Description page of Project Settings.
//
#pragma once
//
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Slate/Custom/SimpleColourPicker.h"
#include "UMG/Custom/SimpleColourPickerWidget.h"
#include "Framework/SlateDelegates.h"
#include "NewUserWidgetsFunctionLibrary.generated.h"

class FOnPickedColourChangedSignature;
/**
 *
 */
UCLASS()
class NEWUMGWIDGETS_API UNewUserWidgetsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 *
	 * @param Args The arguments to pass to the colour picker
	 * @param OnColourPicked The delegate to call when the colour is picked
	 * @remarks
	 * If FColourPickerArgs::bOnlyRefreshOnMouseUp is true, the delegate will be called when the mouse button is released.
	 * If FColourPickerArgs::bOnlyRefreshOnOk is true, the delegate will be called when the user clicks the OK button.]p
	 */
	UFUNCTION(BlueprintCallable, Category = "Simple Window Manager", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnColourPicked"))
	static void ShowColourPicker(UPARAM(ref) const FSimpleColourPickerArgs& Args, const FSimpleColourPickerValueChangedSignature& OnColourPicked);
};
