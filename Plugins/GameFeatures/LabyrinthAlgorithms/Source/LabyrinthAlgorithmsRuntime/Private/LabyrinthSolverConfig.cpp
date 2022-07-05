
#include "LabyrinthSolverConfig.h"



void ULabyrinthSolverConfig::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = (PropertyChangedEvent.Property) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	
	OnLabyrinthSettingsChangedDelegate.Broadcast(PropertyName);
}


