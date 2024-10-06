// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Templates/SharedPointer.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SimpleWindowManagerSubsystem.generated.h"


class IWindowUMGInterface;
class UDEPRECATED_WindowUserWidget;

/**
 * @remark All types have to derive IWindowUMGInterface to handled by the SimpleWindowManagerSubsystem.
 */
UCLASS()
class NEWUMGWIDGETS_API USimpleWindowManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//~ Begin UGameInstanceSubsystem Interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//~ End of UGameInstanceSubsystem Interface
	UFUNCTION(BlueprintCallable, Category = "Simple Window Manager")
	void ShowWindowForWidget(UUserWidget* WidgetToShow, bool bFocus = true);

	UFUNCTION(BlueprintCallable, Category = "Simple Window Manager")
	void CloseWindowForWidget(UUserWidget* WidgetToClose);



	TWeakPtr<SWindow> GetWindowForWidget(const UUserWidget* WidgetToFind);
	TWeakPtr<SWindow> GetWindowForWidget(IWindowUMGInterface* WidgetToFind);

	// Create a method for creating a window from a widget
	TSharedPtr<SWindow> CreateWindowForWidget(UUserWidget* WidgetToShow);

	UFUNCTION(BlueprintCallable, Category = "Simple Window Manager", DisplayName="Close Window")
	void K2_CloseWindow(const  UUserWidget* WindowToClose);
	void CloseWindow(const TSharedRef<SWindow>& WindowToClose);

	UFUNCTION(BlueprintCallable, Category = "Simple Window Manager")
	void CloseAllWindows(bool bRequireUserConfirmation = true);

protected:

	void CloseWindowOnTopOfStack();


private:
	TMap<IWindowUMGInterface*, TWeakPtr<SWindow>> WindowMap;

	// Stack of windows that are currently open
	UPROPERTY()
	TArray<UUserWidget*> OpenWindows;






	friend class IWindowUMGInterface;
};
