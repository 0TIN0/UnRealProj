// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/UR_KhaimeraBoss.h"
#include "../Controller/URMonsterController.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AUR_KhaimeraBoss::AUR_KhaimeraBoss()	:
	m_IsBerserk(false)
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AURMonsterController::StaticClass();

	Tags.Add(FName("Khaimera"));

	{
		UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

		if (Component)
		{
			Component->SetCollisionProfileName(FName(TEXT("Monster")));
		}

		RootComponent = Component;
	}

	{
		// CDO ����
		// ���͸� ���鶧���� ������ �������� �ʰ� �⺻������ ������������ �����ؾߵǴ� �κ��� ����°���
		// ex : �⺻ �����Ҷ� �������ִ� �浹ü
		m_LDamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("KhaimeraBossAttackLCollision")));

		// � �浹�������Ϸ� �������� �־���
		m_LDamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// �θ� �����ϰ� � ���Ͽ� ������ ���� �־��־����.
		m_LDamageCollision->SetupAttachment(GetMesh(), FName(TEXT("weapon_l_head")));


		m_RDamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("KhaimeraBossAttackRCollision")));

		// � �浹�������Ϸ� �������� �־���
		m_RDamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// �θ� �����ϰ� � ���Ͽ� ������ ���� �־��־����.
		m_RDamageCollision->SetupAttachment(GetMesh(), FName(TEXT("weapon_r_head")));
	}
	{
		m_IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("KhaimeraIconArm")));
		m_IconArm->SetRelativeRotation(FRotator(-90, 0, 0));
		// �ڽ����� �޾��ش�.
		m_IconArm->SetupAttachment(RootComponent);
		m_IconArm->TargetArmLength = 300.f;

		//Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'"));

		m_PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("GruxBossIconPlane"));
		m_PlaneComponent->SetRelativeRotation(FRotator(0, 90, 90));
		m_PlaneComponent->SetupAttachment(m_IconArm);
		m_PlaneComponent->SetHiddenInSceneCapture(true);
		m_PlaneComponent->SetHiddenInGame(false);
		m_PlaneComponent->SetCastHiddenShadow(true);

		if (nullptr != MeshPath.Object
			&& MeshPath.Object->IsValidLowLevel())
		{
			m_PlaneComponent->SetStaticMesh(MeshPath.Object);
		}

		if (nullptr != MatPath.Object
			&& MatPath.Object->IsValidLowLevel())
		{
			m_PlaneComponent->SetMaterial(0, MatPath.Object);
		}

	}
}

const FURMonsterDataInfo* AUR_KhaimeraBoss::BossDataInit()
{
	m_KhaimeraData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(FName(TEXT("Khaimera")));

	if (!m_KhaimeraData)
	{
		UE_LOG(LogTemp, Error, TEXT("KhaimeraData Empty"));
	}

	// MonsterDataTable���ٰ� �̸� ������ �س��ұ� ������
	// ������ �����ִ� �ִϸ��̼��� �ִٸ� Ŭ�����Ѵ� Empty() == Clear();
	SetAnimations(m_KhaimeraData->Animations);

	SetHP(m_KhaimeraData->HP);

	m_KnockBackHitPower = 700.f;
	m_KnockDownHitPower = 1500.f;
	GetCharacterMovement()->MaxWalkSpeed = m_KhaimeraData->Speed;

	return m_KhaimeraData;
}

void AUR_KhaimeraBoss::BeginPlay()
{
	Super::BeginPlay();

	DamageOff();

	for (auto& Anim : m_BossAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

	GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::Spawn);
	SetTargetLook(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void AUR_KhaimeraBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUR_KhaimeraBoss::DamageOn()
{
	m_RDamageCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	TArray<FHitResult> Targets = CollisionCheck(m_RDamageCollision->GetComponentLocation(),
		FName(TEXT("MonsterAttackTrace")), m_RDamageCollision->GetCollisionShape());

	bool Check = false;

	for (size_t i = 0; i < Targets.Num(); ++i)
	{
		AURCharacter* Character = Cast<AURCharacter>(Targets[i].GetActor());

		if (Character)
		{
			if (m_IsKnockDown)
			{
				Character->SetHitType(EHitType::KnockDownHit);
			}
			else
			{
				Character->SetHitType(EHitType::NormalHit);
			}
			Check = true;

			int Damage = GetGameInstance<UURGameInstance>()->GetRandomStream().FRandRange(m_KhaimeraData->MinAttack, m_KhaimeraData->MaxAttack);

			Character->CallDamage(Damage, this);
		}
	}

	FColor Color = FColor::Green;

	if (Check)
	{
		Color = FColor::Red;
	}

	DrawDebugSphere(GetWorld(), m_RDamageCollision->GetComponentLocation(), m_RDamageCollision->GetScaledSphereRadius(),
		15, Color, false, 0.1f);
}

void AUR_KhaimeraBoss::DamageOff()
{
	m_RDamageCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AUR_KhaimeraBoss::CallDamage(double _Damage, AActor* _Actor, bool _IsKnockBack)
{
	Super::CallDamage(_Damage, _Actor, _IsKnockBack);

	if (IsDeath())
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::DeathStart);
		}

		return;
	}

	// ���� �ʾ������� ���۵ǵ���
	switch (m_HitType)
	{
	case EHitType::NormalHit:
	{
		if (_IsKnockBack)
		{
			switch (m_HitDir)
			{
			case EHitDir::Forward:
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::ForwardHit);
				break;
			case EHitDir::Backward:
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackwardHit);
				break;
			case EHitDir::Left:
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::LeftHit);
				break;
			case EHitDir::Right:
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::RightHit);
				break;
			}
		}
	}
	break;
	case EHitType::KnockDownHit:
	{
		UAnimMontage* Montage = GetAnimationInstance()->GetAnimation(DefaultAnimation::KnockDown);

		if (Montage)
		{
			GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::KnockDown);
		}
	}
	break;
	}
}

