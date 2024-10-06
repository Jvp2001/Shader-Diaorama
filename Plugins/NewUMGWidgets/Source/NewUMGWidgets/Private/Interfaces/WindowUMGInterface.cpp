// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/WindowUMGInterface.h"

#include "UMG/Custom/WindowData.h"


// Add default functionality here for any IWindowUMGInterface functions that are not pure virtual.
bool IWindowUMGInterface::HasValidWindow()
{

	return GetWindowData().WindowPtr.IsValid();
}

FWindowConfig& IWindowUMGInterface::GetWindowConfig()
{
	return GetWindowData().Config;
}
