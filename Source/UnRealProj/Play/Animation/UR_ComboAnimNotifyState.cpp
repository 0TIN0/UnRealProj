// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_ComboAnimNotifyState.h"
#include "Kismet/GameplayStatics.h"

UUR_ComboAnimNotifyState::UUR_ComboAnimNotifyState()	:
	m_ComboChangeAnimation(WarriorAnimation::Default),
	m_Player(nullptr),
	m_IsComboAttack(false)
{
}

void UUR_ComboAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	m_Player->AttackOn();

	m_IsComboAttack = false;
	m_Player->SetIsCombating(true);
	m_Player->SetIsComboAttack(false);
}

void UUR_ComboAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (m_Player)
	{
		// NotifyTick이 돌아가는동안 좌클릭이 한 번이라도 더 눌렸는지 판단을 하기 위해서이다
		if (m_Player->GetIsComboAttack())
		{
			m_IsComboAttack = true;
		}
	}
}

void UUR_ComboAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (m_Player)
	{
		// 중간에 콤보동작을 하려고 공격을 눌렀다는 의미이다.
		// 그래서 NotifyEnd일떄 다음 콤보 동작을 시켜주면 됨.
		if (m_IsComboAttack && m_ComboChangeAnimation != WarriorAnimation::Default)
		{
			m_Player->GetAnimationInstance()->ChangeAnimMontage(m_ComboChangeAnimation);
		}

		//m_Player->AttackOff();
	}
}
