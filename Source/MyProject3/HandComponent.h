// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "HandComponent.generated.h"

class UGraspableRegion;

// Can be used to hold graspable objects
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT3_API UHandComponent : public UPrimitiveComponent
{
    GENERATED_UCLASS_BODY()

public:	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    // Attempts to grab the given region and attach it to this component
    UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Hand" )
        bool Grab( UGraspableRegion* region );

    // Attempts to drop the given region and remove it from this component
    UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Hand" )
        bool Release( UGraspableRegion* region );
};