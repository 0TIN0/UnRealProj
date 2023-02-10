// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_MotionWarpingDash.h"
#include "../WarriorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UUR_MotionWarpingDash::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
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

	m_Player->TraceAttackMonster();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	//LatentInfo.ExecutionFunction = FName("Finished");
	//LatentInfo.Linkage = 0;
	//LatentInfo.UUID = 0;

	FVector Dir = m_TargetActor->GetActorLocation() - m_Player->GetActorLocation();
	Dir = Dir.GetSafeNormal();

	Dir.Z = 0.0;

	FVector EndPos = m_TargetActor->GetActorLocation() + Dir * 500.f;

	UKismetSystemLibrary::MoveComponentTo(m_Player->GetRootComponent(), EndPos, m_Player->GetActorRotation(),
		false, false, 0.1f, true, EMoveComponentAction::Type::Move, LatentInfo);
}

void UUR_MotionWarpingDash::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	m_TargetActor = m_Player->GetMotionWarpingActor();

	if (!m_TargetActor)
	{
		return;
	}

}

void UUR_MotionWarpingDash::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

void UUR_MotionWarpingDash::Finished()
{
}
