// Fill out your copyright notice in the Description page of Project Settings.



#include "Traits/AssortedTags.h"
#include "MassEntityTemplateRegistry.h"

void UAssortedTags::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, UWorld& World) const
{
	for (auto& Tag : Tags)
	{
		const UScriptStruct* TagStruct = Tag.GetScriptStruct();

		if (TagStruct)
		{
			if(TagStruct->IsChildOf(FMassTag::StaticStruct()))
			{
				BuildContext.AddTag(*TagStruct);
			}
		}
	}
}
