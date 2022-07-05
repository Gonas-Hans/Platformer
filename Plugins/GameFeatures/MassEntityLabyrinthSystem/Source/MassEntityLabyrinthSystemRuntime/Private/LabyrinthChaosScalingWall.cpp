// Fill out your copyright notice in the Description page of Project Settings.


#include "LabyrinthChaosScalingWall.h"

// Sets default values
ALabyrinthChaosScalingWall::ALabyrinthChaosScalingWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ALabyrinthChaosScalingWall::SetActorScale3D(FVector NewScale3D)
{
	
}

// Called when the game starts or when spawned
void ALabyrinthChaosScalingWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabyrinthChaosScalingWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

