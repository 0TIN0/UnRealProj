// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Controller/UR_BossController.h"
#include "../UR_BossMonster.h"
#include "Global/URStructs.h"
#include "BehaviorTree/BlackboardComponent.h"

void AUR_BossController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	AUR_BossMonster* Boss = Cast< AUR_BossMonster>(_Pawn);

	if (!Boss)
	{
		UE_LOG(LogTemp, Error, TEXT("Boss Cast Error"));
		return;
	}

	const struct FURMonsterDataInfo* Data = Boss->BossDataInit();

	Blackboard->SetValueAsFloat("FindRange", Data->FindRange);

	double Value = Blackboard->GetValueAsFloat("FindRange");
}
