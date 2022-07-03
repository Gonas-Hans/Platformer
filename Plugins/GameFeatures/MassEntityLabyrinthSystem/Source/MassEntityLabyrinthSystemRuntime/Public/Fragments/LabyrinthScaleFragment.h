// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "LabyrinthScaleFragment.generated.h"

/**
 * 
 */
USTRUCT()
struct MASSENTITYLABYRINTHSYSTEMRUNTIME_API FLabyrinthScaleFragment : public FMassFragment
{
	
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float TargetScale{0};

	UPROPERTY(EditAnywhere)
	float GrowSpeed = 1.0f;
};
