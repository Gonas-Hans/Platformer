// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LabyrinthSolverConfig.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FWallSettings
{
	GENERATED_BODY()
	
	// used for step size
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CellSize{200, 200, 200};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform TransformOffset{FRotator(0, 0, 0), FVector(0, 0, 0), FVector(1, 1, 1)};
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLabyrinthSettingsChanged, FName, PropertyName);


UCLASS()
class LABYRINTHALGORITHMSRUNTIME_API ULabyrinthSolverConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnLabyrinthSettingsChanged OnLabyrinthSettingsChangedDelegate;
	
	// used cell count
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	FIntVector LabyrinthArea{20, 20, 1};
	
	// used for generate horizontal line of walls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	FWallSettings Horizontal_Wall_Settings{};
	
	// used for generate vertical line of walls
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	FWallSettings Vertical_Wall_Settings{};

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	bool GenerateVerticalWalls{true};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	bool GenerateHorizontalWalls{true};
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings", meta = (ClampMin = "0", UIMin = "0"))
	//int32 LabyrinthLineCountPerExecution{1};

	
	
	
	
};
