// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/Sparrow/UR_SPCreateTargetFX.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "../../Boss/BossObj/UR_SparrowTargeting.h"

void UUR_SPCreateTargetFX::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Boss = MeshComp->GetOwner<AUR_SparrowSubBoss>();

	if (!m_Boss || !m_Boss->IsValidLowLevel())
	{
		return;
	}

	switch (m_Boss->GetRandAttackNumb())
	{
	case SparrowAttack_Type::Attack3:
	{
		// 소켓의 이름을얻어와서 해당 소켓의 위치값을 얻어온다.
		FVector Pos = MeshComp->GetSocketLocation(m_SocketName);
		Pos += m_Boss->GetActorForwardVector() * 350.f;
		FRotator Rot = m_Boss->GetActorRotation();
		Pos.Z += m_AddLocationZ;

		FTransform SpawnTransform = FTransform(Rot, Pos);

		AUR_SparrowTargeting* NewActor = MeshComp->GetWorld()->SpawnActorDeferred<AUR_SparrowTargeting>(AUR_SparrowTargeting::StaticClass(), SpawnTransform);

		NewActor->AttachToActor(m_Boss, FAttachmentTransformRules::KeepWorldTransform, m_SocketName);
		NewActor->FinishSpawning(SpawnTransform);
	}
		break;
	}
}

void UUR_SPCreateTargetFX::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UUR_SPCreateTargetFX::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
