// Fill out your copyright notice in the Description page of Project Settings.


#include "Slate/Custom/SimpleColourPicker.h"


FSimpleColourPickerArgs::operator FColorPickerArgs()
{
	FColorPickerArgs Args;
	Args.bUseAlpha = bUseAlpha;
	Args.bOnlyRefreshOnOk = bOnlyRefreshOnOk;
	Args.bOnlyRefreshOnMouseUp = bOnlyRefreshOnMouseUp;
	Args.InitialColor = InitialColour;
	Args.bExpandAdvancedSection = bExpandAdvancedSection;
	Args.bOpenAsMenu = bOpenAsMenu;
	Args.bClampValue = bClampValue;
	Args.bIsModal = bIsModal;

	return Args;


}
