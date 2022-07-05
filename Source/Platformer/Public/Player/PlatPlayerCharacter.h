// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlatCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlatPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API APlatPlayerCharacter : public APlatCharacterBase
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	APlatPlayerCharacter();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Camera")
	UCameraComponent* FollowCamera;

};
