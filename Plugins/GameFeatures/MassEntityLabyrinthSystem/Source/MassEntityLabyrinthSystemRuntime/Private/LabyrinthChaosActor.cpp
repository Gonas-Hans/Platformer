// Fill out your copyright notice in the Description page of Project Settings.


#include "LabyrinthChaosActor.h"

#include "ObjectCacheEventSink.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

// Sets default values
ALabyrinthChaosActor::ALabyrinthChaosActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GeometryCollectionComponent= CreateDefaultSubobject<UGeometryCollectionComponent>(FName("GC_Mesh"));

}

void ALabyrinthChaosActor::SetNewGeometryCollectionScale(const FVector NewScale3D)
{
	float Scale_X = FMath::RoundHalfToZero(10.0 * NewScale3D.X);
	float Scale_Y = FMath::RoundHalfToZero(10.0 * NewScale3D.Y);
	float Scale_Z = FMath::RoundHalfToZero(10.0 * NewScale3D.Z);

	const auto Value = GeometryCollections.Find(NewScale3D);
	if(Value)
	{
		AsyncLoadGeometryCollection(Value);
	}
	else if(auto GeometryCollection = Value->Get()) GeometryCollectionComponent->RestCollection = GeometryCollection;
	else UE_LOG(LogTemp,Warning,TEXT("NewScale doesnt supported in this object The TMap named GeometryCollections doesnt contain vector:  X: %d, Y: %d, Z: %d"), NewScale3D.X, NewScale3D.Y, NewScale3D.Z);
}

void ALabyrinthChaosActor::AsyncLoadGeometryCollection(const TSoftObjectPtr<UGeometryCollection>* SoftObject)
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	UAssetManager::Get().GetStreamableManager().Unload(SoftObject->ToSoftObjectPath());
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ManagerHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(SoftObject->ToSoftObjectPath());
	const FStreamableDelegate DelegateFinished = FStreamableDelegate::CreateUObject(this,&ALabyrinthChaosActor::AsyncLoadObjectReviewFinished);
	ManagerHandle->BindCompleteDelegate(DelegateFinished);
}

void ALabyrinthChaosActor::AsyncLoadObjectReviewFinished()
{
	TArray<UObject*> ObjectArray;
	ManagerHandle->GetLoadedAssets(ObjectArray);
	if(ObjectArray.Num()>0)
	{
		for(auto const& Object:ObjectArray)
		{
			UE_LOG(LogTemp,Warning,TEXT("Load Object %s"),*Object->GetName());
			UGeometryCollection* GeometryCollection = Cast<UGeometryCollection>(Object);
			if(GeometryCollection)
			{
				SetRestCollection(GeometryCollection);
				
			}
		}
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("Can't Load Object"));
	}
}

void ALabyrinthChaosActor::SetRestCollection(UGeometryCollection* GeometryCollection)
{
	if(GeometryCollection && GeometryCollectionComponent)
	{
		GeometryCollectionComponent->SetRestCollection(GeometryCollection);
		//GeometryCollectionComponent->SetDynamicState(Chaos::EObjectStateType::Dynamic);
		//GeometryCollectionComponent->RefreshEmbeddedGeometry();
		
		if (GeometryCollectionComponent->IsRenderStateCreated())
		{
			GeometryCollectionComponent->MarkRenderStateDirty();
		}

		else if (GeometryCollectionComponent->ShouldCreateRenderState())
		{
			GeometryCollectionComponent->RecreateRenderState_Concurrent();
		}
		GeometryCollectionComponent->SetRenderStateDirty();
		//GeometryCollectionComponent->RecreatePhysicsState();
		
		//GeometryCollectionComponent->SetShouldUpdatePhysicsVolume(true);
		//GeometryCollectionComponent->UpdatePhysicsVolume(true);
		//GeometryCollectionComponent->UpdateCollisionProfile();
		
		//GeometryCollectionComponent->ConditionalUpdateComponentToWorld();
	
		
		//IStreamingManager::Get().NotifyPrimitiveUpdated(GeometryCollectionComponent);
		//GeometryCollectionComponent->UpdateBounds();

		
	}
	
	
}


// Called when the game starts or when spawned
void ALabyrinthChaosActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALabyrinthChaosActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ManagerHandle.IsValid())
	{
		
		ManagerHandle->ReleaseHandle();
	}
}

// Called every frame
void ALabyrinthChaosActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

