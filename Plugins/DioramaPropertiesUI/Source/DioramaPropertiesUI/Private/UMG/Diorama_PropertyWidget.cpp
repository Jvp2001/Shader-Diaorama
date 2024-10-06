// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Widgets/Diorama_PropertyWidget.h"

#include "Components/TextBlock.h"

void UDiorama_PropertyWidget::SetName(const FStringView Name) const
{
	PropertyName->SetText(FText::FromStringView(Name));
}

void UDiorama_PropertyWidget::SetName(const FName Name) const
{
	if( Name == NAME_None)
		return;


	PropertyName->SetText(FText::FromName(Name));
}

FText UDiorama_PropertyWidget::GetPropertyName() const
{
	return PropertyName->GetText();
}
