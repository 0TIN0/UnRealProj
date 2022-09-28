// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_CreateObjAnimNotifyState.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "../URProjectile.h"

void UUR_CreateObjAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	// ������ �÷��̿��尡 NULL�̶�� ����
	if (!UURBlueprintFunctionLibrary::GetCurrentPlayWorld())
	{
		return;
	}
	
	if (!m_SpawnActorClass && !m_SpawnActorClass->IsValidLowLevel())
	{
		return;
	}

	// ������ �̸������ͼ� �ش� ������ ��ġ���� ���´�.
	FVector Pos = MeshComp->GetSocketLocation(m_SocketName);

	FTransform SpawnTransform = FTransform(Pos);

	SpawnTransform.SetRotation(MeshComp->GetOwner()->GetTransform().GetRotation());

	// ���ο� ���͸� ������ش�.
	AActor* NewActor = MeshComp->GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);

	AURProjectile* Projectile = Cast<AURProjectile>(NewActor);

	// ���⼭ �̻����� �ɼ��� �����ϴ� ������ Ư�� ��Ÿ�ָ��� �̻����� ������ �ٸ��� �� �� �־�̴�.
	Projectile->SetInfo(m_CollisionProfileName, m_Speed, m_LifeTime);
}
