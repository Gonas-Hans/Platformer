// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LabyrinthLogicSolverBase.h"
#include "MassEntitySpawnDataGeneratorBase.h"
#include "MassLabyrinthGenerator.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ELabyrinthAreaSettingPolicy
{
	Use_MassSpawnerCount_As_LabyrinthLineWidth,
	Use_CustomAreaFromSettings
	
};

UCLASS(BlueprintType, meta=(DisplayName="Labytinth Generator"))
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API UMassLabyrinthGenerator : public UMassEntitySpawnDataGeneratorBase
{
	GENERATED_BODY()
	UMassLabyrinthGenerator();
public:
	
	virtual void Generate(
		UObject& QueryOwner
		, TConstArrayView<FMassSpawnedEntityType> EntityTypes
		, int32 Count
		, FFinishedGeneratingSpawnDataSignature& FinishedGeneratingSpawnPointsDelegate
		) const override;

	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ULabyrinthLogicSolverBase* GetLabyrinthLogicSolver() const { return LabyrinthLogicSolver;}

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULabyrinthLogicSolverBase* LabyrinthLogicSolver;
};
