// Fill out your copyright notice in the Description page of Project Settings.

#include "Traits/HismVisualizationTrait.h"

#include "LabyrinthMassTags.h"
#include "MassEntityTemplateRegistry.h"
#include "MassCommonFragments.h"
#include "MassRepresentationFragments.h"
#include "Engine/World.h"
#include "MassLODFragments.h"
#include "Fragments/HismFragments.h"


UHismVisualizationTrait::UHismVisualizationTrait()
{
}



void UHismVisualizationTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	UMassEntitySubsystem* EntitySubsystem = UWorld::GetSubsystem<UMassEntitySubsystem>(&World);
	if(!EntitySubsystem) return;
	ULabyrinthSubsystem* LabyrinthSubsystem = UWorld::GetSubsystem<ULabyrinthSubsystem>(&World);
	if(!LabyrinthSubsystem) return;
	
	BuildContext.AddTag<FMassCollectLODViewerInfoTag>(); // Depends on FMassViewerInfoFragment
	BuildContext.AddFragment<FTransformFragment>();
	
	FLabyrinthSubsystemFragment LabyrinthSubsystemFragment;
	LabyrinthSubsystemFragment.LabyrinthSubsystem = LabyrinthSubsystem;
	const uint32 LabyrinthSubsystemHash = UE::StructUtils::GetStructCrc32(FConstStructView::Make(LabyrinthSubsystemFragment));
	const FConstSharedStruct LabyrinthSubsystemSharedFragment =EntitySubsystem->GetOrCreateConstSharedFragment<FLabyrinthSubsystemFragment>(LabyrinthSubsystemHash, LabyrinthSubsystemFragment);
	BuildContext.AddConstSharedFragment(LabyrinthSubsystemSharedFragment);
	
	FHismFragment& HismFragment = BuildContext.AddFragment_GetRef<FHismFragment>();
	
	for(auto Hism : Hisms)
	{
		// spawm hism
		UHierarchicalInstancedStaticMeshComponent* CurrentHism = LabyrinthSubsystem->FindOrAddHism(Hism.Key, Hism.Value);
		HismFragment.Hism = CurrentHism;
		
	}
	
	FHismTypeFragment& TypeFragment = BuildContext.AddFragment_GetRef<FHismTypeFragment>();
	TypeFragment.HismTypeTag = LabyrinthSubsystem->GetCurrentGeneratingWallsType();
	BuildContext.AddFragment<FMassRepresentationLODFragment>();
	BuildContext.AddTag<FMassVisibilityCulledByDistanceTag>();
	BuildContext.AddTag<FHismTag>();
	BuildContext.AddChunkFragment<FMassVisualizationChunkFragment>();
}
