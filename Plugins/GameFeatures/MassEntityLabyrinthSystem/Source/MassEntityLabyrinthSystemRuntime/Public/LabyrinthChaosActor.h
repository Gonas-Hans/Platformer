// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Actor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollectionObject.h"
#include "LabyrinthChaosActor.generated.h"

UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ALabyrinthChaosActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALabyrinthChaosActor();

	
	// SetScale3D choice new mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap< FVector, TSoftObjectPtr<UGeometryCollection>> GeometryCollections;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ScaleChoiceRate{1, 1};
	
	UFUNCTION(BlueprintCallable)
	virtual void SetNewGeometryCollectionScale(FVector NewScale3D);
	
	virtual void AsyncLoadGeometryCollection(const TSoftObjectPtr<UGeometryCollection>* SoftObject);
	virtual void AsyncLoadObjectReviewFinished();
	
	UFUNCTION(BlueprintCallable)
	virtual void SetRestCollection(UGeometryCollection* GeometryCollection);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(Category=Mesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UGeometryCollectionComponent> GeometryCollectionComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	TSharedPtr<FStreamableHandle> ManagerHandle;

};
