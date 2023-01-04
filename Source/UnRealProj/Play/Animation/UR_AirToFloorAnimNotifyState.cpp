// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_AirToFloorAnimNotifyState.h"
#include "../WarriorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UUR_AirToFloorAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}
}

void UUR_AirToFloorAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UUR_AirToFloorAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	for (auto& Target : m_Player->GetUltimateTarget())
	{
		if (Target)
		{
			Target->GetCharacterMovement()->GravityScale = 2.f;
			Target->SetHitType(EHitType::KnockDownHit);
			Target->CallDamage(m_Player->GetPlayerInfo()->MaxAttack, m_Player);
		}
	}

	m_Player->GetCharacterMovement()->GravityScale = 2.f;
	m_Player->AttackOff();
	m_Player->SetIsUltimateAttack(false);

	if (!m_Player->GetIsCombating())
	{
		m_Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}
	else
	{
		m_Player->GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
	}

}