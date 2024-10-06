// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/SimpleWindowManagerSubsystem.h"

#include "Interfaces/WindowUMGInterface.h"
#include "UMG/Custom/WindowData.h"
#include "UMG/Custom/WindowUserWidget.h"

void USimpleWindowManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}
void USimpleWindowManagerSubsystem::ShowWindowForWidget(UUserWidget* WidgetToShow, bool bFocus)
{
	if (not WidgetToShow)
	{
		return;
	}
	IWindowUMGInterface* WindowUMGInterface = CastChecked<IWindowUMGInterface>(WidgetToShow);

	TSharedPtr<SWindow> WindowPtr;
	if(not WindowUMGInterface->HasValidWindow())
	{
		WindowPtr = WindowUMGInterface->GetWindowData().WindowPtr = CreateWindowForWidget(WidgetToShow);
	}
	else
	{
		WindowPtr = WindowUMGInterface->GetWindowData().WindowPtr;
	}



	if(not WindowUMGInterface->GetWindowData().bIsAddedToWindowManager)
	{
		 if (not WindowPtr.IsValid())
		 {
			 return;
		 }
		if(WindowUMGInterface->GetWindowConfig().bIsModal)
		{
			FSlateApplication::Get().AddModalWindow(WindowPtr.ToSharedRef(), WidgetToShow->TakeWidget());
		}
		else
		{
			FSlateApplication::Get().AddWindow(WindowPtr.ToSharedRef());
		}
	}

	if (bFocus and WindowPtr.IsValid())
	{
		WindowPtr->BringToFront();
	}
	WindowUMGInterface->OnWindowOpened();
	// Add the window to the stack
	OpenWindows.Push(WidgetToShow);
}

void USimpleWindowManagerSubsystem::CloseWindowForWidget(UUserWidget* WidgetToClose)
{
	const auto WindowUMGInterface = CastChecked<IWindowUMGInterface>(WidgetToClose);
	if (const TWeakPtr<SWindow> WindowPtr = GetWindowForWidget(WindowUMGInterface);
		WindowPtr.IsValid())
	{
		WindowPtr.Pin()->RequestDestroyWindow();
	}

}

TWeakPtr<SWindow> USimpleWindowManagerSubsystem::GetWindowForWidget(const UUserWidget* WidgetToFind)
{
	if (not WidgetToFind)
	{
		return nullptr;
	}
	auto* WindowUMGInterface = const_cast<IWindowUMGInterface*>(CastChecked<IWindowUMGInterface>(WidgetToFind));
	return GetWindowForWidget(WindowUMGInterface);

}

TWeakPtr<SWindow> USimpleWindowManagerSubsystem::GetWindowForWidget(IWindowUMGInterface* WidgetToFind)
{

	return WidgetToFind->GetWindowData().WindowPtr.ToWeakPtr();
}



TSharedPtr<SWindow> USimpleWindowManagerSubsystem::CreateWindowForWidget(UUserWidget* WidgetToShow)
{
	if (not WidgetToShow)
	{
		return nullptr;
	}
	const auto WindowUMGInterface = CastChecked<IWindowUMGInterface>(WidgetToShow);

	FWindowConfig& Config = WindowUMGInterface->GetWindowConfig();

	uint8 AutoCentreProp = static_cast<uint8>(Config.AutoCentre);
	const EAutoCenter AutoCentre = static_cast<EAutoCenter>(AutoCentreProp);


	auto NewWindow =  SNew(SWindow)
		.Title(Config.Title)
		.ClientSize(Config.ClientSize)
		.AutoCenter(AutoCentre)
		.IsInitiallyMaximized(Config.bIsInitiallyMaximized)
		.IsInitiallyMinimized(Config.bInitiallyMinimized)
		.HasCloseButton(Config.bHasCloseButton)
		.SupportsMinimize(Config.bHasMinimizeButton)
		.SupportsMaximize(Config.bHasMaximizeButton)
		.CreateTitleBar(Config.bHasTitleBar)
		.SaneWindowPlacement(Config.bSaneWindowPlacement)
		.ShouldPreserveAspectRatio(Config.bShouldPreserveAspectRatio)
		.UserResizeBorder(Config.bIsResizable)
		[
			WidgetToShow->TakeWidget()
		];



	WindowUMGInterface->GetWindowData().OnWindowClosed.BindLambda([this, WidgetToShow, WindowUMGInterface](const TSharedRef<SWindow>& Window)
	{
		// Remove the window from the stack
		OpenWindows.Remove(WidgetToShow);
		// Remove the window from the map
		WindowMap.Remove(WindowUMGInterface);
		// Clear the window data
		WindowUMGInterface->GetWindowData().WindowPtr.Reset();
		WindowUMGInterface->OnWindowClosed();

	});
	NewWindow->SetOnWindowClosed(WindowUMGInterface->GetWindowData().OnWindowClosed);


	return NewWindow;


}

void USimpleWindowManagerSubsystem::K2_CloseWindow(const UUserWidget* WindowToClose)
{
	auto WindowPtr = GetWindowForWidget(WindowToClose);
	if(WindowPtr.IsValid())
	{
		CloseWindow(WindowPtr.Pin().ToSharedRef());
	}
}


void USimpleWindowManagerSubsystem::CloseAllWindows(bool bRequireUserConfirmation)
{bool bCanCloseWindows = not bRequireUserConfirmation;
	if(bRequireUserConfirmation)
	{
		bCanCloseWindows = FMessageDialog::Open(EAppMsgType::YesNo, FText::FromStringView(TEXT("Close all windows?"))) == EAppReturnType::Yes;
	}
	while(OpenWindows.Num() > 0 and bCanCloseWindows)
	{
		CloseWindowOnTopOfStack();
	}
}

void USimpleWindowManagerSubsystem::CloseWindowOnTopOfStack()
{
	if(OpenWindows.Num() > 0)
	{
		CloseWindowForWidget(OpenWindows.Pop());
	}
}


void USimpleWindowManagerSubsystem::CloseWindow(const TSharedRef<SWindow>& WindowToClose)
{
	WindowToClose->RequestDestroyWindow();
}

void USimpleWindowManagerSubsystem::Deinitialize()
{
 	Super::Deinitialize();


	CloseAllWindows(false);
}

