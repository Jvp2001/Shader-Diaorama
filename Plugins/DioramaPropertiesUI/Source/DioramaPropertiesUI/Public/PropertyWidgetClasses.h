#pragma once
#include "CoreMinimal.h"
#include "PropertyWidgetClasses.generated.h"

USTRUCT(BlueprintType)
struct DIORAMAPROPERTIESUI_API FDiorama_PropertyWidgetsClasses
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDiorama_PropertyGroupWidget> PropertyGroupWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDiorama_NumericPropertyWidget> NumericPropertyWidgetClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDiorama_ColourPropertyWidget> ColourPropertyWidgetClass = nullptr;


};