// Fill out your copyright notice in the Description page of Project Settings.


#include "PropertyGrabber.h"
#include <functional>
#include "Kismet/KismetMaterialLibrary.h"
#include "Logging/StructuredLog.h"
#include "Materials/MaterialParameterCollection.h"
#include "UMG/Widgets/Diorama_ColourPropertyWidget.h"
#include "UMG/Widgets/Diorama_NumericPropertyWidget.h"
#include "UMG/Widgets/Diorama_PropertyGroupWidget.h"


void FPropertyGrabber::GrabAndStoreProperties(const FDiorama_PropertyWidgetsClasses& PropertyWidgetsClasses,
                                              UDiorama_PropertyGroupWidget* PropertyGroupWidget,
                                              UMaterialParameterCollection* Collection)
{
	SetupProperties<UDiorama_NumericPropertyWidget, float, FCollectionScalarParameter>(
		PropertyGroupWidget, Collection->ScalarParameters, PropertyWidgetsClasses.NumericPropertyWidgetClass,
		[=](const FName ParameterName, [[maybe_unused]] float OldValue, const float NewValue)
		{
			UKismetMaterialLibrary::SetScalarParameterValue(PropertyGroupWidget, Collection,
			                                                ParameterName, NewValue);
		});
	SetupProperties<UDiorama_ColourPropertyWidget, FLinearColor, FCollectionVectorParameter>(
		PropertyGroupWidget, Collection->VectorParameters, PropertyWidgetsClasses.ColourPropertyWidgetClass,
		[=](const FName ParameterName, [[maybe_unused]] FLinearColor OldValue, const FLinearColor NewValue)
		{
			UKismetMaterialLibrary::SetVectorParameterValue(PropertyGroupWidget, Collection,
			                                                ParameterName, NewValue);
		});
}


void FPropertyGrabber::GrabAndStoreProperties(const FDiorama_PropertyWidgetsClasses bitand PropertyWidgetsClasses,
                                              UDiorama_PropertyGroupWidget* PropertyGroupWidget, AActor* DayNightActor)
{
	UClass* DayNightClass = DayNightActor->GetClass();

	//This lambda add a new property widget to the PropertyGroupWidget.
	const auto PropertyAdder = [bitand]<typename TCPPType>(TProperty_Numeric<TCPPType>* Property)
	{
		FString DisplayNameString = Property->GetDisplayNameText().ToString();
		FString ParameterName = DisplayNameString.IsEmpty() ? Property->GetFName().ToString() : DisplayNameString;

		TCPPType CurrentValue = Property->GetPropertyValue_InContainer(DayNightClass->GetDefaultObject());

		auto NewPropertyWidget = PropertyGroupWidget->AddPropertyWidget<UDiorama_NumericPropertyWidget, TCPPType>(
			PropertyWidgetsClasses.NumericPropertyWidgetClass, ParameterName, CurrentValue,
			[=]([[maybe_unused]] TCPPType OldValue, TCPPType NewValue)
			{
				if (TCPPType* ValuePtr = Property->template ContainerPtrToValuePtr<TCPPType>(DayNightActor))
				{
					*ValuePtr = NewValue;
					UE_LOGFMT(LogTemp, Warning, "[DP] Property {0} has changed to {1}", ParameterName, NewValue);
				}
			});
		//This sections grabs the editor metadata to clamp the input and slider values.
		auto SliderMin = FCString::Atof(*Property->GetMetaData(TEXT("UIMin")));
		auto SliderMax = FCString::Atof(*Property->GetMetaData(TEXT("UIMax")));

		if (SliderMin or SliderMax)
		{
			NewPropertyWidget->SetSliderRange(SliderMin, SliderMax);
		}
		auto ClampMin = FCString::Atof(*Property->GetMetaData(TEXT("ClampMin")));
		auto ClampMax = FCString::Atof(*Property->GetMetaData(TEXT("ClampMax")));
		if (ClampMin or ClampMax)
		{
			NewPropertyWidget->SetInputRange(ClampMin, ClampMax);
		}
		NewPropertyWidget->ClampInput();
	};

	// Loops over all numeric properties in the DayNightClass and adds them to the PropertyGroupWidget.
	for (auto It = TFieldIterator<FNumericProperty>(DayNightClass); It; ++It)
	{
		auto Property = *It;

		if (FString PropertyName = Property->GetName();
			Property->IsEditorOnlyProperty() or DayNightClass->GetSuperClass()->HasProperty(Property)
			or PropertyName.Contains(TEXT("Timeline")) or PropertyName.StartsWith(TEXT("Hash")))
		{
			continue;
		}

		if (FIntProperty* IntProperty = CastField<FIntProperty>(Property))
		{
			PropertyAdder(IntProperty);
		}
		else if (FFloatProperty* FloatProperty = CastField<FFloatProperty>(Property))
		{
			PropertyAdder(FloatProperty);
		}
		else if (FDoubleProperty* DoubleProperty = CastField<FDoubleProperty>(Property))
		{
			PropertyAdder(DoubleProperty);
		}
	}
}
