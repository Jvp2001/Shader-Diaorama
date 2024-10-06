// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowData.h"
#include "Blueprint/UserWidget.h"
#include "WindowUserWidget.generated.h"



/**
 * This was used to create a window in the editor; it is now deprecated in favour of the interface IWindowUMGInterface.
 */
UCLASS(BlueprintType, Deprecated, Blueprintable, meta = (Category = "Window"))
class NEWUMGWIDGETS_API UDEPRECATED_WindowUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FWindowConfig& GetWindowConfig() { return WindowData.Config; }

	UFUNCTION(BlueprintNativeEvent)
	void OnWindowOpened();

	virtual void OnWindowOpened_Implementation()
	{
	}

	UFUNCTION(BlueprintNativeEvent)
	void OnWindowClosed();

	virtual void OnWindowClosed_Implementation()
	{
	}

	UFUNCTION(BlueprintCallable, Category = "Window")
	void SetWindowTitle(FText NewTitle);


protected:
	bool HasValidWindow() const { return WindowData.WindowPtr.IsValid(); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config", meta=(AllowPrivateAccess))
	FWindowData WindowData;

private:

	friend class USimpleWindowManagerSubsystem;
};
