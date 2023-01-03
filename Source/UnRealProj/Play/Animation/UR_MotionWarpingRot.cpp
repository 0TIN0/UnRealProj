// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_MotionWarpingRot.h"
#include "../WarriorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UUR_MotionWarpingRot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	m_TargetActor = m_Player->GetMotionWarpingActor();

	if (!m_TargetActor)
	{
		return;
	}

	if (!m_Player->GetIsQSkill())
	{
		return;
	}
}

void UUR_MotionWarpingRot::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
}

void UUR_MotionWarpingRot::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!m_Player)
		m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel() || !m_Player->GetIsQSkill())
	{
		return;
	}

	if (!m_TargetActor)
	{
		return;
	}

	FVector Dir = m_TargetActor->GetActorLocation() - m_Player->GetActorLocation();
	Dir = Dir.GetSafeNormal();

	FRotator PlayerRot = Dir.Rotation();

	m_Player->GetController()->SetControlRotation(PlayerRot);

}
