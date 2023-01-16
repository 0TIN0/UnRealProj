// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/Khaimera/UR_KhaimeraDashAnimNotifyState.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "../../WarriorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UUR_KhaimeraDashAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Khaimera = MeshComp->GetOwner<AUR_KhaimeraBoss>();

	if (!m_Khaimera || !m_Khaimera->IsValidLowLevel())
	{
		return;
	}

	m_TargetActor = m_Khaimera->GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();

	if (!m_TargetActor)
	{
		return;
	}

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("Finished");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;

	FVector TargetPos = m_TargetActor->GetActorLocation();
	TargetPos.Z = m_Khaimera->GetActorLocation().Z;
	FVector Dir = TargetPos - m_Khaimera->GetActorLocation();
	Dir = Dir.GetSafeNormal();

	FVector EndPos = TargetPos - Dir * 250.f;

	UKismetSystemLibrary::MoveComponentTo(m_Khaimera->GetRootComponent(), EndPos, m_Khaimera->GetActorRotation(),
		false, false, 0.63f, true, EMoveComponentAction::Type::Move, LatentInfo);
}

void UUR_KhaimeraDashAnimNotifyState::Finished()
{
}
