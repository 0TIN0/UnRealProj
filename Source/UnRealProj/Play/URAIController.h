// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "URAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AURAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	void OnPossess(APawn* _Pawn) override;

private:
	UBehaviorTree* m_BehaviorTree;
	UBlackboardData* m_BlackBoardData;
};
