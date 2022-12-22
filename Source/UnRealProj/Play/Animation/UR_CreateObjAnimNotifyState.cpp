// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_CreateObjAnimNotifyState.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "../Skill/URProjectile.h"
#include "../Monster.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	switch (m_ActorType)
	{
	case ActorType::Normal:
	{
		TArray<AMonster*> ArrayActors;
		AURCharacter* Player = MeshComp->GetOwner<AURCharacter>();
		
		UWorld* World = Player->GetWorld();
		TActorIterator<AMonster> iter(World);

		for (; iter; ++iter)
		{
			AActor* Actor = *iter;
			double Dist = Player->GetTargetDir(Actor).Size();

			if (Dist < 1000.0)
			{
				ArrayActors.Push((AMonster*)Actor);
			}
		}

		for (auto iter1 : ArrayActors)
		{
			FVector Pos = iter1->GetActorLocation();

			FTransform SpawnTransform = FTransform(Pos);

			// 새로운 엑터를 만들어준다.
			AActor* NewActor = MeshComp->GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);
		}


	}
		break;
	case ActorType::Projectile:
	{
		// 소켓의 이름을얻어와서 해당 소켓의 위치값을 얻어온다.
		FVector Pos = MeshComp->GetSocketLocation(m_SocketName);
		Pos.Z += m_AddLocationZ;

		FTransform SpawnTransform = FTransform(Pos);

		SpawnTransform.SetRotation(MeshComp->GetOwner()->GetTransform().GetRotation());

		// 새로운 엑터를 만들어준다.
		AActor* NewActor = MeshComp->GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);

		AURProjectile* Projectile = Cast<AURProjectile>(NewActor);

		if (!Projectile)
			return;

		// 여기서 미사일의 옵션을 설정하는 이유는 특정 몽타주마다 미사일의 설정을 다르게 할 수 있어서이다.
		Projectile->SetInfo(m_CollisionProfileName, m_Speed, m_LifeTime);
	}
		break;
	}
	
}
