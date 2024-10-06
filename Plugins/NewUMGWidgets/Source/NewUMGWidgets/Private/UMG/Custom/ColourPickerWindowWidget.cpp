// Fill out your copyright notice in the Description page of Project Settings.
#include "UMG/Custom/ColourPickerWindowWidget.h"

#include "Subsystems/SimpleWindowManagerSubsystem.h"

void UDEPRECATED_ColourPickerWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(auto WindowManagerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USimpleWindowManagerSubsystem>())
	{

		TSharedPtr<SWindow> Window = WindowManagerSubsystem->CreateWindowForWidget(this);

	}
}
