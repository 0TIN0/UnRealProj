// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "URMonsterController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Global/URStructs.h"

AMonster::AMonster()	:
	m_IsDamageCheck(false)
{
	AIControllerClass = AURMonsterController::StaticClass();

	Tags.Add(FName("Monster"));

	{
		UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

		if (Component)
		{
			Component->SetCollisionProfileName(FName(TEXT("Monster")));
		}
	}

	{
		// CDO 설정
		// 몬스터를 만들때마다 일일히 구성하지 않고 기본적으로 무조건적으로 설정해야되는 부분을 만드는것임
		// ex : 기본 공격할때 데미지주는 충돌체
		m_DamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Damage Collision")));

		// 어떤 충돌프로파일로 설정할지 넣어줌
		m_DamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// 부모를 설정하고 어떤 소켓에 지정을 할지 넣어주어야함.
		m_DamageCollision->SetupAttachment(GetMesh(), FName(TEXT("AttackSocket")));
	}
}

const FURMonsterDataInfo* AMonster::MonsterDataInit()
{
	//m_MonsterData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(m_MonsterStatusKey);

	// 클래스의 이름으로 구성하는 이유는
	// 오브젝트의 이름의 경우 Dragon_C_0을 시작으로 동일한 녀석이 스폰되면 뒤에 숫자가 증가함
	// 그래서 이름이 동일한 클래스의 이름으로 만드는것임
	FString Name = GetClass()->GetName();

	// 이름에 _C로 되어있는 부분을 지운다는 의미
	// 1번인자의 이름을 2번인자로 바꾼다는 의미이다.
	Name = Name.Replace(TEXT("_C"), TEXT(""));

	m_MonsterData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(*Name);

	if (!m_MonsterData)
	{
		UE_LOG(LogTemp, Error, TEXT("MonterData Empty"));
	}

	// MonsterDataTable에다가 미리 지정을 해놓았기 떄문에
	// 기존에 갖고있는 애니메이션이 있다면 클리어한다 Empty() == Clear();
	SetAnimations(m_MonsterData->Animations);

	SetHP(m_MonsterData->HP);

	return m_MonsterData;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	DamageOff();
}

void AMonster::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

}

void AMonster::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

void AMonster::NotifyActorEndOverlap(AActor* OtherActor)
{
}

void AMonster::DamageOn()
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
			Character->CallDamage(1.0);
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

void AMonster::DamageOff()
{
	m_DamageCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

void AMonster::CallDamage(double _Damage)
{
	Super::CallDamage(_Damage);

	if (IsDeath())
	{
		Destroy();
	}
}
