// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LabyrinthSystemActor.h"

// Sets default values
ALabyrinthSystemActor::ALabyrinthSystemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALabyrinthSystemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabyrinthSystemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

