// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Controller/UR_KhaimeraBossController.h"
#include "../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"
#include "BehaviorTree/BlackboardComponent.h"

void AUR_KhaimeraBossController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);

	AUR_KhaimeraBoss* Boss = Cast< AUR_KhaimeraBoss>(_Pawn);

	if (!Boss)
	{
		UE_LOG(LogTemp, Error, TEXT("KhaimeraBoss Cast Error"));
		return;
	}

	const struct FURMonsterDataInfo* Data = Boss->BossDataInit();

	Blackboard->SetValueAsFloat("FindRange", Data->FindRange);

	double Value = Blackboard->GetValueAsFloat("FindRange");
}
