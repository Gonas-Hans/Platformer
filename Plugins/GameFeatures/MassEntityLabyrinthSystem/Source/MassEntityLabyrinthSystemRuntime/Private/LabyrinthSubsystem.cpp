// Fill out your copyright notice in the Description page of Project Settings.


#include "LabyrinthSubsystem.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagsManager.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


UE_DEFINE_GAMEPLAY_TAG(TAG_HismReceivers, "LabyrinthSystem.HISM_Owner")




UHierarchicalInstancedStaticMeshComponent* ULabyrinthSubsystem::FindOrAddHism(FGameplayTag& HismTag,  const FHismInitParams& HismConstructParams)
{
	TObjectPtr<UHierarchicalInstancedStaticMeshComponent>* CurrentHism = Hisms.Find(HismTag);
	// init new HISM if it no exist
	if(CurrentHism && CurrentHism->Get())
	{
		if(LabyrinthSystemActor)
		{
			UHierarchicalInstancedStaticMeshComponent* NewHism = NewObject<UHierarchicalInstancedStaticMeshComponent>(LabyrinthSystemActor, HismConstructParams.HISM_Class);
			if(NewHism)
			{
				NewHism->SetupAttachment(LabyrinthSystemActor->GetRootComponent());
				NewHism->RegisterComponent();
				InitHism(NewHism, HismConstructParams);
				return NewHism;
			}
		}
	}
	return nullptr;
}


void ULabyrinthSubsystem::BatchMarkHismsRenderStateDirty()
{
	for(auto HismComp :  Hisms)
	{
		if(HismComp.Value) HismComp.Value.Get()->MarkRenderStateDirty();
	}
}

void ULabyrinthSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void ULabyrinthSubsystem::Deinitialize()
{
	
}

void ULabyrinthSubsystem::OnUpdateWallsLine(const FSolveResult& SolveResult)
{
	//CurrentGeneratingWallsType = SolveResult.LineType;
}

void ULabyrinthSubsystem::InitHism(UHierarchicalInstancedStaticMeshComponent* NewHISM, const FHismInitParams& Params)
{
	if(NewHISM)
	{
		NewHISM->bDisableCollision = Params.bDisableCollision;
		NewHISM->SetStaticMesh(Params.Mesh);
		NewHISM->SetMobility(Params.Mobility);
		NewHISM->SetCastShadow(Params.bCastShadows);
		int16 MaterialIndex{0};
		for(auto i : Params.MaterialsOverride)
		{
			NewHISM->SetMaterial(MaterialIndex, i);
			MaterialIndex++;
		}
	}
}
