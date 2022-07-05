﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InstancedStruct.h"
#include "MassEntityTraitBase.h"
#include "UObject/Object.h"
#include "AssortedTags.generated.h"

/**
 * MASS ENTITY EXTENSION PLUGIN
 * The build in assorted fragments will probably do this too at some point
 */
UCLASS(meta=(DisplayName="Assorted Tags"))
class MASSENTITYEXTENSION_API UAssortedTags : public UMassEntityTraitBase
{
	GENERATED_BODY()
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const override;

	UPROPERTY(EditAnywhere, meta = (BaseStruct = "MassTag", ExcludeBaseStruct))
	TArray<FInstancedStruct> Tags;
};
