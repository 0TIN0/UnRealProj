// Fill out your copyright notice in the Description page of Project Settings.


#include "URStaticMeshActor.h"
#include "Components/StaticMeshComponent.h"

AURStaticMeshActor::AURStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AURStaticMeshActor::BeginPlay()
{
	TArray<UActorComponent*> Array = GetComponentsByClass(UMeshComponent::StaticClass());

	for (size_t i = 0; i < Array.Num(); ++i)
	{
		UMeshComponent* Com = Cast<UMeshComponent>(Array[i]);

		if (!Com)
		{
			return;
		}

		Com->bHiddenInSceneCapture = true;
	}
}
