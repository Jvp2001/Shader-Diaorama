// Copyright Epic Games, Inc. All Rights Reserved.

#include "NewUMGWidgets.h"

#define LOCTEXT_NAMESPACE "FNewUMGWidgetsModule"

void FNewUMGWidgetsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FNewUMGWidgetsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNewUMGWidgetsModule, NewUMGWidgets)