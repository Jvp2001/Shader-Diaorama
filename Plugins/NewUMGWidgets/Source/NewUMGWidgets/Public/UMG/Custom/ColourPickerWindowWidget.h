// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowUserWidget.h"
#include "ColourPickerWindowWidget.generated.h"

/**
 * This is also deprecated in favour of the interface IWindowUMGInterface.
 */
UCLASS()
class NEWUMGWIDGETS_API UDEPRECATED_ColourPickerWindowWidget : public UDEPRECATED_WindowUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


private:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	class USimpleColourPicker* ColourPicker;
};

