// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/URItemActor.h"
#include "Global/URStructs.h"
#include "Global/URGameInstance.h"
#include "Components/SphereComponent.h"
#include "UI/UR_InventoryUI.h"

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

	m_ItemData = _ItemData;
}

void AURItemActor::BeginPlay()
{
	Super::BeginPlay();

	GetSphereComponent()->SetCollisionProfileName(FName(TEXT("Item")));
}

void AURItemActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	UURGameInstance* Inst = GetWorld()->GetGameInstance<UURGameInstance>();

	if (!Inst || !Inst->IsValidLowLevel())
	{
		return;
	}

	if (Inst->GetInven()->IsFull(m_ItemData))
	{
		return;
	}

	Inst->GetInven()->AddItem(m_ItemData);

	Destroy();
}
