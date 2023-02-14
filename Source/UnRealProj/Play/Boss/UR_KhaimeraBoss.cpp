// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/UR_KhaimeraBoss.h"
#include "BossObj/UR_BlackHole.h"
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

AUR_KhaimeraBoss::AUR_KhaimeraBoss()	:
	m_SpawnRange(1000.f),
	m_IsBerserk(false),
	m_BlackHoleSpawnTime(5.f)
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
		// CDO 설정
		// 몬스터를 만들때마다 일일히 구성하지 않고 기본적으로 무조건적으로 설정해야되는 부분을 만드는것임
		// ex : 기본 공격할때 데미지주는 충돌체
		m_LDamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("KhaimeraBossAttackLCollision")));

		// 어떤 충돌프로파일로 설정할지 넣어줌
		m_LDamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// 부모를 설정하고 어떤 소켓에 지정을 할지 넣어주어야함.
		m_LDamageCollision->SetupAttachment(GetMesh(), FName(TEXT("weapon_l_head")));


		m_RDamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("KhaimeraBossAttackRCollision")));

		// 어떤 충돌프로파일로 설정할지 넣어줌
		m_RDamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// 부모를 설정하고 어떤 소켓에 지정을 할지 넣어주어야함.
		m_RDamageCollision->SetupAttachment(GetMesh(), FName(TEXT("weapon_r_head")));
	}
	{
		m_IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("KhaimeraIconArm")));
		m_IconArm->SetRelativeRotation(FRotator(-90, 0, 0));
		// 자식으로 달아준다.
		m_IconArm->SetupAttachment(RootComponent);
		m_IconArm->TargetArmLength = 300.f;

		//Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resource/Play/UI/Purple_Circle_Full_Mat.Purple_Circle_Full_Mat'"));

		m_PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("KhaimeraBossIconPlane"));
		m_PlaneComponent->SetRelativeRotation(FRotator(0, 90, 90));
		m_PlaneComponent->SetupAttachment(m_IconArm);
		m_PlaneComponent->SetHiddenInSceneCapture(true);
		m_PlaneComponent->SetHiddenInGame(true);
		m_PlaneComponent->SetCastHiddenShadow(false);

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

	// MonsterDataTable에다가 미리 지정을 해놓았기 떄문에
	// 기존에 갖고있는 애니메이션이 있다면 클리어한다 Empty() == Clear();
	SetAnimations(m_KhaimeraData->Animations);

	SetHP(m_KhaimeraData->HP);
	m_MaxHP = m_KhaimeraData->HP;

	m_KnockBackHitPower = 700.f;
	m_KnockDownHitPower = 1500.f;
	GetCharacterMovement()->MaxWalkSpeed = m_KhaimeraData->Speed;

	return m_KhaimeraData;
}

void AUR_KhaimeraBoss::SetBerserkMesh()
{
	if (m_BerserkerMesh)
	{
		GetMesh()->SetSkeletalMesh(m_BerserkerMesh);
	}
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

	if (m_IsBerserk)
	{
		m_BlackHoleSpawnTime -= DeltaTime;

		if (0.f >= m_BlackHoleSpawnTime)
		{
			if (m_BlackHole == nullptr)
			{
				CreateBlackHole();
			}
		}
	}
}

void AUR_KhaimeraBoss::DamageOn(bool _IsKnockBack)
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

			Character->CallDamage(Damage, this, _IsKnockBack);
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

void AUR_KhaimeraBoss::CallDamage(double _Damage, AActor* _Actor, bool _IsKnockBack, bool _IsCameraShake)
{
	if (m_IsInvincibility)
	{
		return;
	}
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

void AUR_KhaimeraBoss::CreateBlackHole()
{
	UURGameInstance* Inst = GetWorld()->GetGameInstance<UURGameInstance>();
	FVector vecSpawnPos;

	// 범위값을 기반으로 랜덤한 float타입 값을 얻어온다.
	// 하지만 이런식으로 구성을 하면 사각형의 모양이 만들어지게 된다.
	vecSpawnPos.X = Inst->GetRandomStream().FRandRange(-m_SpawnRange, m_SpawnRange);
	vecSpawnPos.Y = Inst->GetRandomStream().FRandRange(-m_SpawnRange, m_SpawnRange);

	vecSpawnPos.Normalize();

	vecSpawnPos *= Inst->GetRandomStream().FRandRange(0.f, m_SpawnRange);

	vecSpawnPos.Z = 0.0;

	// 기본적으로 0을 중심으로 하고있기 때문에 스폰엑터의 위치 중심으로 바꿔줌
	vecSpawnPos += GetActorLocation();

	FRotator Rot = FRotator();

	FTransform SpawnTransform = FTransform(Rot, vecSpawnPos);

	m_BlackHole = GetWorld()->SpawnActor<AUR_BlackHole>(m_SpawnActorClass, SpawnTransform);

	if (m_BlackHole)
	{
		AWarriorCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();
		Player->SetBlackHole(m_BlackHole);
		Player->GetBlackHoleBodyComponent()->SetVariableVec3(FName(TEXT("Start Position_SpawnRate")), m_BlackHole->GetActorLocation());
	}
}

