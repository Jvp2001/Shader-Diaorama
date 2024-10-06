// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/Custom/WindowUserWidget.h"


void UDEPRECATED_WindowUserWidget::SetWindowTitle(FText NewTitle)
{

	WindowData.Config.Title = std::move(NewTitle);
}
