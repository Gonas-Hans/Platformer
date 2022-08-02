// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "MassLabyrinthGenerator.h"
#include "MassSpawner.h"

#include "LabyrinthSystemActor.generated.h"

UCLASS()
class MASSENTITYLABYRINTHSYSTEMRUNTIME_API ALabyrinthSystemActor : public AMassSpawner, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALabyrinthSystemActor();

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override { TagContainer = GameplayTagContainer;}

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer GameplayTagContainer{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMassLabyrinthGenerator* LabyrinthGenerator;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FMassSpawnDataGenerator>& GetSpawnGenerators(){return SpawnDataGenerators;};

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE int32 GetSpawnedEntitiesCount() const {return AllSpawnedEntities.Num();}

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	
};
