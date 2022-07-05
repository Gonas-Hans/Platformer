// Fill out your copyright notice in the Description page of Project Settings.


#include "Processors/LabyrinthMassToActorScaleTranslator.h"
#include "MassActorSubsystem.h"
#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "Tags/AgentScaleTranslatorTag.h"
#include "Tags/LabyrinthWallVisualizationTag.h"
#include "Translators/MassSceneComponentLocationTranslator.h"


ULabyrinthMassToActorScaleTranslator::ULabyrinthMassToActorScaleTranslator()
{
	ExecutionFlags = (int32)EProcessorExecutionFlags::All;
	ExecutionOrder.ExecuteInGroup = UE::Mass::ProcessorGroupNames::UpdateWorldFromMass;
	ExecutionOrder.ExecuteAfter.Add(UE::Mass::ProcessorGroupNames::Movement);
	RequiredTags.Add<FLabyrinthWallVisualizationTag>();
}

void ULabyrinthMassToActorScaleTranslator::ConfigureQueries()
{
	AddRequiredTagsToQuery(EntityQuery);
	EntityQuery.AddRequirement<FMassActorFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddTagRequirement<FAgentScaleTranslatorTag>(EMassFragmentPresence::All);
}

void ULabyrinthMassToActorScaleTranslator::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [this](FMassExecutionContext& Context)
		{
			const TArrayView<FMassActorFragment> ActorList = Context.GetMutableFragmentView<FMassActorFragment>();
			const TArrayView<FTransformFragment> TransformList = Context.GetMutableFragmentView<FTransformFragment>();

			const int32 NumEntities = Context.GetNumEntities();
			for (int32 i = 0; i < NumEntities; ++i)
			{
				if (AActor* Actor = ActorList[i].GetMutable())
				{
					Actor->SetActorScale3D(TransformList[i].GetTransform().GetScale3D());
				}
			}
		});
}