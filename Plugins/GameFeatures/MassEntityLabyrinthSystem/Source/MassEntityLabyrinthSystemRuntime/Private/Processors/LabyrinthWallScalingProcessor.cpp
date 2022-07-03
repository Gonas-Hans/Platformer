// Fill out your copyright notice in the Description page of Project Settings.


#include "Processors/LabyrinthWallScalingProcessor.h"

#include "MassActorSubsystem.h"
#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Fragments/LabyrinthScaleFragment.h"
#include "Tags/AgentScaleTranslatorTag.h"
#include "Tags/LabyrinthWallScalingTag.h"


ULabyrinthWallScalingProcessor::ULabyrinthWallScalingProcessor()
{
	ExecutionFlags = int32(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::Movement;
}


void ULabyrinthWallScalingProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassActorFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddTagRequirement<FLabyrinthWallScalingTag>(EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FLabyrinthScaleFragment>(EMassFragmentAccess::ReadOnly);
}


void ULabyrinthWallScalingProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [this](FMassExecutionContext& Context)
	{
		
		const int32 NumEntities = Context.GetNumEntities();
		const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FLabyrinthScaleFragment> ScaleFragments = Context.GetMutableFragmentView<FLabyrinthScaleFragment>();
		//const TArrayView<FMassActorFragment> Actors = Context.GetMutableFragmentView<FMassActorFragment>();
		for (int32 EntityIndex = 0; EntityIndex < NumEntities; ++EntityIndex)
		{
			float GrowSpeed = ScaleFragments[EntityIndex].GrowSpeed;
			float TargetScale = ScaleFragments[EntityIndex].TargetScale;
			
			// grow Entity
			FTransform& TransformToChange = TransformList[EntityIndex].GetMutableTransform();
			FVector EntityScale = TransformToChange.GetScale3D();

			
			if(EntityScale.Z < TargetScale)
			{
				float Z = UKismetMathLibrary::FClamp(EntityScale.Z + Context.GetDeltaTimeSeconds() * TargetScale * GrowSpeed, 0.f, TargetScale);
				FVector NewScale = FVector(EntityScale.X, EntityScale.Y, Z);
				TransformToChange.SetScale3D(NewScale);
			}
			else
			{
				// disable this entity
				Context.Defer().RemoveTag<FLabyrinthWallScalingTag>(Context.GetEntity(EntityIndex));
				Context.Defer().RemoveTag<FAgentScaleTranslatorTag>(Context.GetEntity(EntityIndex));
			}
			
		}
	});
}
