// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraspableInterface.h"
#include "GraspableRegion.h"
#include "GraspableActor.generated.h"

/**
 * An actor which can be grasped by a hand at regions defined by child GraspableRegion components.
 */
UCLASS()
class MYPROJECT3_API AGraspableActor : public AActor, public IGraspableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraspableActor();       

    // Gets all the graspable regions on this actor.
    UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "Graspable Interface" )
    TArray<UGraspableRegion*> GetGraspableRegions( ) const;
    TArray<UGraspableRegion*> GetGraspableRegions_Implementation( ) const;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Graspable Interface" )
    TArray<UGraspableRegion*> GraspableRegions;

    virtual UGraspableRegion* FindGraspableRegionNearestTo_Implementation( const FHandInformation hand, FGripHint& outHint, float distance = 10 ) const override;

    UFUNCTION( BlueprintCallable, Category = "Graspable Interface" )
    bool IsGrasped( ) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
