// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LabyrinthSystemActor.h"

#include "LabyrinthSubsystem.h"
#include "MassLabyrinthGenerator.h"


// Sets default values
ALabyrinthSystemActor::ALabyrinthSystemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LabyrinthGenerator = CreateDefaultSubobject<UMassLabyrinthGenerator>(FName("LabyrinthGenerator"), true);
	FMassSpawnDataGenerator SpawnDataGenerator;
	SpawnDataGenerator.GeneratorClass = UMassLabyrinthGenerator::StaticClass();
	SpawnDataGenerator.bDataGenerated = true;
	SpawnDataGenerator.GeneratorInstance = LabyrinthGenerator;
	SpawnDataGenerator.Proportion = 1.f;
	SpawnDataGenerators.Add(SpawnDataGenerator);
	
}

// Called when the game starts or when spawned
void ALabyrinthSystemActor::BeginPlay()
{
	Super::BeginPlay();
	ULabyrinthSubsystem* LabyrinthSubsystem = UWorld::GetSubsystem<ULabyrinthSubsystem>(GetWorld());
	if(!LabyrinthSubsystem) return;
	//LabyrinthGenerator->GetLabyrinthLogicSolver()->GetOnLabyrinthSolvedDelegate().AddDynamic(LabyrinthSubsystem, ULabyrinthSubsystem::OnUpdateWallsLine);
	
}

// Called every frame
void ALabyrinthSystemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

