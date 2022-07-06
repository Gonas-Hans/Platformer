// Fill out your copyright notice in the Description page of Project Settings.


#include "EllerMazeAlgorithm.h"

#include "Kismet/KismetMathLibrary.h"



UEllerMazeAlgorithm::UEllerMazeAlgorithm()
{
	
}


FSolveResult UEllerMazeAlgorithm::SolveLabyrinth_Implementation()
{
	if(!GetSolverSettings())
	{
		SetSolverSettings(CreateDefaultSubobject<ULabyrinthSolverConfig>(FName("Settings")));
	}

	if (GetSolverSettings()->LabyrinthArea.X <= 0)
	{
		return FSolveResult{};
	}
	
	PreSolveLabyrinthLine();
	
	if(GetSolverSettings()->LabyrinthArea.X > LabyrinthCellAndItsSet.Num())
		{
			for(int32 i = LabyrinthCellAndItsSet.Num() ; i < GetSolverSettings()->LabyrinthArea.X; i++)
			{
				LabyrinthCellAndItsSet.Add(i, i);
			}
		}
	auto OutResult = FSolveResult{};
	OutResult.LineType =CurrentLineType;
	switch (CurrentLineType)
	{
	case ELabyrinthLineType::Vertical:
		{
			
			SolveVerticalLine(OutResult);
			break;
		}
		
	case ELabyrinthLineType::Horizontal:
		{
			SolveHorizontalLine(OutResult);
			
			break;
		}
	default:
		{
			return FSolveResult{};
		}
	}
	
	PostSolveLabyrinthLine(OutResult);
	
	return GetSolveResults().Add(CurrentLine, OutResult);
}



void UEllerMazeAlgorithm::BuildTransformFromSolveResult_Implementation(
	FTransform InitialLabyrinthPosition, FSolveResult SolveResult, TArray<FTransform>& OutTransforms)
{
	ULabyrinthSolverConfig* SolverSettings = GetSolverSettings();
	
	if(!SolverSettings) SolverSettings = SetSolverSettings(CreateDefaultSubobject<ULabyrinthSolverConfig>(FName("Settings")));
	
	switch (SolveResult.LineType)
	{
	case ELabyrinthLineType::Vertical:
		{
			for(const FIntVector LabyrinthCell : SolveResult.CellWithWall)
				
			{
				if(GetSolverSettings()->bGenerateVerticalWalls)
				{
					FTransform OutPosition = InitialLabyrinthPosition;
					CalculateTransform(InitialLabyrinthPosition
									   , LabyrinthCell
									   , SolverSettings->Vertical_Wall_Settings.CellSize
									   , SolverSettings->Vertical_Wall_Settings.TransformOffset
									   , OutPosition);
					OutTransforms.Add(OutPosition);
				}
			}
			return;
			
		}
	case ELabyrinthLineType::Horizontal:
		{
			for(const FIntVector LabyrinthCell : SolveResult.CellWithWall)
			{
				if(GetSolverSettings()->bGenerateHorizontalWalls)
				{
					FTransform OutPosition = InitialLabyrinthPosition;
					CalculateTransform(InitialLabyrinthPosition
									   , LabyrinthCell
									   , SolverSettings->Horizontal_Wall_Settings.CellSize
									   , SolverSettings->Horizontal_Wall_Settings.TransformOffset
									   , OutPosition);
					OutTransforms.Add(OutPosition);
				}
			}
			return;  
		}
	default:
		{
			return;
		}
	}
}

void UEllerMazeAlgorithm::CalculateTransform(const FTransform& InitTransform
	, const FIntVector& LabyrinthCell
	, const FVector& CellSize
	, const FTransform& TransformOffset
	, FTransform& OutTransform) const
{
	
	const FVector WallLocation = FVector(LabyrinthCell) * CellSize + TransformOffset.GetLocation();
	const	FVector RotatedLocation = InitTransform.GetRotation().RotateVector(WallLocation);

	OutTransform.AddToTranslation(RotatedLocation);
	OutTransform.SetRotation(FQuat(OutTransform.GetRotation()) * FQuat(TransformOffset.GetRotation()));
	OutTransform.SetScale3D(TransformOffset.GetScale3D());
	
}



void UEllerMazeAlgorithm::PreSolveLabyrinthLine()
{
	
}


void UEllerMazeAlgorithm::PostSolveLabyrinthLine(FSolveResult& OutResultsHandle)
{
	if(CurrentLineType == ELabyrinthLineType::Horizontal) CurrentLine += 1;
	++CurrentLineType;
	GetOnLabyrinthSolvedDelegate().Broadcast(OutResultsHandle);
}



void UEllerMazeAlgorithm::SolveVerticalLine(FSolveResult& OutResult)
{
	for(int32 CurrentCell = 0; CurrentCell <= GetSolverSettings()->LabyrinthArea.X; CurrentCell++)
	{
		
		const int32* CurrentSet = LabyrinthCellAndItsSet.Find(CurrentCell);
		
		const int32* NextSet = LabyrinthCellAndItsSet.Find(CurrentCell+1);
		
		FIntVector CellLocation = FIntVector{CurrentLine, CurrentCell, 0};
		
		if(NextSet && CurrentSet)
		{
			bool bBuild = UKismetMathLibrary::RandomBool();
			if(*CurrentSet == *NextSet || bBuild)
			{
				OutResult.CellWithWall.Add(CellLocation);
				OutResult.AllCells.Add(CellLocation, true);
				OutResult.WallCountForBuild += 1;
				continue;
			}
			else
			{
				LabyrinthCellAndItsSet.Add(CurrentCell+1, *CurrentSet);
			}
		}
		OutResult.AvailableCell.Add(CellLocation);
		OutResult.AllCells.Add(CellLocation, false);
	}
}




void UEllerMazeAlgorithm::SolveHorizontalLine(FSolveResult& OutResult)
{
	
	TMap<int32, TArray<int32>> SetAndItsCells{};
	for(int32 CurrentCell{0}; CurrentCell < GetSolverSettings()->LabyrinthArea.X; CurrentCell++)
	{
		const int32* CurrentSet = LabyrinthCellAndItsSet.Find(CurrentCell);
		if(CurrentSet) SetAndItsCells.FindOrAdd(*CurrentSet).Add(CurrentCell);
	}

	
	for(auto i : SetAndItsCells)
	{
		bool bIsBuildWay{true};
		bool bStopBuildWay{false};
		
		if(i.Value.Num() <= 1) continue; // guaranteed way
		
		for(int32 j =0; j < i.Value.Num(); j++)
		{
			
			int32 CurrentCell = i.Value[j];
			FIntVector Location = {CurrentLine, CurrentCell,  0};
			
			
			if(j == i.Value.Last()) if(!bStopBuildWay) continue;
			
			if(UKismetMathLibrary::RandomBool())
			{
				LabyrinthCellAndItsSet.Add(CurrentCell, -1);
				if(!bIsBuildWay) bStopBuildWay = true;
				
				OutResult.CellWithWall.Add(Location);
				OutResult.AllCells.Add(Location, true);
				OutResult.WallCountForBuild += 1;
				continue;
			}
			else bIsBuildWay = false;

			OutResult.AvailableCell.Add(Location);
			OutResult.AllCells.Add(Location, false);
		}
		
		
	}
	for(int32 i{0}; i < GetSolverSettings()->LabyrinthArea.X; i++)
	{
		if(LabyrinthCellAndItsSet.Find(i) && *LabyrinthCellAndItsSet.Find(i) == -1)
		{
			for(int32 j{0}; j < GetSolverSettings()->LabyrinthArea.X; j++)
			{
				if(!LabyrinthCellAndItsSet.FindKey(j)) LabyrinthCellAndItsSet.Add(i, j); 
			}
		}
	}
}



