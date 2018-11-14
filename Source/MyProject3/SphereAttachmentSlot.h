// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Components/SphereComponent.h"
#include "SphereAttachmentSlot.generated.h"


UCLASS(Blueprintable, ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class USphereAttachmentSlot : public USphereComponent
{
    GENERATED_BODY()

public:
    USphereAttachmentSlot();
	~USphereAttachmentSlot();
};
