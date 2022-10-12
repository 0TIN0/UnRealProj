// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/URItemActor.h"
#include "Global/URStructs.h"
#include "Components/SphereComponent.h"

AURItemActor::AURItemActor()
{
}

void AURItemActor::SetItem(const FURItemData* _ItemData)
{
	if (!_ItemData)
	{
		return;
	}

	if (nullptr == _ItemData->DropMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Drop Item Mesh Is nullptr!"), *_ItemData->DisplayName.ToString());
		return;
	}

	GetStaticMeshComponent()->SetStaticMesh(_ItemData->DropMesh);
}

void AURItemActor::BeginPlay()
{
	Super::BeginPlay();

	GetSphereComponent()->SetCollisionProfileName(FName(TEXT("Item")));
}

void AURItemActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Destroy();
}
