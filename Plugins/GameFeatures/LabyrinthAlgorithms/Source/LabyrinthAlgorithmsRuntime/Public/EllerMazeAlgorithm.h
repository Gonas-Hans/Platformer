// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LabyrinthLogicSolverBase.h"
#include "EllerMazeAlgorithm.generated.h"




UCLASS(Blueprintable, EditInlineNew)
class LABYRINTHALGORITHMSRUNTIME_API UEllerMazeAlgorithm :  public ULabyrinthLogicSolverBase
{
	GENERATED_BODY()

public:
	
	UEllerMazeAlgorithm();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual ELabyrinthLineType GetLastLineType() const  { return CurrentLineType;}
	
	virtual FSolveResult SolveLabyrinth_Implementation() override;

	virtual void BuildTransformFromSolveResult_Implementation(FTransform InitialLabyrinthPosition, FSolveResult SolveResult, TArray<FTransform>& Transforms) override;

	

	
protected:
	
	virtual void PreSolveLabyrinthLine();
	
	virtual void PostSolveLabyrinthLine(FSolveResult& OutResultsHandle);

	
	
	
private:
	
	void SolveVerticalLine(FSolveResult& OutResult);
	void SolveHorizontalLine(FSolveResult& OutResult);

	void CalculateTransform(const FTransform& InitTransform, const FIntVector& LabyrinthCell, const FVector& CellLenght, const FVector& Offset, const
	                        FTransform& AdditionalCustomTransform, FTransform
	                        & OutTransform) const;
	
	ELabyrinthLineType CurrentLineType{ELabyrinthLineType::Vertical};
	
	int CurrentLine{0};
	
	TMap<int32, int32> LabyrinthCellAndItsSet{};
};

