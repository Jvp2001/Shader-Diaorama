// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Diorama_PropertyWidget.h"
#include "PropertyDelegates.h"
#include "Components/SpinBox.h"
#include "Diorama_NumericPropertyWidget.generated.h"

class USpinBox;
struct FValueRange
{
	float Min{};
	float Max{};
};
/**
 *
 */
UCLASS(Abstract)
class DIORAMAPROPERTIESUI_API UDiorama_NumericPropertyWidget : public UDiorama_PropertyWidget
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FNumericPropertyChangedSignature, float /*OldValue*/, float  /*NewValue*/);



	virtual void NativeOnInitialized() override;
	void Setup(FStringView InPropertyName, const float InValue, TDioramaPropertyChangeSignature<float> InOnValueChanged);

	UFUNCTION(BlueprintGetter)
	float GetValue() const { return Value; }

	UFUNCTION(BlueprintSetter)
	void SetValue(float NewValue);


	void SetSliderRange(float Min, float Max);

	void SetInputRange(float Min, float Max);

	void ClampInput();
	FNumericPropertyChangedSignature OnValueChanged;
protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName="On Value Changed")
	void K2_OnValueChanged(float OldValue, float NewValue);

private:
	UFUNCTION()
	void OnSpinBoxValueCommitted(float InValue, ETextCommit::Type CommitMethod);
	void InvokeDelegates();

	UFUNCTION()
	void OnSpinBoxValueChanged(float InValue);

	UFUNCTION()
	void OnSpinBoxSliderEndMovement(float InValue);



	UPROPERTY(BlueprintGetter="GetValue", BlueprintSetter="SetValue")
	float Value{0.0f};

	UPROPERTY(DisplayName="ValueInput", meta=(BindWidget))
	TObjectPtr<USpinBox> ValueInput;

	float PreviousValue{0.0f};


	FValueRange SliderRange{0.0f, 1.0f};
	FValueRange InputRange{0.0f, 1.0f};

	bool bClampInput{false};

	TDioramaPropertyChangeSignature<float> NativeOnValueChangedFunction;
};
