// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URStaticMeshActor.h"
#include "URItemActor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AURItemActor : public AURStaticMeshActor
{
	GENERATED_BODY()

	AURItemActor();

private:
	const struct FURItemData* m_ItemData;

public:
	void SetItem(const struct FURItemData* _ItemData);

	FORCEINLINE const struct FURItemData* GetItem()
	{
		return m_ItemData;
	}
	
protected:
	virtual void BeginPlay() override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
