// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Diorama_UserWidget.h"
#include "PropertyWidgetClasses.h"
#include "Diorama_PropertiesPanelWidget.generated.h"

struct FDiorama_PropertyInfo;
/**
 *
 */
UCLASS(Abstract)
class DIORAMAPROPERTIESUI_API UDiorama_PropertiesPanelWidget : public UDiorama_UserWidget , public IWindowUMGInterface
{
	GENERATED_BODY()

public:

	virtual FWindowData& GetWindowData() override final { return WindowData; }

	virtual void NativeOnInitialized() override;
	FDiorama_PropertyWidgetsClasses& GetPropertyWidgetsClasses();


	UFUNCTION(BlueprintCallable, DisplayName="Add Property Group")
	void K2_AddPropertyGroup(TSubclassOf<UDiorama_PropertyGroupWidget> Class);
	UDiorama_PropertyGroupWidget* AddNewPropertyGroup(const FStringView GroupName);


	void CreateMaterialParameterCollectionPropertyGroup(const FStringView GroupName, UMaterialParameterCollection* ParameterCollection);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnNativePropertyGroupsAdded();

private:

	UPROPERTY(DisplayName="Root", meta=(BindWidget))
	TObjectPtr<class UVerticalBox> Root = nullptr;

	UPROPERTY(DisplayName="Panel Title", meta=(BindWidget))
	TObjectPtr<class UTextBlock> PanelTitle = nullptr;

	UPROPERTY(DisplayName="Property Groups Container", meta=(BindWidget))
	TObjectPtr<class UVerticalBox> PropertyGroupsContainer = nullptr;

	UPROPERTY(EditAnywhere)
	FDiorama_PropertyWidgetsClasses PropertyWidgetsClasses;

	UPROPERTY(EditAnywhere, Category="Properties")
	TObjectPtr<class UMaterialParameterCollection> WindParameterCollection = nullptr;

	UPROPERTY(EditAnywhere, Category="Properties")
	TObjectPtr<class UMaterialParameterCollection> GrassParameterCollection = nullptr;

	UPROPERTY(EditAnywhere, Category="Properties")
	TSubclassOf<AActor> DayNightActorClass = nullptr;

	UPROPERTY(EditAnywhere, Category="Properties")
	double PropertyGroupVerticalSpacing{20.0};

	UPROPERTY(EditDefaultsOnly, Category = "Diorama")
	FWindowData WindowData;
};
