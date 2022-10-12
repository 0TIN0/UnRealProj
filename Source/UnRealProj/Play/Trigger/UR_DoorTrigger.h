// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "UR_DoorTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_DoorTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	AUR_DoorTrigger();
	
protected:
	virtual void BeginPlay();
};
