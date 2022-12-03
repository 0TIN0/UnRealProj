// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Skill/Boss/UR_CircleActor.h"
#include "../..//PlayCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUR_CircleActor::AUR_CircleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>(FName(TEXT("DamageCollision")));

	m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AUR_CircleActor::OnCollisionBegin);
	m_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AUR_CircleActor::OnCollisionEnd);
	m_SphereComponent->SetCollisionProfileName(FName(TEXT("MonsterAttack")));
	RootComponent = m_SphereComponent;

	m_RandomSkillNumb = 0;
	m_DamageTime = 0.2f;
	m_IsCollision = false;
}

// Called when the game starts or when spawned
void AUR_CircleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_CircleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_Player)
		m_Player = Cast<AURCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// 瘤加利牢 平单固瘤
	TickDamage(m_Player, DeltaTime);

}

void AUR_CircleActor::OnCollisionBegin(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	m_IsCollision = true;
}

void AUR_CircleActor::OnCollisionEnd(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex)
{
	m_IsCollision = false;
}

void AUR_CircleActor::TickDamage(AURCharacter* _Actor, float DeltaTime)
{
	if (m_IsCollision)
	{
		m_DamageTime -= DeltaTime;

		if (m_DamageTime < 0.f)
		{
			m_DamageTime = 0.2f;

			_Actor->CallDamage(1.0, this);
		}
	}
}

