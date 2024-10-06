// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widgets/Diorama_PropertiesPanelWidget.h"

#include "UMG/Widgets/Diorama_PropertyGroupWidget.h"
#include "Components/VerticalBoxSlot.h"
#include "PropertyGrabber.h"
#include "Kismet/GameplayStatics.h"

void UDiorama_PropertiesPanelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CreateMaterialParameterCollectionPropertyGroup(TEXT("Grass"), GrassParameterCollection);
	CreateMaterialParameterCollectionPropertyGroup(TEXT("Wind"), WindParameterCollection);

	if (AActor* DayNightActor = UGameplayStatics::GetActorOfClass(this, DayNightActorClass))
	{
		UDiorama_PropertyGroupWidget* GroupWidget = AddNewPropertyGroup(TEXT("Day Night"));
		FPropertyGrabber::GrabAndStoreProperties(PropertyWidgetsClasses, GroupWidget, DayNightActor);
	}
}

FDiorama_PropertyWidgetsClasses& UDiorama_PropertiesPanelWidget::GetPropertyWidgetsClasses()
{
	return PropertyWidgetsClasses;
}

void UDiorama_PropertiesPanelWidget::K2_AddPropertyGroup(TSubclassOf<UDiorama_PropertyGroupWidget> Class)
{
	auto Widget = CreateWidget<UDiorama_PropertyGroupWidget>(GetOwningPlayer(), Class);
	PropertyGroupsContainer->AddChild(Widget);
}

UDiorama_PropertyGroupWidget* UDiorama_PropertiesPanelWidget::AddNewPropertyGroup(const FStringView GroupName)
{
	UDiorama_PropertyGroupWidget* GroupWidget = CreateWidget<UDiorama_PropertyGroupWidget>(
		GetOwningPlayer(), PropertyWidgetsClasses.PropertyGroupWidgetClass);
	GroupWidget->SetName(FName(GroupName));

	UVerticalBoxSlot* NewSlot = PropertyGroupsContainer->AddChildToVerticalBox(GroupWidget);
	NewSlot->SetPadding(FMargin(0, 0, 0, PropertyGroupVerticalSpacing));

	return GroupWidget;
}

void UDiorama_PropertiesPanelWidget::CreateMaterialParameterCollectionPropertyGroup(const FStringView GroupName,
	UMaterialParameterCollection* ParameterCollection)
{
	FPropertyGrabber::GrabAndStoreProperties(PropertyWidgetsClasses, AddNewPropertyGroup(GroupName), ParameterCollection);
}
