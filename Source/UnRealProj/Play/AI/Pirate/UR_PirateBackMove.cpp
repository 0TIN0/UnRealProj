// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Pirate/UR_PirateBackMove.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UUR_PirateBackMove::UUR_PirateBackMove()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_PirateBackMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Controller->GetPawn<AMonster>();

	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();

	if (Monster->IsDeath())
	{
		return EBTNodeResult::Failed;
	}

	if (!AnimMontageJudge(Monster))
	{
		return EBTNodeResult::Failed;
	}

	if (Monster->GetUltimateHitEnable())
	{
		return EBTNodeResult::Failed;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - Monster->GetActorLocation();

	if (!Monster->GetAIStruct().IsBackMove)
	{
		if (Monster->GetTargetDir(TargetActor).Size() > 150.f)
		{
			Monster->ResetPath();
			Monster->SetAIIsAttack(false);
			return EBTNodeResult::Failed;
		}
		else
		{
			Monster->SetAIIsAttack(true);
		}
	}

	if (Monster->GetAIStruct().IsBackMove)
	{
		if (Monster->GetTargetDir(TargetActor).Size() > MonsterInfo->AttRange)
		{
			Monster->ResetPath();
			Monster->SetAIIsAttack(false);
			if (Monster->GetIsBlocking())
				Monster->SetIsBlocking(false);
			return EBTNodeResult::Failed;
		}

		Monster->SetTargetLook(TargetActor);

		// 몬스터가 블로킹중이 아니라면 블로킹중으로 변경했다 알려주어야함.
		if (!Monster->GetIsBlocking())
			Monster->SetIsBlocking(true);

		if (!Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::BlockLoop) &&
			!Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::BlockWalkBackward) &&
			!Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::IdleToBlock))
		{
			Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::IdleToBlock);
			if (Monster->GetCharacterMovement()->MaxWalkSpeed != 0.f)
			{
				Monster->GetCharacterMovement()->MaxWalkSpeed = 0.f;
			}
		}
		else
		{
			Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::BlockWalkBackward);
			Monster->SetDirMovementInput(-Monster->GetActorForwardVector());
			if (Monster->GetCharacterMovement()->MaxWalkSpeed != 200)
			{
				Monster->GetCharacterMovement()->MaxWalkSpeed = 200.f;
			}
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
