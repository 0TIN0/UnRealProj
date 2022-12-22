// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/UR_BossMonster.h"
#include "../Controller/URMonsterController.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AUR_BossMonster::AUR_BossMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AURMonsterController::StaticClass();

	Tags.Add(FName("Lich"));

	{
		UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

		if (Component)
		{
			Component->SetCollisionProfileName(FName(TEXT("Monster")));
		}

		RootComponent = Component;
	}
	{
		m_IconArm = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("LichIconArm")));
		m_IconArm->SetRelativeRotation(FRotator(-90, 0, 0));
		// 자식으로 달아준다.
		m_IconArm->SetupAttachment(RootComponent);
		m_IconArm->TargetArmLength = 300.f;

		//Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'
		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
		ConstructorHelpers::FObjectFinder<UMaterialInterface> MatPath(TEXT("Material'/Game/Resource/Play/Sprite/UI/MonsterIcon_Mat.MonsterIcon_Mat'"));

		m_PlaneComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("LichIconPlane"));
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


	GetCharacterMovement()->RotationRate = FRotator(0.0f, 940.0f, 0.0f);
}

const FURMonsterDataInfo* AUR_BossMonster::BossDataInit()
{
	m_BossData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(FName(TEXT("Lich")));

	if (!m_BossData)
	{
		UE_LOG(LogTemp, Error, TEXT("MonterData Empty"));
	}

	// MonsterDataTable에다가 미리 지정을 해놓았기 떄문에
	// 기존에 갖고있는 애니메이션이 있다면 클리어한다 Empty() == Clear();
	SetAnimations(m_BossData->Animations);

	SetHP(m_BossData->HP);

	return m_BossData;
}

void AUR_BossMonster::BeginPlay()
{
	Super::BeginPlay();

	DamageOff();

	for (auto& Anim : m_BossAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

	GetAnimationInstance()->ChangeAnimMontage(BossAnimation::Spawn);
	SetTargetLook(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

void AUR_BossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_RandNumb = GetGameInstance<UURGameInstance>()->GetRandomStream().FRandRange(0, 20);

	if (m_RandNumb == 0)
	{
		FVector Pos = GetActorLocation();

		int RandPosX = GetGameInstance<UURGameInstance>()->GetRandomStream().FRandRange(-1000, 1000);
		int RandPosY = GetGameInstance<UURGameInstance>()->GetRandomStream().FRandRange(-1000, 1000);

		Pos.X += RandPosX;
		Pos.Y += RandPosY;
		Pos.Z = GetActorLocation().Z - 200.0;

		FTransform SpawnTransform = FTransform(Pos);

		TSubclassOf<AActor> SpawnActorClass = GetSpawnActorClass();

		// 새로운 엑터를 만들어준다.
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, SpawnTransform);

		//GetAnimationInstance()->ChangeAnimMontage(BossAnimation::Skill2);
	}
}

void AUR_BossMonster::DamageOn()
{
	Super::DamageOn();
}

void AUR_BossMonster::DamageOff()
{
	Super::DamageOff();
}

void AUR_BossMonster::CallDamage(double _Damage, AActor* _Actor)
{
	Super::CallDamage(_Damage);

	if (IsDeath())
	{
		Destroy();
	}
}
