// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "PropertyWidgetClasses.h"
#include "UMG/Widgets/Diorama_PropertyGroupWidget.h"


class ADiorama_DayNightActor;
class UMaterialParameterCollection;


/**
 * This class adds the properties to a specific UDiorama_PropertyGroupWidget
 */

class DIORAMAPROPERTIESUI_API FPropertyGrabber
{
public:

	static void GrabAndStoreProperties(const FDiorama_PropertyWidgetsClasses& PropertyWidgetsClasses, UDiorama_PropertyGroupWidget* PropertyGroupWidget, UMaterialParameterCollection
	                           * Collection);

	static void GrabAndStoreProperties(const FDiorama_PropertyWidgetsClasses& PropertyWidgetsClasses, UDiorama_PropertyGroupWidget* PropertyGroupWidget, AActor
	                           * DayNightActor);



	/**
	 * A templated function to setup the properties of a specific type.
	 * This used to setup properties for a specific UMaterialParameterCollection.
	 * This helps with code reduction and keeps it more DRY
	 */
	template <typename TPropertyWidget, typename TPropertyType, typename TParameterType>
	static void SetupProperties(UDiorama_PropertyGroupWidget* PropertyGroupWidget, const TArray<TParameterType>& Parameters,
						 UClass* PropertyWidgetClass,
						 std::function<void(FName, TPropertyType, TPropertyType)> OnValueChanged)
	{
		for (auto& Parameter : Parameters)
		{
			FName ParameterName = Parameter.ParameterName;
			TPropertyType ParameterValue = Parameter.DefaultValue;
			PropertyGroupWidget->AddPropertyWidget<TPropertyWidget, TPropertyType>(
				PropertyWidgetClass, ParameterName.ToString(), ParameterValue,
				[=](TPropertyType OldValue, TPropertyType NewValue)
				{
					OnValueChanged(ParameterName, OldValue, NewValue);
				});
		}
	}

};
