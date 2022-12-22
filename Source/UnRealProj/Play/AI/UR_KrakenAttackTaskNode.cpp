// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_KrakenAttackTaskNode.h"
#include "../Play/Boss/UR_KrakenBoss.h"
#include "Play/Controller/URAIController.h"
#include "../PlayCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UUR_KrakenAttackTaskNode::UUR_KrakenAttackTaskNode()
{
	// TickTask�Լ��� ���۽�ų�� �������� ����
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KrakenAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KrakenBoss>();

	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetKrakenData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	UAnimMontage* Montage = m_Boss->GetAnimationInstance()->GetAnimation(DefaultAnimation::Attack);

	// ���� �������� �ۿ� �ִٸ� Idle�� �����Ѵ�.
	if (!m_Boss->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange) && !m_Boss->GetAnimationInstance()->Montage_IsPlaying(Montage))
	{
		return EBTNodeResult::Failed;
	}

	if (!Montage)
	{
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
		return EBTNodeResult::Failed;
	}

	m_WaitTime = Montage->GetPlayLength();


	int RandomSelect = m_Stream.RandRange(0, 3);

	switch (RandomSelect)
	{
	case 0:
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
		break;
	case 1:
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(KrakenBossAnimation::FowardAttack2);
		break;
	case 2:
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(KrakenBossAnimation::FowardComboAttack);
		break;
	}


	return EBTNodeResult::InProgress;
}

void UUR_KrakenAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KrakenBoss>();

	APlayCharacter* Player = Cast<APlayCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Waittime���� �� ��Ÿ���� ���̰� ���ְ�
	m_WaitTime -= DeltaSeconds;

	if (0.0f < m_WaitTime)
	{
		return;
	}

	// �׸�ŭ ��ٷȴٴ� �̾߱Ⱑ �˴ϴ�.
	m_WaitTime = 0.0f;


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
