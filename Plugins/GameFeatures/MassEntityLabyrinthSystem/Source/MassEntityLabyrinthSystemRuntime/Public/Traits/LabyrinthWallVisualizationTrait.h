// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "MassVisualizationTrait.h"
#include "LabyrinthWallVisualizationTrait.generated.h"

/**
 * 
 */


UCLASS(meta=(DisplayName="Labyrinth Wall Visualization Trait"))
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ULabyrinthWallVisualizationTrait : public UMassVisualizationTrait
{
	GENERATED_BODY()
public:
	ULabyrinthWallVisualizationTrait();
protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;
};
