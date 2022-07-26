// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PlatCharAbilitySystemComponent.h"
#include "Abilities/AttributeSets/PlatCharAttributeSetBase.h"
#include "GameFramework/Character.h"
#include "PlatCharacterBase.generated.h"

UCLASS()
class PLATFORMER_API APlatCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlatCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Character")
	UPlatCharAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Character")
	UPlatCharAttributeSetBase* AttributeSetBase;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Demo|Character")
	FText CharacterName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
