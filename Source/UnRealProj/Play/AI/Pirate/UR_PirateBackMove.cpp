// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Pirate/UR_PirateBackMove.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UUR_PirateBackMove::UUR_PirateBackMove()	:
	m_Enable(false)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_PirateBackMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Controller->GetPawn<AMonster>();

	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();

	if (!AnimMontageJudge(Monster))
	{
		m_Enable = false;
		return EBTNodeResult::Failed;
	}

	if (Monster->GetUltimateHitEnable())
	{
		m_Enable = false;
		return EBTNodeResult::Failed;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		m_Enable = false;
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - Monster->GetActorLocation();

	if (!m_Enable)
	{
		if (Monster->GetTargetDir(TargetActor).Size() > 150.f)
		{
			Monster->ResetPath();
			m_Enable = false;
			return EBTNodeResult::Failed;
		}
		else
		{
			m_Enable = true;
		}
	}

	if (m_Enable)
	{
		if (Monster->GetCharacterMovement()->MaxWalkSpeed != 200)
		{
			Monster->GetCharacterMovement()->MaxWalkSpeed = 200.f;
		}

		if (Monster->GetTargetDir(TargetActor).Size() > MonsterInfo->AttRange)
		{
			Monster->ResetPath();
			m_Enable = false;
			return EBTNodeResult::Failed;
		}

		Monster->SetTargetLook(TargetActor);

		if (!Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::BlockLoop) &&
			!Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::BlockWalkBackward) &&
			!Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::IdleToBlock))
		{
			Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::IdleToBlock);
		}
		else
		{
			Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::BlockWalkBackward);
			Monster->SetDirMovementInput(-Monster->GetActorForwardVector());
		}
	}

	return EBTNodeResult::Type::InProgress;
}

void UUR_PirateBackMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_PirateBackMove::AnimMontageJudge(AMonster* _Monster)
{
	if (_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::Attack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorEnd) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathLoop))
	{
		return false;
	}

	return true;
}
