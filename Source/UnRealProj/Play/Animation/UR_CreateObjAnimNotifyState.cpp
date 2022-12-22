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
	// ������ �÷��̿��尡 NULL�̶�� ����
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

			// ���ο� ���͸� ������ش�.
			AActor* NewActor = MeshComp->GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);
		}


	}
		break;
	case ActorType::Projectile:
	{
		// ������ �̸������ͼ� �ش� ������ ��ġ���� ���´�.
		FVector Pos = MeshComp->GetSocketLocation(m_SocketName);
		Pos.Z += m_AddLocationZ;

		FTransform SpawnTransform = FTransform(Pos);

		SpawnTransform.SetRotation(MeshComp->GetOwner()->GetTransform().GetRotation());

		// ���ο� ���͸� ������ش�.
		AActor* NewActor = MeshComp->GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);

		AURProjectile* Projectile = Cast<AURProjectile>(NewActor);

		if (!Projectile)
			return;

		// ���⼭ �̻����� �ɼ��� �����ϴ� ������ Ư�� ��Ÿ�ָ��� �̻����� ������ �ٸ��� �� �� �־�̴�.
		Projectile->SetInfo(m_CollisionProfileName, m_Speed, m_LifeTime);
	}
		break;
	}
	
}
