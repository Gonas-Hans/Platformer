// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassProcessor.h"
#include "LabyrinthWallScalingProcessor.generated.h"

/**
 * 
 */

UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ULabyrinthWallScalingProcessor : public  UMassProcessor
{
	GENERATED_BODY()
public:

	ULabyrinthWallScalingProcessor();
	
protected:
	FMassEntityQuery EntityQuery;

	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;
	
};
