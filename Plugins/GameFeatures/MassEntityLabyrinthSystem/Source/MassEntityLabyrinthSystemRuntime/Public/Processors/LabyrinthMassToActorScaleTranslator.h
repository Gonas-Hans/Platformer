// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityQuery.h"
#include "MassTranslator.h"
#include "LabyrinthMassToActorScaleTranslator.generated.h"

/**
 * 
 */
UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ULabyrinthMassToActorScaleTranslator : public UMassTranslator
{
	GENERATED_BODY()

public:
	ULabyrinthMassToActorScaleTranslator();

protected:
	virtual void ConfigureQueries() override;
	virtual void Execute(UMassEntitySubsystem& EntitySubsystem, FMassExecutionContext& Context) override;

	FMassEntityQuery EntityQuery;
};