// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Controller/UR_SparrowBossController.h"
#include "../Boss/UR_SparrowSubBoss.h"
#include "Global/URStructs.h"
#include "BehaviorTree/BlackboardComponent.h"

void AUR_SparrowBossController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	AUR_SparrowSubBoss* Boss = Cast<AUR_SparrowSubBoss>(_Pawn);

	if (!Boss)
	{
		UE_LOG(LogTemp, Error, TEXT("SparrowBoss Cast Error"));
		return;
	}

	const struct FURMonsterDataInfo* Data = Boss->BossDataInit();

	Blackboard->SetValueAsFloat("FindRange", Data->FindRange);

	double Value = Blackboard->GetValueAsFloat("FindRange");
}

