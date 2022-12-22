// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Skill/UR_UltimateHit.h"
#include "Components/SphereComponent.h"
#include "../PlayCharacter.h"
#include "../Monster.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUR_UltimateHit::AUR_UltimateHit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>(FName(TEXT("UltimateCollision")));
	m_SphereComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	m_SphereComponent->SetCollisionProfileName(FName(TEXT("PlayerAttack")));
	RootComponent = m_SphereComponent;
	// 이 방식을 사용하면 나와 상대가 같이 충돌해서 양쪽이 동시에 들어오는 곤란한 상황이 발생하지 않는다.
	// AddDynamic이란 디파인을 통해서 해야지만 간편하게 작성할 수 있음.
	m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AUR_UltimateHit::OnCollision);

}

// Called when the game starts or when spawned
void AUR_UltimateHit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_UltimateHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUR_UltimateHit::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
	int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	// 충돌했을경우 대상의 컴포넌트를 얻어올 수 있다.
	AURCharacter* Character = Cast<AURCharacter>(_DestActor);

	AURCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<AURCharacter>();

	if (nullptr == Character)
	{
		return;
	}

	m_Dir = Character->GetActorLocation() - Player->GetActorLocation();
	m_Dir.GetSafeNormal();

	Character->CallDamage(m_Damage);

	AMonster* Monster = Cast<AMonster>(Character);
	Monster->SetUltimateHitDir(m_Dir);
	Monster->SetUltimateHitEnable(true);
	Monster->GetCharacterMovement()->MaxAcceleration = 3000.f;	// 300
	Monster->GetCharacterMovement()->MaxWalkSpeed = 4000.f;	//400

	m_SphereComponent->DestroyComponent();
}

