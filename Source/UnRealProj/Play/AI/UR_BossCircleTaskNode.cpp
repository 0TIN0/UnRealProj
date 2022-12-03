// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossCircleTaskNode.h"
#include "../Play/UR_BossMonster.h"
#include "Play/Controller/URAIController.h"
#include "../PlayCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UUR_BossCircleTaskNode::UUR_BossCircleTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossCircleTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_BossMonster>();

	UAnimMontage* FindMontage = m_Boss->GetAnimationInstance()->GetAnimation(BossAnimation::Spawn);
	if (m_Boss->GetAnimationInstance()->Montage_IsPlaying(FindMontage))
	{
		return EBTNodeResult::Failed;
	}

	const FURMonsterDataInfo* BossInfo = m_Boss->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	// 공격 범위보다 밖에 있다면 Idle로 변경한다.
	if (!m_Boss->GetIsRangeInTarget(TargetActor, BossInfo->FindRange))
	{
		return EBTNodeResult::Failed;
	}

	if (m_SkillCount >= 10)
	{
		return EBTNodeResult::Failed;
	}

	// 해당 스킬은 0번이여야지만 사용할 수 있음.
	/*if (m_Boss->GetRandNumb() != 0)
	{
		return EBTNodeResult::Failed;
	}*/

	FVector Pos = m_Boss->GetActorLocation();

	FTransform SpawnTransform = FTransform(Pos);

	TSubclassOf<AActor> SpawnActorClass = m_Boss->GetSpawnActorClass();

	// 새로운 엑터를 만들어준다.
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnTransform);

	m_Boss->GetAnimationInstance()->ChangeAnimMontage(BossAnimation::Skill2);

	++m_SkillCount;

	return EBTNodeResult::Succeeded;
}

void UUR_BossCircleTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_BossMonster>();
}
