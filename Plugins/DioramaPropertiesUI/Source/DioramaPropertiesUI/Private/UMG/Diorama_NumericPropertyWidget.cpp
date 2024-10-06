// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widgets/Diorama_NumericPropertyWidget.h"
#include "Components/SpinBox.h"


void UDiorama_NumericPropertyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ValueInput->OnValueChanged.AddDynamic(this, &UDiorama_NumericPropertyWidget::OnSpinBoxValueChanged);
	ValueInput->OnValueCommitted.AddUniqueDynamic(this, &ThisClass::OnSpinBoxValueCommitted);
	ValueInput->OnEndSliderMovement.AddUniqueDynamic(this, &ThisClass::OnSpinBoxSliderEndMovement);


}

void UDiorama_NumericPropertyWidget::Setup(FStringView InPropertyName, const float InValue, TDioramaPropertyChangeSignature<float> InOnValueChanged)

{
	SetName(InPropertyName);
	ValueInput->SetValue(InValue);

	OnValueChanged.AddLambda(InOnValueChanged);
}


void UDiorama_NumericPropertyWidget::SetValue(const float NewValue)
{
	PreviousValue = Value;
	Value = NewValue;

}

void UDiorama_NumericPropertyWidget::SetSliderRange(const float Min, const float Max)
{
	SliderRange = {Min, Max};
	bClampInput = true;
	ValueInput->SetMinValue(Min);
	ValueInput->SetMaxValue(Max);
}

void UDiorama_NumericPropertyWidget::SetInputRange(float Min, float Max)
{
	InputRange = {Min, Max};
}

void UDiorama_NumericPropertyWidget::ClampInput()
{
	if(not bClampInput)
	{
		return;
	}

	ValueInput->SetValue(FMath::Clamp(Value, SliderRange.Min, SliderRange.Max));

}

void UDiorama_NumericPropertyWidget::OnSpinBoxValueCommitted(const float InValue, ETextCommit::Type CommitMethod)
{
	OnSpinBoxValueChanged(InValue);

}

void UDiorama_NumericPropertyWidget::InvokeDelegates()
{
	OnValueChanged.Broadcast(PreviousValue,Value);
	K2_OnValueChanged(PreviousValue, Value);
}

void UDiorama_NumericPropertyWidget::OnSpinBoxValueChanged(const float InValue)
{
	SetValue(InValue);
	InvokeDelegates();
}


void UDiorama_NumericPropertyWidget::OnSpinBoxSliderEndMovement(const float InValue)
{

	if(bClampInput)
	{
		SetValue(FMath::Clamp(InValue, SliderRange.Min, SliderRange.Max));
	}

	InvokeDelegates();
}