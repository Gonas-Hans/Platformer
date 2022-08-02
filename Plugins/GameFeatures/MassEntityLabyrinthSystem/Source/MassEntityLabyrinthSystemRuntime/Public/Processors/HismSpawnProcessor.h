// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassObserverProcessor.h"
#include "MassProcessor.h"
#include "HismSpawnProcessor.generated.h"

/**
 * this Processor manages HISM entities representation
 */
UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API UHismSpawnProcessor : public UMassObserverProcessor
{
	GENERATED_BODY()

public:
	UHismSpawnProcessor();

protected:
	
	
	/** Configure the owned FMassEntityQuery instances to express processor's requirements */
	virtual void ConfigureQueries() override;

	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;
	
	FMassEntityQuery EntityQuery;
	
};

