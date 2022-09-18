// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UR_TargetSearchService.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_TargetSearchService : public UBTService
{
	GENERATED_BODY()
	
public:
	UUR_TargetSearchService();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
