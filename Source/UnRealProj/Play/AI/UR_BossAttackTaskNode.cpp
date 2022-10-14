// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossAttackTaskNode.h"
#include "../Play/UR_BossMonster.h"
#include "Play/Controller/URAIController.h"
#include "../PlayCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UUR_BossAttackTaskNode::UUR_BossAttackTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if(!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_BossMonster>();

	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	// 공격 범위보다 밖에 있다면 Idle로 변경한다.
	if (!m_Boss->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange))
	{
		return EBTNodeResult::Failed;
	}

	UAnimMontage* Montage = m_Boss->GetAnimationInstance()->GetAnimation(DefaultAnimation::Attack);

	if (!Montage)
	{
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
		return EBTNodeResult::Failed;
	}

	m_WaitTime = Montage->GetPlayLength();

	m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);

	return EBTNodeResult::Type();
}

void UUR_BossAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_BossMonster>();

	APlayCharacter* Player = Cast<APlayCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Waittime에는 이 몽타주의 길이가 들어가있고
	m_WaitTime -= DeltaSeconds;

	if (0.0f < m_WaitTime)
	{
		return;
	}

	// 그만큼 기다렸다는 이야기가 됩니다.
	m_WaitTime = 0.0f;


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
