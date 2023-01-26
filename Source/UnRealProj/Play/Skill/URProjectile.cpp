// Fill out your copyright notice in the Description page of Project Settings.


#include "URProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../URCharacter.h"
#include "../PlayCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AURProjectile::AURProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName(TEXT("DefaultSceneRoot")));

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>(FName(TEXT("DamageCollision")));

	// 이 방식을 사용하면 나와 상대가 같이 충돌해서 양쪽이 동시에 들어오는 곤란한 상황이 발생하지 않는다.
	// AddDynamic이란 디파인을 통해서 해야지만 간편하게 작성할 수 있음.
	m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AURProjectile::OnCollision);

	RootComponent = m_SphereComponent;

	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("ProjectileMovementComponent")));

	// 이래야 중력을 받고 떨어지지 않는다. 미사일의 경우는 1자로 앞으로 나아가기 때문
	m_ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	m_ProjectileMovementComponent->bRotationFollowsVelocity = true;

	m_Damage = 5.f;
}

// Called when the game starts or when spawned
void AURProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AURProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	m_ProjectileMovementComponent->Velocity = m_SkillDir * m_Speed;

	if (0.0f >= (m_LifeTime -= DeltaTime))
	{
		Destroy();
	}
}

void AURProjectile::SetInfo(FName _CollisionProfileName, float _Speed, float _LifeTime)
{
	m_Speed = _Speed;

	m_LifeTime = _LifeTime;

	m_SphereComponent->SetCollisionProfileName(_CollisionProfileName);
}

void AURProjectile::SetInfo(FName _CollisionProfileName, FVector _Dir, float _Speed, float _LifeTime)
{
	m_Speed = _Speed;

	m_LifeTime = _LifeTime;

	m_SkillDir = _Dir;

	m_SphereComponent->SetCollisionProfileName(_CollisionProfileName);
}

void AURProjectile::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	// 충돌했을경우 대상의 컴포넌트를 얻어올 수 있다.
	AURCharacter* Chracter = Cast<AURCharacter>(_DestActor);

	if (nullptr == Chracter)
	{
		return;
	}

	Chracter->CallDamage(m_Damage, this);
}

