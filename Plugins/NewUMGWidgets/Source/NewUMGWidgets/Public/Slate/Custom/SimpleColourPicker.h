// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
#pragma once
#include "CoreMinimal.h"
#include "Widgets/Colors/SColorPicker.h"
#include "Framework/SlateDelegates.h"
#include "SimpleColourPicker.generated.h"
DECLARE_DYNAMIC_DELEGATE_OneParam(FSimpleColourPickerValueChangedSignature, FLinearColor, NewColour);

USTRUCT(BlueprintType)
struct FSimpleColourPickerArgs
{
	GENERATED_BODY()
	//Copy all the args from FColorPickerArgs and make them blueprint accessible


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	FLinearColor InitialColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bUseAlpha = true;

	/** Whether to disable the refresh except on mouse up for performance reasons. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bOnlyRefreshOnMouseUp = false;

	/** Whether to disable the refresh until the picker closes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bOnlyRefreshOnOk = false;

	/** Whether to automatically expand the Advanced section. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bExpandAdvancedSection = true;

	/** Whether to open the color picker as a menu window. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bOpenAsMenu = false;

	/** Set true if values should be max to 1.0. HDR values may go over 1.0. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bClampValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Simple Colour Picker Args")
	bool bIsModal = false;





	operator FColorPickerArgs();
};
//
// /**
//  *
//  */
// class NEWUMGWIDGETS_API SSimpleColourPicker : public SColorPicker
// {
// public:
// 	void SetColourRGB(const FLinearColor& InNewColour)
// 	{
// 		SetNewTargetColorRGB({InNewColour.R, InNewColour.B, InNewColour.G, 1.0f}, true);
// 	}
//
// 	void SetColourHSV(const FLinearColor& InNewColour)
// 	{
// 		SetNewTargetColorHSV(InNewColour, true);
// 	}
//
// 	void SetColourRGBA(const FLinearColor& InNewColour)
// 	{
// 		SetNewTargetColorRGB(InNewColour, true);
// 	}
// };



/*
	By  for You

	You are welcome to use this code anywhere as long as you include this notice.
*/


class NEWUMGWIDGETS_API SSimpleColourPicker
	: public SColorPicker
{
	typedef SColorPicker Super;

public: //! <~~~~~
	FORCEINLINE void SetColorRGB(const FLinearColor& NewColor)
	{
		//This is protected in SColorPicker
		//		so can't call it from UMG component
		SetNewTargetColorRGB( NewColor, true ); //Force Update
	}

	//Animation

	FLinearColor InstantColor;
	bool Animation_SkipToFinalForOneTick = false;
	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override
	{
		//Skip to final, then resume normal animation behavior
		if(Animation_SkipToFinalForOneTick)
		{
			Animation_SkipToFinalForOneTick = false;
			Super::Tick(AllottedGeometry, InCurrentTime, 10000); //<~~~ because all the required vars like CurrentTime are private :)
			SetColorRGB(InstantColor);
			return;
			//~~~~
		}

		//Animate normally!
		Super::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	}
};
