// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_MoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

UUR_MoveTaskNode::UUR_MoveTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_MoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();
	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();
	//Monster->GetCharacterMovement()->MaxWalkSpeed = 2000.f;

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
		return EBTNodeResult::Succeeded;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - Monster->GetActorLocation();

	if (Monster->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
	{
		Monster->ResetPath();
		return EBTNodeResult::Failed;
	}
	if (nullptr != Monster->GetPath())
	{
		if (false == Monster->PathMove())
		{
			Monster->ResetPath();
			return EBTNodeResult::InProgress;
		}

		if (100.0f <= Monster->GetLastPathPointToTargetDis(TargetActor->GetActorLocation()))
		{
			Monster->ResetPath();
			return EBTNodeResult::InProgress;
		}
	}

	UNavigationPath* FindPath = Monster->PathFind(TargetActor);


	if (nullptr != FindPath && false == FindPath->PathPoints.IsEmpty())
	{
		Monster->SetPath(FindPath, false);
		Monster->PathMove();
		return EBTNodeResult::InProgress;
	}

	Monster->SetTargetLook(TargetActor);
	Monster->SetTargetMovementInput(TargetActor);
	Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


	return EBTNodeResult::Type::InProgress;
}

void UUR_MoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_MoveTaskNode::AnimMontageJudge(AMonster* _Monster)
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
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorEnd))
	{
		return false;
	}

	return true;
}
