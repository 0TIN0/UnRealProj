// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/Sparrow/UR_RainShootCreateDecal.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "../../WarriorCharacter.h"
#include "../../Boss/BossObj/Decal/UR_RainPosDecal.h"

void UUR_RainShootCreateDecal::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AUR_SparrowSubBoss* Boss = MeshComp->GetOwner<AUR_SparrowSubBoss>();

	if (!Boss || !Boss->IsValidLowLevel())
	{
		return;
	}

	AWarriorCharacter* Player = Boss->GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();

	if (!Player || !Player->IsValidLowLevel())
	{
		return;
	}

	switch (Boss->GetRandAttackNumb())
	{
	case SparrowAttack_Type::RainBowShoot:
	{
		FVector DecalPos;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Player);
		CollisionParams.AddIgnoredActor(Boss);

		FVector StartPos = Player->GetActorLocation();
		FVector EndPos = StartPos;
		EndPos.Z -= 500.f;

		FHitResult HitResult;

		// �ٴ����� Lay�� �� ��Į�� ��ġ�� ��Ȯ�ϰ� �ٴ��̶� ������ �ϱ� ���ؼ� �Ʒ�ó�� ����
		if (Player->GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECollisionChannel::ECC_Visibility, CollisionParams))
		{
			// ��Į�� ��ġ�� �浹�� ��ġ�� ����
			DecalPos = HitResult.Location;

			FActorSpawnParameters SpawnParams;
			FTransform SpawnTransform = FTransform(DecalPos);

			AUR_RainPosDecal* Decal = Player->GetWorld()->SpawnActor<AUR_RainPosDecal>(AUR_RainPosDecal::StaticClass(), SpawnTransform, SpawnParams);
			Decal->SetAttackType(Boss->GetRandAttackNumb());
			Decal->SetData(Boss->GetSparrowData());
		}
	}
		break;
	case SparrowAttack_Type::RainBowBurstShoot:
	{
		FVector DecalPos;

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Player);
		CollisionParams.AddIgnoredActor(Boss);

		FVector StartPos = Player->GetActorLocation();
		FVector EndPos = StartPos;
		EndPos.Z -= 500.f;

		FHitResult HitResult;

		// �ٴ����� Lay�� �� ��Į�� ��ġ�� ��Ȯ�ϰ� �ٴ��̶� ������ �ϱ� ���ؼ� �Ʒ�ó�� ����
		if (Player->GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECollisionChannel::ECC_Visibility, CollisionParams))
		{
			// ��Į�� ��ġ�� �浹�� ��ġ�� ����
			DecalPos = HitResult.Location;

			FActorSpawnParameters SpawnParams;
			FTransform SpawnTransform = FTransform(DecalPos);

			AUR_RainPosDecal* Decal = Player->GetWorld()->SpawnActor<AUR_RainPosDecal>(AUR_RainPosDecal::StaticClass(), SpawnTransform, SpawnParams);
			Decal->SetAttackType(Boss->GetRandAttackNumb());
			Decal->SetData(Boss->GetSparrowData());
		}
	}
		break;
	}
}
