// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "TestGeometryCollectionComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API UTestGeometryCollectionComponent : public UGeometryCollectionComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ResetGeoCollection()
	{
		ResetDynamicCollection();
	}
};
