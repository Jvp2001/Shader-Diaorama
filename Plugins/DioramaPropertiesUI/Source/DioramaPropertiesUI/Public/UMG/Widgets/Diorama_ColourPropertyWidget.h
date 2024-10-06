// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Diorama_PropertyWidget.h"
#include "NewUserWidgetsFunctionLibrary.h"
#include "PropertyDelegates.h"
#include "Diorama_ColourPropertyWidget.generated.h"

/**
 *
 */
UCLASS(Abstract)
class DIORAMAPROPERTIESUI_API UDiorama_ColourPropertyWidget : public UDiorama_PropertyWidget
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FColourPropertyChangedSignature, FLinearColor /*OldValue*/,
	                                     FLinearColor /*NewValue*/);

	UFUNCTION()
	void OnColourPickerValueChanged(const FLinearColor& NewColour);

	UFUNCTION()
	void ShowColourPicker();
	virtual void NativeOnInitialized() override;
	void Setup(FStringView InPropertyName, FLinearColor InValue,
	           TDioramaPropertyChangeSignature<FLinearColor> InOnValueChanged);

	UFUNCTION(BlueprintSetter)
	void SetValue(FLinearColor InValue);

	UFUNCTION(BlueprintGetter)
	FLinearColor GetValue() const { return Value; }

	UFUNCTION(BlueprintGetter)
	FLinearColor GetPreviousValue() const { return PreviousValue; }

	FColourPropertyChangedSignature OnValueChanged;

	FSimpleColourPickerValueChangedSignature OnSimpleColourPickerValueChanged;

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="On Value Changed")
	void K2_OnValueChanged(FLinearColor OldValue, FLinearColor NewValue);
private:

	UPROPERTY(BlueprintGetter="GetValue")
	FLinearColor Value;

	UPROPERTY(VisibleAnywhere)
	FSimpleColourPickerArgs ColourPickerArgs;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> ShowColourPickerButton;

	UPROPERTY(BlueprintGetter=GetPreviousValue)
	FLinearColor PreviousValue;


	TDioramaPropertyChangeSignature<FLinearColor> NativeOnValueChangedFunction;
};
