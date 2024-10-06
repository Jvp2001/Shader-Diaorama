// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widgets/Diorama_ColourPropertyWidget.h"

#include "Components/Button.h"
#include "UMG/Custom/SimpleColourPickerWidget.h"

void UDiorama_ColourPropertyWidget::OnColourPickerValueChanged(const FLinearColor& NewColour)
{
	NativeOnValueChangedFunction(PreviousValue, NewColour);
}

void UDiorama_ColourPropertyWidget::ShowColourPicker()
{
	UNewUserWidgetsFunctionLibrary::ShowColourPicker(ColourPickerArgs, OnSimpleColourPickerValueChanged);
}

void UDiorama_ColourPropertyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ShowColourPickerButton->OnClicked.AddUniqueDynamic(this, &ThisClass::ShowColourPicker);

	OnSimpleColourPickerValueChanged.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ThisClass, SetValue));


}

void UDiorama_ColourPropertyWidget::Setup(FStringView InPropertyName, FLinearColor InValue,
	TDioramaPropertyChangeSignature<FLinearColor> InOnValueChanged)
{
	SetName(InPropertyName);
	ColourPickerArgs.Title = GetPropertyName();
	ColourPickerArgs.InitialColour = InValue;
	OnValueChanged.AddLambda(std::move(InOnValueChanged));
}

void UDiorama_ColourPropertyWidget::SetValue(const FLinearColor InValue)
{
	PreviousValue = Value;
	ColourPickerArgs.InitialColour = InValue;
	Value = InValue;

	OnValueChanged.Broadcast(PreviousValue, Value);
	K2_OnValueChanged(PreviousValue, Value);

}

