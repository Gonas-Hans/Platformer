// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlatCharAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class PLATFORMER_API UPlatCharAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	// Current Health, when 0 we expect owner to die unless prevented by an ability. Capped by MaxHealth.
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, Health)
	
	// MaxHealth is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, MaxHealth)

	// Health regen rate will passively increase Health every second
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, HealthRegenRate)

	// Current Energy, used to execute special abilities. Capped by MaxEnergy.
	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, Energy)

	// MaxEnergy is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, MaxEnergy)

	// Energy regen rate will passively increase Health every second
	UPROPERTY(BlueprintReadOnly, Category = "Energy")
	FGameplayAttributeData EnergyRegenRate;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, EnergyRegenRate)

	UPROPERTY(BlueprintReadOnly, Category = "Character Level")
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, CharacterLevel)

	// Experience points gained from killing enemies. Used to level up.
	UPROPERTY(BlueprintReadOnly, Category = "XP")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, XP)

	// Experience points awarded to the character's killers. Used to level up.
	UPROPERTY(BlueprintReadOnly, Category = "XP")
	FGameplayAttributeData XPBounty;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, XPBounty)

	// Gold gained from killing enemies. Used to purchase items.
	UPROPERTY(BlueprintReadOnly, Category = "Gold")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, Gold)

	// Gold awarded to the character's killer. Used to purchase items.
	UPROPERTY(BlueprintReadOnly, Category = "Gold")
	FGameplayAttributeData GoldBounty;
	ATTRIBUTE_ACCESSORS(UPlatCharAttributeSetBase, GoldBounty)
};
