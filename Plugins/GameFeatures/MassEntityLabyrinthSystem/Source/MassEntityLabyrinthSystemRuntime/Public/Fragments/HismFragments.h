// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LabyrinthSubsystem.h"
#include "MassEntityTypes.h"
#include "HismFragments.generated.h"

/**
 * 
 */

USTRUCT()
struct FLabyrinthSubsystemFragment : public FMassSharedFragment
{
	GENERATED_BODY()
	
	FLabyrinthSubsystemFragment() = default;
	
	UPROPERTY(Transient)
	ULabyrinthSubsystem* LabyrinthSubsystem = nullptr;
	
	
};

USTRUCT()
struct FHismFragment : public FMassFragment
{
	GENERATED_BODY()

	FHismFragment () = default;
	UHierarchicalInstancedStaticMeshComponent* Hism = nullptr;
	
	
};

USTRUCT()
struct FHismTypeFragment : public FMassFragment
{
	GENERATED_BODY()
	
	FHismTypeFragment() = default;

	UPROPERTY()
	FGameplayTag HismTypeTag;
	
};

