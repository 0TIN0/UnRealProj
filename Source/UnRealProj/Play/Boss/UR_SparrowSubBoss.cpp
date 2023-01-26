// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/UR_SparrowSubBoss.h"
#include "../WarriorCharacter.h"
#include "../Controller/URMonsterController.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraComponent.h"

AUR_SparrowSubBoss::AUR_SparrowSubBoss()	:
	m_RandAttackNumb(SparrowAttack_Type::Default)
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AURMonsterController::StaticClass(); Tags.Add(FName("Khaimera"));

	{
		UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

		if (Component)
		{
			Component->SetCollisionProfileName(FName(TEXT("Monster")));
		}

		RootComponent = Component;
	}

	{
		m_BowMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("BowComponent")));
		m_BowMesh->SetupAttachment(GetMesh(), FName(TEXT("Weapon_Left")));

		m_ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("ArrowComponent")));
		m_ArrowMesh->SetupAttachment(GetMesh(), FName(TEXT("Muzzle_01")));
		m_ArrowMesh->SetHiddenInGame(true);
	}

	{
		m_IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("SparrowIconArm")));
		m_IconArm->SetRelativeRotation(FRotator(-90, 0, 0));
		// 자식으로 달아준다.
		m_IconArm->SetupAttachment(RootComponent);
		m_IconArm->TargetArmLength = 300.f;

		//Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'"));

		m_PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("SparrowBossIconPlane"));
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

const FURMonsterDataInfo* AUR_SparrowSubBoss::BossDataInit()
{
	m_SparrowData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(FName(TEXT("Sparrow")));

	if (!m_SparrowData)
	{
		UE_LOG(LogTemp, Error, TEXT("SparrowData Empty"));
	}

	// MonsterDataTable에다가 미리 지정을 해놓았기 떄문에
	// 기존에 갖고있는 애니메이션이 있다면 클리어한다 Empty() == Clear();
	SetAnimations(m_SparrowData->Animations);

	SetHP(m_SparrowData->HP);
	m_MaxHP = m_SparrowData->HP;

	m_KnockBackHitPower = 700.f;
	m_KnockDownHitPower = 1500.f;
	GetCharacterMovement()->MaxWalkSpeed = m_SparrowData->Speed;

	return m_SparrowData;
}

void AUR_SparrowSubBoss::BeginPlay()
{
	Super::BeginPlay();

	DamageOff();

	for (auto& Anim : m_BossAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void AUR_SparrowSubBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUR_SparrowSubBoss::DamageOn(bool _IsKnockBack)
{
	Super::DamageOn(_IsKnockBack);
}

void AUR_SparrowSubBoss::DamageOff()
{
	Super::DamageOff();
}

void AUR_SparrowSubBoss::CallDamage(double _Damage, AActor* _Actor, bool _IsKnockBack, bool _IsCameraShake)
{
	Super::CallDamage(_Damage, _Actor, _IsKnockBack, _IsCameraShake);
	
	if (IsDeath())
	{
		if (!GetCharacterMovement()->IsFalling())
		{
			GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::DeathStart);
		}

		return;
	}

	// 죽지 않았을때만 동작되도록
	switch (m_HitType)
	{
	case EHitType::NormalHit:
	{
		if (_IsKnockBack)
		{
			switch (m_HitDir)
			{
			case EHitDir::Forward:
				if (!GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown))
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::ForwardHit);
				}
				else
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::KnockDown);
				}
				break;
			case EHitDir::Backward:
				if (!GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown))
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackwardHit);
				}
				else
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::KnockDown);
				}
				break;
			case EHitDir::Left:
				if (!GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown))
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::LeftHit);
				}
				else
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::KnockDown);
				}
				break;
			case EHitDir::Right:
				if (!GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown))
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::RightHit);
				}
				else
				{
					GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::KnockDown);
				}
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
