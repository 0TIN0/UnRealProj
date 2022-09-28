// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "URStaticMeshActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AURStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AURStaticMeshActor();

protected:
	virtual void BeginPlay() override;
	
};
