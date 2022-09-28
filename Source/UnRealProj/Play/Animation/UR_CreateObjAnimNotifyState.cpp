// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_CreateObjAnimNotifyState.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "../URProjectile.h"

void UUR_CreateObjAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	// 현재의 플레이월드가 NULL이라면 리턴
	if (!UURBlueprintFunctionLibrary::GetCurrentPlayWorld())
	{
		return;
	}
	
	if (!m_SpawnActorClass && !m_SpawnActorClass->IsValidLowLevel())
	{
		return;
	}

	// 소켓의 이름을얻어와서 해당 소켓의 위치값을 얻어온다.
	FVector Pos = MeshComp->GetSocketLocation(m_SocketName);

	FTransform SpawnTransform = FTransform(Pos);

	SpawnTransform.SetRotation(MeshComp->GetOwner()->GetTransform().GetRotation());

	// 새로운 엑터를 만들어준다.
	AActor* NewActor = MeshComp->GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);

	AURProjectile* Projectile = Cast<AURProjectile>(NewActor);

	// 여기서 미사일의 옵션을 설정하는 이유는 특정 몽타주마다 미사일의 설정을 다르게 할 수 있어서이다.
	Projectile->SetInfo(m_CollisionProfileName, m_Speed, m_LifeTime);
}
