// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LabyrinthSolverConfig.h"
#include "LabyrinthLogicSolverBase.generated.h"



UENUM(BlueprintType)
enum class ELabyrinthLineType : uint8
{
	MIN UMETA(Hidden),
	
	Vertical,
	Horizontal,
	
	MAX UMETA(Hidden)
};

inline ELabyrinthLineType& operator ++(ELabyrinthLineType& T)
{
	int8 NextValue = static_cast<int8>(T) + 1;
	if(NextValue == static_cast<int8>(ELabyrinthLineType::MAX))
		NextValue = static_cast<int8>(ELabyrinthLineType::MIN) + 1;
	
	T = static_cast<ELabyrinthLineType>(NextValue);
	return T;
	
};

USTRUCT(BlueprintType)
struct FSolveResult
{
	GENERATED_BODY()
	
	// bool значение показывает где стена а где проход
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FIntVector, bool> AllCells;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 WallCountForBuild;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ELabyrinthLineType LineType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FIntVector> CellWithWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FIntVector> AvailableCell;
	
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLabyrinthSolved, const FSolveResult, SolveResults);


UCLASS(Abstract)
class LABYRINTHALGORITHMSRUNTIME_API ULabyrinthLogicSolverBase : public  UObject
	{
		GENERATED_BODY()
	
public:

	ULabyrinthLogicSolverBase(){};
	
	UFUNCTION(BlueprintCallable,  BlueprintPure)
	virtual FORCEINLINE ULabyrinthSolverConfig* GetSolverSettings() const { return Settings;}
	
	UFUNCTION(BlueprintCallable)
	virtual ULabyrinthSolverConfig* SetSolverSettings(ULabyrinthSolverConfig* NewSettings) { Settings = NewSettings; return Settings;}
	
	UFUNCTION(BlueprintCallable,  BlueprintPure)
	virtual FORCEINLINE TMap<int32, FSolveResult>& GetSolveResults() { return BuildResults;}
	
	UFUNCTION()
	virtual FORCEINLINE FOnLabyrinthSolved GetOnLabyrinthSolvedDelegate() {return OnLabyrinthSolvedDelegate;};

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FSolveResult SolveLabyrinth();
	
	virtual FSolveResult SolveLabyrinth_Implementation() {PURE_VIRTUAL(ULabyrinthLogicSolverBase::SolveLabyrinth_Implementation); return FSolveResult{};};

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BuildTransformFromSolveResult(FTransform InitialLabyrinthPosition, FSolveResult SolveResult, TArray<FTransform>& OutTransforms);
	
	virtual void BuildTransformFromSolveResult_Implementation(FTransform InitialLabyrinthPosition, FSolveResult SolveResult, TArray<FTransform>& OutTransforms) {PURE_VIRTUAL(ULabyrinthLogicSolverBase::SolveLabyrinth_Implementation)};
	
	
private:

	UPROPERTY(EditAnywhere)
	ULabyrinthSolverConfig* Settings;
	
	TMap<int32, FSolveResult> BuildResults;
	
	UPROPERTY(BlueprintAssignable)
	FOnLabyrinthSolved OnLabyrinthSolvedDelegate;
	
};


