// Fill out your copyright notice in the Description page of Project Settings.


#include "Traits/LabyrinthWallScalingTrait.h"
#include "MassCommonFragments.h"
#include "MassEntityTemplateRegistry.h"
#include "Fragments/LabyrinthScaleFragment.h"
#include "Tags/LabyrinthWallScalingTag.h"


void ULabyrinthWallScalingTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	BuildContext.AddFragment<FTransformFragment>();
	FLabyrinthScaleFragment& ScaleFragment = BuildContext.AddFragment_GetRef<FLabyrinthScaleFragment>() ;
	ScaleFragment.TargetScale = TargetScale;
	ScaleFragment.GrowSpeed = GrowSpeed;
	BuildContext.AddTag<FLabyrinthWallScalingTag>();;
	
}
