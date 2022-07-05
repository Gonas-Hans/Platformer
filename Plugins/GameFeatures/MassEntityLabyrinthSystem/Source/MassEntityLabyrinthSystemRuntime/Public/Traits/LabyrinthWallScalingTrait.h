// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "LabyrinthWallScalingTrait.generated.h"

/**
 * 
 */
UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ULabyrinthWallScalingTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

	UPROPERTY(EditAnywhere, Category = "Mass")
	float TargetScale{5.f};
	
	UPROPERTY(EditAnywhere, Category = "Mass")
	float GrowSpeed{1.f};
};
