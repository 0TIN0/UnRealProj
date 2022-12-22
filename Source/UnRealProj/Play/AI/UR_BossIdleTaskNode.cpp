// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossIdleTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Controller/URAIController.h"
#include "../Boss/UR_BossMonster.h"
#include "../Boss/UR_KrakenBoss.h"
#include "Global/URStructs.h"

UUR_BossIdleTaskNode::UUR_BossIdleTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossIdleTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AUR_BossMonster* Lich = Controller->GetPawn<AUR_BossMonster>();
	if (Lich)
	{
		const FURMonsterDataInfo* MonsterInfo = Lich->GetMonsterData();

		UAnimMontage* FindMontage = Lich->GetAnimationInstance()->GetAnimation(BossAnimation::Spawn);
		if (Lich->GetAnimationInstance()->Montage_IsPlaying(FindMontage))
		{
			return EBTNodeResult::Failed;
		}

		UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

		if (Target)
		{
			return EBTNodeResult::Failed;
		}

		Lich->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);

		return EBTNodeResult::InProgress;
	}
	else
	{
		AUR_KrakenBoss* Kraken = Controller->GetPawn<AUR_KrakenBoss>();

		if (Kraken)
		{
			UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

			if (Target)
			{
				return EBTNodeResult::Failed;
			}

			Kraken->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);

			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

void UUR_BossIdleTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
