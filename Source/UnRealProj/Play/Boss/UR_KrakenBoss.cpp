// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/UR_KrakenBoss.h"
#include "../Controller/URMonsterController.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AUR_KrakenBoss::AUR_KrakenBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AURMonsterController::StaticClass();

	Tags.Add(FName("Kraken"));

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
		m_DamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("KrakenAttackCollision")));

		// � �浹�������Ϸ� �������� �־���
		m_DamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// �θ� �����ϰ� � ���Ͽ� ������ ���� �־��־����.
		m_DamageCollision->SetupAttachment(GetMesh(), FName(TEXT("AttackSocket")));
	}
	{
		m_IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("KrakenIconArm")));
		m_IconArm->SetRelativeRotation(FRotator(-90, 0, 0));
		// �ڽ����� �޾��ش�.
		m_IconArm->SetupAttachment(RootComponent);
		m_IconArm->TargetArmLength = 300.f;

		//Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'"));

		m_PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("KrakenIconPlane"));
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

const FURMonsterDataInfo* AUR_KrakenBoss::BossDataInit()
{
	m_KrakenData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(FName(TEXT("Kraken")));

	if (!m_KrakenData)
	{
		UE_LOG(LogTemp, Error, TEXT("KrakenData Empty"));
	}

	// MonsterDataTable���ٰ� �̸� ������ �س��ұ� ������
	// ������ �����ִ� �ִϸ��̼��� �ִٸ� Ŭ�����Ѵ� Empty() == Clear();
	SetAnimations(m_KrakenData->Animations);

	SetHP(m_KrakenData->HP);

	return m_KrakenData;
}

void AUR_KrakenBoss::BeginPlay()
{
	Super::BeginPlay();

	DamageOff();

	for (auto& Anim : m_BossAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	SetTargetLook(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void AUR_KrakenBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUR_KrakenBoss::DamageOn()
{
	m_DamageCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);

	TArray<FHitResult> Targets = CollisionCheck(m_DamageCollision->GetComponentLocation(),
		FName(TEXT("MonsterAttackTrace")), m_DamageCollision->GetCollisionShape());

	bool Check = false;

	for (size_t i = 0; i < Targets.Num(); ++i)
	{
		AURCharacter* Character = Cast<AURCharacter>(Targets[i].GetActor());

		if (Character)
		{
			Check = true;
			Character->CallDamage(10.0);
		}
	}

	FColor Color = FColor::Green;

	if (Check)
	{
		Color = FColor::Red;
	}

	DrawDebugSphere(GetWorld(), m_DamageCollision->GetComponentLocation(), m_DamageCollision->GetScaledSphereRadius(),
		15, Color, false, 0.1f);
}

void AUR_KrakenBoss::DamageOff()
{
	m_DamageCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AUR_KrakenBoss::CallDamage(double _Damage, AActor* _Actor, bool _IsKnockBack)
{
	Super::CallDamage(_Damage, _Actor);

	if (IsDeath())
	{
		Destroy();
	}
}
