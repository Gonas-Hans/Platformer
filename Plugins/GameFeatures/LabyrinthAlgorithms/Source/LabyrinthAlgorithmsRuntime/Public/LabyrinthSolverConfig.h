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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CellLenght{200, 200, 200};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LocationOffset{0.f, 0.f, 0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform CustomTransform{};
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
	
	// считает все в целых клетках
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	FIntVector LabyrinthArea{2000, 2000, 1};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	FIntVector LabyrinthCellArea{200, 200, 0};
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings")
	bool bCustomWallRotation{false};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LabyrinthSettings", meta = (ClampMin = "0", UIMin = "0"))
	int32 LabyrinthLineCountPerExecution{1};

	
	
	
	
};
