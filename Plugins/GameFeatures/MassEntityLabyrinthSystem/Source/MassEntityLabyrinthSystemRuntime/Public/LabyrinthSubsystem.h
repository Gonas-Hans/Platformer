// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LabyrinthSystemActor.h"
#include "MassLODTypes.h"
#include "NativeGameplayTags.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

#include "Subsystems/WorldSubsystem.h"
#include "LabyrinthSubsystem.generated.h"


UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_HismReceivers);


USTRUCT()
struct FHismInitParams
{
	GENERATED_BODY()
	
	//UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	//TSubclassOf<UHierarchicalInstancedStaticMeshComponent> HISM_Class{UHierarchicalInstancedStaticMeshComponent::StaticClass()};
	
	UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	UStaticMesh* Mesh = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	TArray<UMaterialInterface*> MaterialsOverride;
	
	/** Controls whether the ISM can cast shadow or not */
	UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	bool bCastShadows = false;
	
	UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	bool bDisableCollision = false;
	
	/** Controls the mobility of the ISM */
	UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	TEnumAsByte<EComponentMobility::Type> Mobility = EComponentMobility::Movable;
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWallTypeChanged, FGameplayTag, WallType);

/**
 * This subsystem manages lifetime of all HISM components for the Mass Entity Labyrinth Visualization 
 */
UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ULabyrinthSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:

	friend ALabyrinthSystemActor;
	
	
	//
	UHierarchicalInstancedStaticMeshComponent* FindOrAddHism(FGameplayTag&, const FHismInitParams& HismConstructParams);
	
	
	UFUNCTION()
	void BatchMarkHismsRenderStateDirty();
	
	

	UFUNCTION()
	FORCEINLINE FGameplayTag GetCurrentGeneratingWallsType() const { return CurrentGeneratingWallsType; }

protected:

	// USubsystem BEGIN
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem END
	
	void OnUpdateWallsLine(const FSolveResult& SolveResult);
	

	// Map for cache What types of Hisms actor has
	UPROPERTY()
	AActor* LabyrinthSystemActor;

	
	// infos about all existing HISMs. Map (LodType, ActorGameplayTag for find the HISM Owner, Hism Type and Hism Pointer
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UHierarchicalInstancedStaticMeshComponent>> Hisms;

	FOnWallTypeChanged OnWallTypeChanged;

private:

	// gameplayTag for checking Actor is HISM receiver or not
	FGameplayTag HismReceiversTag = TAG_HismReceivers;
	
	FGameplayTag CurrentGeneratingWallsType;
	
	void InitHism(UHierarchicalInstancedStaticMeshComponent* NewHISM, const FHismInitParams& Params);
};


