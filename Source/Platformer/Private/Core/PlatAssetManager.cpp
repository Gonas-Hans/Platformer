// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlatAssetManager.h"

#include "AbilitySystemGlobals.h"

void UPlatAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();

	UE_LOG(LogTemp, Error, TEXT("Hello"));
}
