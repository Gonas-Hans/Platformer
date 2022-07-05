// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFeatureAction_AddSpawnedActors.h"

#include "EngineUtils.h"
#include "Engine/AssetManager.h"
#include "GameFeaturesSubsystemSettings.h"

#define LOCTEXT_NAMESPACE "AncientGameFeatures"


//////////////////////////////////////////////////////////////////////
// UGameFeatureAction_AddWorldSystem

void UGameFeatureAction_AddSpawnedActors::OnGameFeatureActivating()
{
	//GameInstanceStartHandle = FWorldDelegates::OnStartGameInstance.AddUObject(this, &UGameFeatureAction_WorldActionBase::HandleGameInstanceStart);

	// Add to any worlds with associated game instances that have already been initialized
	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
	{
		AddActorsToWorld(WorldContext);
	}
}


void UGameFeatureAction_AddSpawnedActors::OnGameFeatureDeactivating(FGameFeatureDeactivatingContext& Context)
{
	FWorldDelegates::OnStartGameInstance.Remove(GameInstanceStartHandle);
	Reset();
}

#if WITH_EDITORONLY_DATA
void UGameFeatureAction_AddSpawnedActors::AddAdditionalAssetBundleData(FAssetBundleData& AssetBundleData)
{
	if (UAssetManager::IsValid())
	{
		for (const FSpawningWorldActorsEntry& Entry : ActorsList)
		{
			for (const FSpawningActorEntry& ActorEntry : Entry.Actors)
			{
				AssetBundleData.AddBundleAsset(UGameFeaturesSubsystemSettings::LoadStateClient, ActorEntry.ActorType->GetPathName());
				AssetBundleData.AddBundleAsset(UGameFeaturesSubsystemSettings::LoadStateServer, ActorEntry.ActorType->GetPathName());
			}
		}
	}
}
#endif

#if WITH_EDITOR
EDataValidationResult UGameFeatureAction_AddSpawnedActors::IsDataValid(TArray<FText>& ValidationErrors)
{
	EDataValidationResult Result = CombineDataValidationResults(Super::IsDataValid(ValidationErrors), EDataValidationResult::Valid);

	int32 EntryIndex = 0;
	for (const FSpawningWorldActorsEntry& Entry : ActorsList)
	{
		int32 ActorIndex = 0;
		for (const FSpawningActorEntry& ActorEntry : Entry.Actors)
		{
			if (ActorEntry.ActorType == nullptr)
			{
				ValidationErrors.Add(FText::Format(LOCTEXT("NullSpawnedActorType", "Null ActorType for actor #{0} at index {1} in ActorsList."), FText::AsNumber(ActorIndex), FText::AsNumber(EntryIndex)));
			}
			++ActorIndex;
		}
		++EntryIndex;
	}

	return Result;
}

#endif

void UGameFeatureAction_AddSpawnedActors::AddActorsToWorld(const FWorldContext& WorldContext)
{
	UWorld* World = WorldContext.World();

	if ((World != nullptr) && World->IsGameWorld())
	{
		for (const FSpawningWorldActorsEntry& Entry : ActorsList)
		{
			if (!Entry.TargetWorld.IsNull())
			{
				UWorld* TargetWorld = Entry.TargetWorld.Get();
				if (TargetWorld != World)
				{
					// This system is intended for a specific world (not this one)
					continue;
				}
			}
			for (const FSpawningActorEntry& ActorEntry : Entry.Actors)
			{
				FTransform SpawningTransform{};
				if(ActorEntry.bUseTargetPoint)
				{
					for (TActorIterator<ATargetPoint> ActorItr(World); ActorItr; ++ActorItr)
					{
						if(ActorItr->GetClass() == ActorEntry.TargetPoint)
						{
							for (auto ActorTag : ActorItr->Tags)
							{
								if(ActorTag == ActorEntry.TargetPointActorTag)  SpawningTransform = ActorItr->GetActorTransform();
							}
						}
					}
				}
				else  SpawningTransform = ActorEntry.SpawnTransform;
				
				AActor* NewActor = World->SpawnActor<AActor>(ActorEntry.ActorType, SpawningTransform);
				SpawnedActors.Add(NewActor);
			}
		}
	}
}


void UGameFeatureAction_AddSpawnedActors::Reset()
{
	for (TWeakObjectPtr<AActor>& ActorPtr : SpawnedActors)
	{
		if (ActorPtr.IsValid())
		{
			ActorPtr->Destroy();
		}
	}
}

#undef LOCTEXT_NAMESPACE