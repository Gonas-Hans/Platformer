#pragma once

#include "MassEntityTypes.h"
#include "LabyrinthMassTags.generated.h"


// Base tag for notify custom mass processors work with Hierarchical instanced static mesh
USTRUCT()
struct  FHismTag : public FMassTag
{
	GENERATED_BODY()
};