// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widgets/Diorama_PropertyGroupWidget.h"

#include "Components/TextBlock.h"

void UDiorama_PropertyGroupWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PropertyGroupNameLabel->TextDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ThisClass, GetTitleName));

}

FText UDiorama_PropertyGroupWidget::GetTitleName()
{
	return FText::FromName(TitleName);
}
