// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "UMG/Custom/SimpleColourPickerWidget.h"
//
// #include "Slate/Custom/SimpleColourPicker.h"
//
//
// #define LOCTEXT_NAMESPACE "SimpleColourPickerWidget"
//
// USimpleColourPickerWidget::USimpleColourPickerWidget(const FObjectInitializer& ObjectInitializer)
// 	:Super(ObjectInitializer),
// 	Colour(FLinearColor::Red)
// {
// }
//
// void USimpleColourPickerWidget::SynchronizeProperties()
// {
// 	Super::SynchronizeProperties();
// }
//
// const FText USimpleColourPickerWidget::GetPaletteCategory()
// {
// 	return LOCTEXT("New UMG Widgets", "New Widgets");
// }
// #if WITH_EDITOR
//
// void USimpleColourPickerWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
// {
// 	Super::PostEditChangeProperty(PropertyChangedEvent);
// 	const FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
// 	if (PropertyName == GET_MEMBER_NAME_CHECKED(USimpleColourPickerWidget, Colour))
// 	{
// 		UpdateColour(Colour);
// 	}
// }
// #endif
//
//
//
// TSharedRef<SWidget> USimpleColourPickerWidget::RebuildWidget()
// {
// 	SimpleColourPicker = SNew(SSimpleColourPicker)
// 	.UseAlpha(bUseAlpha)
// 	.DisplayInlineVersion(bUseInlineColourPicker)
// 	.OnColorCommitted_UObject(this, &ThisClass::UpdateColour)
// 	;
//
// 	return SimpleColourPicker.ToSharedRef();
// }
//
// void USimpleColourPickerWidget::ReleaseSlateResources(bool bReleaseChildren)
// {
// 	Super::ReleaseSlateResources(bReleaseChildren);
//
// 	if(SimpleColourPicker.IsValid())
// 		SimpleColourPicker.Reset();
//
// }
//
// void USimpleColourPickerWidget::UpdateColour(FLinearColor NewColour)
// {
// 	Colour = MoveTemp(NewColour);
//
// 	if (SimpleColourPicker.IsValid())
// 	{
// 		if(bUseAlpha)
// 			SimpleColourPicker->SetColourRGBA(Colour);
// 		else
// 			SimpleColourPicker->SetColourRGB(Colour);
// 	}
// 	// OnPickedColourChanged.Broadcast(Colour);
// }
//
//
// #undef LOCTEXT_NAMESPACE


#include "UMG/Custom/SimpleColourPickerWidget.h"



#include "UObject/ConstructorHelpers.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Slate/Custom/SimpleColourPicker.h"

#define LOCTEXT_NAMESPACE "UMG"

USimpleColourPicker::USimpleColourPicker(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, JoyColor(FLinearColor::Red)
{}

#if WITH_EDITOR
/*
const FSlateBrush* UJoyColorWheel::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Image");
}
*/

const FText USimpleColourPicker::GetPaletteCategory()
{
	return LOCTEXT("Victory Plugin", "Victory Plugin");
}

void USimpleColourPicker::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	//Update Picker to JoyColor property change!
	if (PropertyName == TEXT("JoyColor"))
	{
		SetJoyColor(JoyColor,true);
	}
}
#endif

void USimpleColourPicker::SetJoyColor(FLinearColor NewColor, bool SkipAnimation)
{
	if(!MySlateColorPicker.IsValid())
	{
		return;
	}

	//Skip Anim?
	if(SkipAnimation)
	{
		MySlateColorPicker->InstantColor = NewColor;
		MySlateColorPicker->Animation_SkipToFinalForOneTick = true;		//See SJoyColorPicker.h
	}
	else
	{
		//Set!
		MySlateColorPicker->SetColorRGB(NewColor);
	}
}

void USimpleColourPicker::ColorUpdated(FLinearColor NewValue)
{
	JoyColor = NewValue;

	if(OnColorChanged.IsBound())
	{
		OnColorChanged.Broadcast(JoyColor);
	}
}

TSharedRef<SWidget> USimpleColourPicker::RebuildWidget()
{
	MySlateColorPicker = SNew( SSimpleColourPicker )
		.TargetColorAttribute( JoyColor )
		.OnColorCommitted( FOnLinearColorValueChanged::CreateUObject( this, &USimpleColourPicker::ColorUpdated) );

	return MySlateColorPicker.ToSharedRef();
}

//Release
void USimpleColourPicker::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	if(MySlateColorPicker.IsValid())
	{
		MySlateColorPicker.Reset();
	}
}

void USimpleColourPicker::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetJoyColor(JoyColor,true);
}


/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE