// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "NewUserWidgetsFunctionLibrary.h"
//
// #include "Slate/Custom/SimpleColourPicker.h"
// #include "UMG/Custom/SimpleColourPickerWidget.h"
// #include "Widgets/Colors/SColorPicker.h"
//
//
// void UNewUserWidgetsFunctionLibrary::ShowColourPicker(UObject* WorldContextObject, const FSimpleColourPickerArgs& Args, const FOnLineColourValueChanged OnColourPicked)
// {
// 	FColorPickerArgs PickerArgs;
//
//
// 	PickerArgs.bUseAlpha = Args.bUseAlpha;
// 	PickerArgs.bOnlyRefreshOnOk = Args.bOnlyRefreshOnOk;
// 	PickerArgs.bOnlyRefreshOnMouseUp = Args.bOnlyRefreshOnMouseUp;
// 	PickerArgs.InitialColor = FLinearColor::Red;
// 	PickerArgs.bExpandAdvancedSection = Args.bExpandAdvancedSection;
// 	PickerArgs.bOpenAsMenu = Args.bOpenAsMenu;
// 	PickerArgs.bClampValue = Args.bClampValue;
// 	PickerArgs.OnColorCommitted.BindLambda([&OnColourPicked](FLinearColor InNewColour)
// 	{
// 		OnColourPicked.ExecuteIfBound(MoveTemp(InNewColour));
// 	});
// 	if(OpenColorPicker(PickerArgs))
// 	{
// 	}
// }
//
//





#include "NewUserWidgetsFunctionLibrary.h"

void UNewUserWidgetsFunctionLibrary::ShowColourPicker(const FSimpleColourPickerArgs& Args, const FSimpleColourPickerValueChangedSignature& OnColourPicked)
{
#define LOCTEXT_NAMESPACE "SimpleColourPickerWidget"
	bool Result = false;

	// Consoles do not support opening new windows
	#if PLATFORM_DESKTOP
	TSharedPtr<SWindow> Window = nullptr;

	FText WindowTitle = Args.Title;
	FColorPickerArgs ColourPickerArgs = const_cast<FSimpleColourPickerArgs&>(Args);
	ColourPickerArgs.OnColorCommitted.BindLambda([OnColourPicked, Window](FLinearColor InNewColour)
	{
#ifdef UE_EDITOR
		if(not OnColourPicked.IsBound())
		{

			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("OnColorCommitted", "OnColorCommitted is not bound."));
		}
		else
		{
			OnColourPicked.Execute(InNewColour);
		}
#else
		OnColourPicked.Execute(InNewColour);
#endif

		if(Window.IsValid())
		{
			FSlateApplication::Get().DestroyWindowImmediately(Window.ToSharedRef());
#if UE_EDITOR
			FMessageDialog::Open(EAppMsgType::Ok, FText::FromStringView(TEXT("Closing Window...")));

#endif
		}
	});




	FLinearColor OldColor = ColourPickerArgs.InitialColor;
	ensureMsgf(ColourPickerArgs.OnColorCommitted.IsBound(), TEXT("OnColourCommitted should be bound to set the color."));

	// Determine the position of the window so that it will spawn near the mouse, but not go off the screen.
	FVector2D CursorPos = FSlateApplication::Get().GetCursorPos();

	FSlateRect Anchor(CursorPos.X, CursorPos.Y, CursorPos.X, CursorPos.Y);

	FVector2D AdjustedSummonLocation = FSlateApplication::Get().CalculatePopupWindowPosition( Anchor, SColorPicker::DEFAULT_WINDOW_SIZE, true, FVector2D::ZeroVector, Orient_Horizontal );


	// Only override the color picker window creation behavior if we are not creating a modal color picker
	const bool bOverrideNonModalCreation = (SColorPicker::OnColorPickerNonModalCreateOverride.IsBound() && !ColourPickerArgs.bIsModal);

	TSharedRef<SBorder> WindowContent = SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"))
			.Padding(FMargin(8.0f, 8.0f));

	bool bNeedToAddWindow = true;
	if (!bOverrideNonModalCreation)
	{
		if (ColourPickerArgs.bOpenAsMenu && !ColourPickerArgs.bIsModal && ColourPickerArgs.ParentWidget.IsValid())
		{
			Window = FSlateApplication::Get().PushMenu(
				ColourPickerArgs.ParentWidget.ToSharedRef(),
				FWidgetPath(),
				WindowContent,
				AdjustedSummonLocation,
				FPopupTransitionEffect(FPopupTransitionEffect::None),
				false,
				FVector2D(0.f,0.f),
				EPopupMethod::CreateNewWindow,
				false)->GetOwnedWindow();

			bNeedToAddWindow = false;
		}
		else
		{
			Window = SNew(SWindow)
				.AutoCenter(EAutoCenter::None)
				.ScreenPosition(AdjustedSummonLocation)
				.SupportsMaximize(false)
				.SupportsMinimize(false)
				.SizingRule(ESizingRule::Autosized)
				.Title(WindowTitle)
				[
					WindowContent
				];
		}
	}

	TSharedRef<SColorPicker> CreatedColorPicker = SNew(SColorPicker)
		.TargetColorAttribute(OldColor)
		.UseAlpha(ColourPickerArgs.bUseAlpha)
		.ExpandAdvancedSection(ColourPickerArgs.bExpandAdvancedSection)
		.OnlyRefreshOnMouseUp(ColourPickerArgs.bOnlyRefreshOnMouseUp && !ColourPickerArgs.bIsModal)
		.OnlyRefreshOnOk(ColourPickerArgs.bOnlyRefreshOnOk || ColourPickerArgs.bIsModal)
		.OnColorCommitted(ColourPickerArgs.OnColorCommitted)
		.OnColorPickerCancelled(ColourPickerArgs.OnColorPickerCancelled)
		.OnInteractivePickBegin(ColourPickerArgs.OnInteractivePickBegin)
		.OnInteractivePickEnd(ColourPickerArgs.OnInteractivePickEnd)
		.OnColorPickerWindowClosed(ColourPickerArgs.OnColorPickerWindowClosed)
		.ParentWindow(Window)
		.DisplayGamma(ColourPickerArgs.DisplayGamma)
		.sRGBOverride(ColourPickerArgs.sRGBOverride)
		.OverrideColorPickerCreation(bOverrideNonModalCreation)
		.OptionalOwningDetailsView(ColourPickerArgs.OptionalOwningDetailsView);

	// If the color picker requested is modal, don't override the behavior even if the delegate is bound
	if (bOverrideNonModalCreation)
	{
		SColorPicker::OnColorPickerNonModalCreateOverride.Execute(CreatedColorPicker);

		// Result = true;
		//
		// //hold on to the window created for external use...
		// ColorPickerWindow = Window;
	}
	else
	{
		WindowContent->SetContent(CreatedColorPicker);

		if (ColourPickerArgs.bIsModal)
		{
			FSlateApplication::Get().AddModalWindow(Window.ToSharedRef(), ColourPickerArgs.ParentWidget);
		}
		else if (bNeedToAddWindow)
		{
			if (ColourPickerArgs.ParentWidget.IsValid())
			{
				// Find the window of the parent widget
				FWidgetPath WidgetPath;
				FSlateApplication::Get().GeneratePathToWidgetChecked(ColourPickerArgs.ParentWidget.ToSharedRef(), WidgetPath);
				Window = FSlateApplication::Get().AddWindowAsNativeChild(Window.ToSharedRef(), WidgetPath.GetWindow());
			}
			else
			{
				Window = FSlateApplication::Get().AddWindow(Window.ToSharedRef());
			}


		}
		//
		// 	Result = true;
		//
		// 	//hold on to the window created for external use...
		// 	ColorPickerWindow = Window;
		// }
		// GlobalColorPicker = CreatedColorPicker;
		#endif

	}

#undef LOCTEXT_NAMESPACE
}
