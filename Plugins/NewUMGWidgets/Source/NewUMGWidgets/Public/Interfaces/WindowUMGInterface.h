// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WindowUMGInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UWindowUMGInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This allows a widget to be used as a window without having to inherit from UWindowUserWidget.
 * This is useful for widgets that are already inheriting from another class, such as UUserWidget.
 */
class NEWUMGWIDGETS_API IWindowUMGInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual struct FWindowData& GetWindowData() = 0;
	virtual bool HasValidWindow();

	virtual struct FWindowConfig& GetWindowConfig();




	virtual void OnWindowOpened() {}
	virtual void OnWindowClosed() {}
};
