// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Diorama_UserWidget.h"
#include <concepts>

#include "Diorama_PropertyWidget.h"
#include "PropertyDelegates.h"
#include "Components/ExpandableArea.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Diorama_PropertyGroupWidget.generated.h"

/**
 * This constrains a templated type to be a subclass of UDiorama_PropertyWidget. This is like the where clause in C#.
 */
template <typename T>
concept TPropertyWidget = std::derived_from<T, UDiorama_PropertyWidget>;


UCLASS()
class DIORAMAPROPERTIESUI_API UDiorama_PropertyGroupWidget : public UDiorama_UserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	template <TPropertyWidget T, typename TValue>
	T* AddPropertyWidget(TSubclassOf<T> Class, FStringView PropertyName, TValue Value, TDioramaPropertyChangeSignature<TValue> OnValueChanged)
	{
		T* PropertyWidget = CreateWidget<T>(this, Class);
		PropertyWidget->Setup(FName::NameToDisplayString(PropertyName.GetData(), false), Value, OnValueChanged);


		PropertyWidget->template SetProperty<TValue>(Value);
		UVerticalBoxSlot* NewItem = PropertyContainer->AddChildToVerticalBox(PropertyWidget);
		NewItem->SetPadding(FMargin(0.0f, 0.0f, 0.0f, PropertyVerticalSpacing));
		return PropertyWidget;
	}


	void SetName(const FName Name)
	{
		TitleName = Name;

	}


	/**
	 *  This is the TextDelegate binding for the for the PropertyGroupNameLabel
	 * @return This returns the name of the property group
	 */
	UFUNCTION(BlueprintPure)
	FText GetTitleName();


private:
	UPROPERTY(DisplayName="PropertyContainer", meta=(BindWidget))
	TObjectPtr<UVerticalBox> PropertyContainer;
	UPROPERTY(DisplayName="PropertyArea", meta=(BindWidget))
	TObjectPtr<UExpandableArea> ExpandableArea;

	UPROPERTY(DisplayName="Property Group Name Label", meta=(BindWidget))
	TObjectPtr<UTextBlock> PropertyGroupNameLabel;

	UPROPERTY(EditAnywhere, Category="Properties")
	double PropertyVerticalSpacing{10.0};

	FName TitleName;

};
