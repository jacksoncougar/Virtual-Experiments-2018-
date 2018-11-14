// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereAttachmentSlot.h"

USphereAttachmentSlot::USphereAttachmentSlot()
{ 
    //Tick
    PrimaryComponentTick.bCanEverTick = true;
}

USphereAttachmentSlot::~USphereAttachmentSlot()
{
    GetComponentTransform( );
}
