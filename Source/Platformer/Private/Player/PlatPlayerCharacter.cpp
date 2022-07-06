// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlatPlayerCharacter.h"

APlatPlayerCharacter::APlatPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	
}
