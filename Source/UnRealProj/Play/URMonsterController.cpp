// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/URMonsterController.h"
#include "Play/Monster.h"
#include "Global/URStructs.h"
#include "BehaviorTree/BlackboardComponent.h"

void AURMonsterController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	AMonster* Monster = Cast<AMonster>(_Pawn);

	if (!Monster)
	{
		UE_LOG(LogTemp, Error, TEXT("Monster Cast Error"));
		return;
	}

	const struct FURMonsterDataInfo* Data = Monster->MonsterDataInit();

	Blackboard->SetValueAsFloat("FindRange", Data->FindRange);

	double Value = Blackboard->GetValueAsFloat("FindRange");
}
