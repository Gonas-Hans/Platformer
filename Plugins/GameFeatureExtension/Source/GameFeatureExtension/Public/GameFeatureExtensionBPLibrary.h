// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFeaturesSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFeatureExtensionBPLibrary.generated.h"


UCLASS()
class UGameFeatureExtensionBPLibrary final : public UBlueprintFunctionLibrary
{
	
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category="GameFeatureExtensionPlugin")
	static FORCEINLINE void ToggleGameFeature(const FString GameFeaturePluginName, const  bool bEnable)
	{
		FString PluginURL;
		UGameFeaturesSubsystem::Get().GetPluginURLForBuiltInPluginByName(GameFeaturePluginName, PluginURL);
		bEnable ? UGameFeaturesSubsystem::Get().LoadAndActivateGameFeaturePlugin(PluginURL, FGameFeaturePluginLoadComplete()) : UGameFeaturesSubsystem::Get().UnloadGameFeaturePlugin(PluginURL);
	}
};