// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Controller/UR_KrakenBossController.h"
#include "../Boss/UR_KrakenBoss.h"
#include "Global/URStructs.h"
#include "BehaviorTree/BlackboardComponent.h"

void AUR_KrakenBossController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	AUR_KrakenBoss* Boss = Cast< AUR_KrakenBoss>(_Pawn);

	if (!Boss)
	{
		UE_LOG(LogTemp, Error, TEXT("KrakenBoss Cast Error"));
		return;
	}

	const struct FURMonsterDataInfo* Data = Boss->BossDataInit();

	Blackboard->SetValueAsFloat("FindRange", Data->FindRange);

	double Value = Blackboard->GetValueAsFloat("FindRange");
}

