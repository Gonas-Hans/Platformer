// Fill out your copyright notice in the Description page of Project Settings.

#include "Traits/LabyrinthWallVisualizationTrait.h"
#include "MassEntityTemplateRegistry.h"
#include "MassActorSubsystem.h"


ULabyrinthWallVisualizationTrait::ULabyrinthWallVisualizationTrait()
{
		Params.LODRepresentation[EMassLOD::High] = EMassRepresentationType::HighResSpawnedActor;
		Params.LODRepresentation[EMassLOD::Medium] = EMassRepresentationType::HighResSpawnedActor;
		Params.LODRepresentation[EMassLOD::Low] = EMassRepresentationType::LowResSpawnedActor;
		Params.LODRepresentation[EMassLOD::Off] = EMassRepresentationType::None;
	
}


void ULabyrinthWallVisualizationTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	Super::BuildTemplate(BuildContext, World);
	BuildContext.AddFragment<FMassActorFragment>();
}
