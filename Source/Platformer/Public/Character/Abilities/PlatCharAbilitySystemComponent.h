// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PlatCharAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API UPlatCharAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool CharacterAbilitiesGiven = false;
	bool StartupEffectsApplied = false;
	
};
