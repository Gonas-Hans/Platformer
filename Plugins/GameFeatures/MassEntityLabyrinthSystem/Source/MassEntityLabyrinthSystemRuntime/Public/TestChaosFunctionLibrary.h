// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestGeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicsProxy/GeometryCollectionPhysicsProxy.h"
#include "TestChaosFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API UTestChaosFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void SetRestCollection(UGeometryCollection* GeometryCollection, UTestGeometryCollectionComponent* GeometryCollectionComponent)
	{
		if(GeometryCollection && GeometryCollectionComponent)
		{
			
			
			
			GeometryCollectionComponent->SetRestCollection(GeometryCollection);
			FGeometryCollectionEdit GeometryCollectionEdit =GeometryCollectionComponent->EditRestCollection(GeometryCollection::EEditUpdate::RestPhysicsDynamic);
			//GeometryCollectionComponent->RegisterAndInitializePhysicsProxy();
			//GeometryCollectionComponent->OnUpdateTransform(EUpdateTransformFlags::PropagateFromParent, ETeleportType::TeleportPhysics);
			
			if (GeometryCollectionComponent->IsRenderStateCreated())
			{
				GeometryCollectionComponent->MarkRenderStateDirty();
			}

			else if (GeometryCollectionComponent->ShouldCreateRenderState())
			{
				GeometryCollectionComponent->RecreateRenderState_Concurrent();
			}
			GeometryCollectionComponent->SetRenderStateDirty();
			//GeometryCollectionComponent->ReregisterComponent();
	
		
			
		}
	}

	UFUNCTION(BlueprintCallable)
	static void UpdateChaosTransform(UGeometryCollectionComponent* GeometryCollectionComponent, TArray<FTransform> NewTransform)
	{
		GeometryCollectionComponent->OnUpdateTransform(EUpdateTransformFlags::None,  ETeleportType::None);
	}

	UFUNCTION(BlueprintCallable)
	static void SetNewWorldGravity(float Gravity, AWorldSettings* WorldSetting)
	{
		WorldSetting->bGlobalGravitySet=true;
		WorldSetting->GlobalGravityZ = Gravity;
		
	}

	
	UFUNCTION(BlueprintCallable)
	static void GetActorWorld(AActor* Actor, UWorld*& World)
	{
		World = Actor->GetWorld();
		
	}

	UFUNCTION(BlueprintCallable)
	static void SpawnGeometryCollectionActor(TSubclassOf<AActor> ActorClass, UWorld* World, FTransform Transform, UGeometryCollection* GeoCollection)
	{
		AActor* Actor = World->SpawnActorDeferred<AActor>(ActorClass.Get(), Transform);
		if(Actor)
		{
			UGeometryCollectionComponent* GeoCollectionComp = Actor->FindComponentByClass<UGeometryCollectionComponent>();
			if(GeoCollectionComp && GeoCollection)
			{
				//GeoCollectionComp->SetRestCollection(GeoCollection);
			}
			else
			{
				FTransform Transform1{};
				UTestGeometryCollectionComponent* Geo_Comp = NewObject<UTestGeometryCollectionComponent>(Actor, UTestGeometryCollectionComponent::StaticClass(), FName("GeoCollection"));
				//Geo_Comp->UnregisterComponent();
				Geo_Comp->SetDynamicState(Chaos::EObjectStateType::Dynamic);
				//FGeometryCollectionEdit Edit  = Geo_Comp->EditRestCollection(GeometryCollection::EEditUpdate::Rest);
				//UGeometryCollection * RestCollection = Edit.GetRestCollection();
				//RestCollection = GeoCollection;
				Geo_Comp->EditRestCollection(GeometryCollection::EEditUpdate::Rest);
				Geo_Comp->SetRestCollection(GeoCollection);
				Geo_Comp->ResetGeoCollection();
				Geo_Comp->RegisterComponent();
				Geo_Comp->MarkRenderStateDirty();
				Actor->AddComponent(FName("GeometryCollection"), false, Transform1, Geo_Comp);
				
				
			}
			Actor->FinishSpawning(Transform);
			Actor->SetActorLocation(Transform.GetLocation());
			
		}
	}

	UFUNCTION(BlueprintCallable)
static void AddGeometryCollectionComponent(AActor* Actor, UGeometryCollection* GeoCollection)
	{
		FTransform Transform1 = Actor->GetActorTransform();
		UTestGeometryCollectionComponent* Geo_Comp = NewObject<UTestGeometryCollectionComponent>(Actor, UTestGeometryCollectionComponent::StaticClass(), FName("GeoCollection"));
		Geo_Comp->SetDynamicState(Chaos::EObjectStateType::Dynamic);
		Geo_Comp->EditRestCollection(GeometryCollection::EEditUpdate::Rest);
		Geo_Comp->SetRestCollection(GeoCollection);
		Geo_Comp->ResetGeoCollection();
		UActorComponent* NewComp = Actor->AddComponent(FName("GeometryCollection"), false,  Transform1, Geo_Comp);
		Geo_Comp->RegisterComponent();
		Geo_Comp->MarkRenderStateDirty();
		Actor->SetActorTransform(Transform1);
	}

	UFUNCTION(BlueprintCallable)
static void ReregisterPhysics(UGeometryCollectionComponent* GeoCollection)
	{
		// РАБОТАЕТ!!!!!!!!!!!!!!!!!!
		GeoCollection->OnUpdateTransform(EUpdateTransformFlags::PropagateFromParent, ETeleportType::TeleportPhysics);
		//GeoCollection->GetPhysicsProxy()->PushToPhysicsState();
	}
	

};
