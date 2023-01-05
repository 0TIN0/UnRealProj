// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_FloorToAirAnimNotifyState.h"
#include "../WarriorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UUR_FloorToAirAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	if (m_Player->GetUltimateTarget().IsEmpty())
	{
		return;
	}

	FVector EndVec = FVector(0.0, 0.0, 1.0);
	EndVec *= 1800.f;

	for (auto& Target : m_Player->GetUltimateTarget())
	{
		Target->LaunchCharacter(EndVec, true, true);
		Target->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::HitAirLoop);
	}

	EndVec.Z += 400.f;

	m_Player->LaunchCharacter(EndVec, true, true);
}

void UUR_FloorToAirAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	for (auto& Target : m_Player->GetUltimateTarget())
	{
		Target->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::HitAirLoop);
	}
}

void UUR_FloorToAirAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}


	if (m_Player->GetActorLocation().Z - m_Player->GetIsPrevZ() >= 800.0)
	{
		for (auto& Target : m_Player->GetUltimateTarget())
		{
			Target->LaunchCharacter(FVector(), true, true);
			Target->GetCharacterMovement()->GravityScale = 0.f;
			Target->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::HitAirLoop);
		}
		m_Player->LaunchCharacter(FVector(), true, true);
		m_Player->GetCharacterMovement()->GravityScale = 0.f;
		m_Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::SkillRAttack);
		m_Player->UltimateAttack();
	}
}
