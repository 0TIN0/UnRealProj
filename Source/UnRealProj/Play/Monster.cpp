// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "PlayCharacter.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Controller/URMonsterController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global/URStructs.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AMonster::AMonster()	:
	m_IsDamageCheck(false),
	m_IsUltimateHit(false),
	m_PushTime(1.f)
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AURMonsterController::StaticClass();

	Tags.Add(FName("Monster"));

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
		m_DamageCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Damage Collision")));

		// 어떤 충돌프로파일로 설정할지 넣어줌
		m_DamageCollision->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
		// 부모를 설정하고 어떤 소켓에 지정을 할지 넣어주어야함.
		m_DamageCollision->SetupAttachment(GetMesh(), FName(TEXT("AttackSocket")));
	}

	{
		m_IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("IconArm")));
		m_IconArm->SetRelativeRotation(FRotator(-90, 0, 0));
		// 자식으로 달아준다.
		m_IconArm->SetupAttachment(RootComponent);
		m_IconArm->TargetArmLength = 300.f;

		//Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'"));

		m_PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("IconPlane"));
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

	UURGameInstance* Instance = GetWorld()->GetGameInstance<UURGameInstance>();

	if (!Instance ||
		!Instance->IsValidLowLevel())
	{
		return;
	}

	int32 Data = Instance->GetRandomStream().RandRange(1, 2);

	m_DropTable = Instance->GetRandomDropData(Data);

	if (GetWorld() != nullptr)
	{
		m_Player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn<APlayCharacter>();
	}
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (m_IsUltimateHit)
	//{
	//	m_PushTime -= DeltaTime;

	//	if (m_PushTime < 0.f)
	//	{
	//		m_PushTime = 1.f;
	//		m_IsUltimateHit = false;
	//		GetCharacterMovement()->MaxAcceleration = 300.f;	// 300
	//		GetCharacterMovement()->MaxWalkSpeed = 400.f;	//400
	//	}

	//	SetDirMovementInput(m_UltimateHitDir);


	//}
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
			if (m_IsKnockDown)
			{
				Character->SetHitType(EHitType::KnockDownHit);
			}
			else
			{
				Character->SetHitType(EHitType::NormalHit);
			}
			Check = true;
			Character->CallDamage(3.0, this);
			
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

void AMonster::CallDamage(double _Damage, AActor* _Actor)
{
	Super::CallDamage(_Damage, _Actor);

	switch (m_HitType)
	{
	case EHitType::NormalHit:
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


	if (IsDeath())
	{
		ItemDrop(m_DropTable);

		m_Player->AddMonsterCount();

		Destroy();
	}
}
