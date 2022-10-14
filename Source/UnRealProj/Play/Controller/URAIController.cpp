// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Controller/URAIController.h"
#include "UnRealProj/Play/URAICharacter.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

void AURAIController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	AURAICharacter* AICharacter = Cast<AURAICharacter>(_Pawn);

	if (!AICharacter || !AICharacter->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("AICharacter Nullptr"));
		return;
	}

	if (!AICharacter->GetBlackBoardData() ||
		!AICharacter->GetBlackBoardData()->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("GetBlackBoardData Nullptr"));
		return;
	}

	if (!AICharacter->GetBehaviorTree() ||
		!AICharacter->GetBehaviorTree()->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("GetBehaviorTree Nullptr"));
		return;
	}

	UBlackboardComponent* BlackBoardComponent = GetBlackboardComponent();
	UseBlackboard(AICharacter->GetBlackBoardData(), BlackBoardComponent);
	RunBehaviorTree(AICharacter->GetBehaviorTree());
}
