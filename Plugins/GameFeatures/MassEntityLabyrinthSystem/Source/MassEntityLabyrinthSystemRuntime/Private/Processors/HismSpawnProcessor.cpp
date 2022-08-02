// Fill out your copyright notice in the Description page of Project Settings.


#include "Processors/HismSpawnProcessor.h"

#include "LabyrinthMassTags.h"
#include "MassCommonFragments.h"
#include "MassRepresentationFragments.h"
#include "MassRepresentationTypes.h"
#include "Fragments/HismFragments.h"

UHismSpawnProcessor::UHismSpawnProcessor()
{
	ObservedType = FHismFragment::StaticStruct();
	Operation = EMassObservedOperation::Add;
	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
}

void UHismSpawnProcessor::ConfigureQueries()
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	//EntityQuery.AddRequirement<FMassRepresentationLODFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FHismFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddTagRequirement<FHismTag>(EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FHismTypeFragment>(EMassFragmentAccess::ReadOnly);
}

void UHismSpawnProcessor::Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context)
{
	
	EntityQuery.ForEachEntityChunk(EntitySubsystem, Context, [this](FMassExecutionContext& Context)
	{
		const TConstArrayView<FTransformFragment> TransformList = Context.GetFragmentView<FTransformFragment>();
		const TConstArrayView<FMassRepresentationLODFragment> RepresentationLODList = Context.GetFragmentView<FMassRepresentationLODFragment>();
		const TConstArrayView<FHismFragment> HismsList = Context.GetFragmentView<FHismFragment>();
		const TConstArrayView<FHismTypeFragment> HismTypesList = Context.GetFragmentView<FHismTypeFragment>();
		
		const int32 NumEntities = Context.GetNumEntities();
		for (int32 EntityIdx = 0; EntityIdx < NumEntities; EntityIdx++)
		{
			const FMassEntityHandle Entity = Context.GetEntity(EntityIdx);
			const FTransformFragment& TransformFragment = TransformList[EntityIdx];
			const FMassRepresentationLODFragment& RepresentationLOD = RepresentationLODList[EntityIdx];
			const FHismTypeFragment& Type = HismTypesList[EntityIdx];
			FHismFragment HismFragment = HismsList[EntityIdx];
			
			if(HismFragment.Hism)
			{
				Context.Defer().EmplaceCommand<FDeferredCommand>([HismFragment, TransformFragment](UMassEntitySubsystem&)
				{
					HismFragment.Hism->AddInstance(TransformFragment.GetTransform(), true);
				});
			}
			else UE_LOG(LogTemp, Warning, TEXT("Hism not valid"))
		}
	});
}
