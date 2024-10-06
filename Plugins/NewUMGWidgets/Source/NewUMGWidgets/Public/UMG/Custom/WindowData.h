#pragma once
#include "CoreMinimal.h"
#include "Widgets/SWindow.h"
#include "WindowData.generated.h"
/** Enum to describe how to auto-center an SWindow
* This has to be redeclared here because it's not exposed to blueprint.
*/
UENUM()
enum class EAutoCentre : uint8
{
	/** Don't auto-center the window */
	None,

	/** Auto-center the window on the primary work area */
	PrimaryWorkArea,

	/** Auto-center the window on the preferred work area, determined using GetPreferredWorkArea() */
	PreferredWorkArea,
};


USTRUCT(BlueprintType)
struct FWindowConfig
{
	GENERATED_BODY()


	// Create properties based on the properties of SWindow
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	FText Title = FText::FromStringView(TEXT("Properties"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	FVector2D ClientSize = FVector2D(1280, 720);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	EAutoCentre AutoCentre = EAutoCentre::None;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bIsInitiallyMaximized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bInitiallyMinimized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bIsModal = false;

	/** Does this window have a close button? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bHasCloseButton = true;

	/** Does this window have a minimize button? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bHasMinimizeButton = true;

	/** Does this window have a maximize button? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bHasMaximizeButton = true;

	/** Does this window have a title bar? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bHasTitleBar = true;

	/** If the window appears of  screen, or too large to safely fit on screen,
	 * this flag will force realistic constraints on the window and bring it back into view.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bSaneWindowPlacement = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bShouldPreserveAspectRatio = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bIsPopupWindow = false;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bIsTopmostWindow = false;

	/**
	 * Should this window be focused when first shown?
	 * @remark If bIsModal, bIsPopupWindow or bIsTopmostWindow is true, then this will be set to true automatically.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bFocusWhenFirstShown = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Window Config")
	bool bIsResizable = true;

};

USTRUCT(BlueprintType)
struct FWindowData
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	FWindowConfig Config;

	TSharedPtr<SWindow> WindowPtr;

	FOnWindowClosed OnWindowClosed;

	bool bIsAddedToWindowManager = false;
};
