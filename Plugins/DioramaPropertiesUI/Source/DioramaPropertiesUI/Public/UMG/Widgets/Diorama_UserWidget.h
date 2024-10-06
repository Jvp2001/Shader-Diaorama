// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/WindowUMGInterface.h"
#include "UMG/Custom/WindowUserWidget.h"
#include "Diorama_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIORAMAPROPERTIESUI_API UDiorama_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:


#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override { return FText::FromString(TEXT("Diorama")); }
#endif





	
};
