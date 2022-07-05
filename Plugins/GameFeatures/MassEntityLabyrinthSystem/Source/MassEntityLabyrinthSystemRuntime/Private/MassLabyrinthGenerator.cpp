// Fill out your copyright notice in the Description page of Project Settings.


#include "MassLabyrinthGenerator.h"

#include "MassSpawnLocationProcessor.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "Kismet/KismetMathLibrary.h"


UMassLabyrinthGenerator::UMassLabyrinthGenerator()
{
}


void UMassLabyrinthGenerator::Generate(UObject& QueryOwner, TConstArrayView<FMassSpawnedEntityType> EntityTypes,
                                       int32 Count, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate) const
{
	if (Count <= 0 || !LabyrinthLogicSolver)
	{
		FinishedGeneratingSpawnPointsDelegate.Execute(TArray<FMassEntitySpawnDataGeneratorResult>());
		return;
	}

	const AActor* OwnerActor = Cast<AActor>(&QueryOwner);
	if (!OwnerActor)
	{
		FinishedGeneratingSpawnPointsDelegate.Execute(TArray<FMassEntitySpawnDataGeneratorResult>());
		UE_LOG(LogTemp, Warning, TEXT("Лабиринт Генератор может работать только на сцене, а его Овнер не является Актором"))
		return;
	}

	
	
	const FSolveResult SolveResult = LabyrinthLogicSolver->SolveLabyrinth();

	const FTransform InitialTransform = OwnerActor->GetTransform();
	TArray<FTransform> WallTransforms{};
	
	LabyrinthLogicSolver->BuildTransformFromSolveResult(InitialTransform, SolveResult, WallTransforms);
	
	
	
	//____________________________________________________________________________________________
	const int32 WallCount = WallTransforms.Num();
	TArray<FMassEntitySpawnDataGeneratorResult> Results;
	BuildResultsFromEntityTypes(WallCount, EntityTypes, Results);
	
	// Distribute points amongst the entities to spawn.
	for (FMassEntitySpawnDataGeneratorResult& Result : Results)
	{
		Result.SpawnDataProcessor = UMassSpawnLocationProcessor::StaticClass();
		Result.SpawnData.InitializeAs<FMassTransformsSpawnData>();
		FMassTransformsSpawnData& EntityTransforms = Result.SpawnData.GetMutable<FMassTransformsSpawnData>();
		EntityTransforms.Transforms.Reserve(Result.NumEntities);
		
		for (int i = 0; i < Result.NumEntities; i++)
		{
			FTransform& Transform = EntityTransforms.Transforms.AddDefaulted_GetRef();
			Transform = WallTransforms[i];
		}
	}
	FinishedGeneratingSpawnPointsDelegate.Execute(Results);
	
}
