// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Diorama_UserWidget.h"
#include "Diorama_PropertyWidget.generated.h"


/**
 *
 */
UCLASS(Abstract)
class DIORAMAPROPERTIESUI_API UDiorama_PropertyWidget : public UDiorama_UserWidget
{
	GENERATED_BODY()

public:
	/**
	 * This functions is defined for the purpose of setting up the widget.
	 * This also allows the child classes to define a more specialised version of this function
	 * @tparam Arguments The types of the arguments
	 * @param args
	 */
	template<typename... Arguments>
	void Setup(Arguments&&... args)
	{
		//ValueInput->OnValueChanged.AddDynamic(this, &UDiorama_NumericPropertyWidget::OnValueChanged);
	}
	template<typename TValue>
	void SetProperty(TValue Value)
	{
		//ValueInput->SetValue(Value);

	}

	void SetName(const FStringView Name) const;
	void SetName(const FName Name) const;

	FText GetPropertyName() const;


private:
	UPROPERTY(DisplayName="PropertyNameLabel", meta=(BindWidget))
	TObjectPtr<class UTextBlock> PropertyName;

};
