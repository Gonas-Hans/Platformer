// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LabyrinthSubsystem.h"
#include "MassEntityTraitBase.h"
#include "MassRepresentationFragments.h"
#include "HismVisualizationTrait.generated.h"



/*
 * This trait contains a visualization fragment for custom Labyrinth Representation Processor which using two arrays of HISM for
 * visualization Entities, first array contains a HISM with collision for 1 LOD, second array contains HISM without collision.
 */
UCLASS(meta=(DisplayName="Hierarchical Instanced Static Mesh Visualization"))
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API UHismVisualizationTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()
public:
	UHismVisualizationTrait();

	/*
	 * HISMs Settings
	 *
	*/
	UPROPERTY(EditAnywhere, Category = "Mass|Visual")
	TMap<FGameplayTag, FHismInitParams> Hisms{};


protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

};
