// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Boss/BossObj/UR_SPMuzzleFlash.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUR_SPMuzzleFlash::AUR_SPMuzzleFlash()	:
	m_MuzzleType(SPMuzzle_Type::EvadeShoot),
	m_DestroyTime(1.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MuzzleParticleSystem(TEXT("ParticleSystem'/Game/ParagonWraith/FX/Particles/Abilities/ScopedShot/FX/P_Wraith_Sniper_MuzzleFlash.P_Wraith_Sniper_MuzzleFlash'"));

	m_MuzzleFlashFX = MuzzleParticleSystem.Object;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_MuzzleComponent = CreateDefaultSubobject<UParticleSystemComponent>(FName(TEXT("MuzzleFlashComponent")));
	m_MuzzleComponent->SetupAttachment(RootComponent);

	// 찾았는지 못찾았는지 로그 띄워준다.
	// BeginPlay에서 Template설정해주고 있기때문에 해주는게 좋다.
	// 물론 게임 실행할때도 로그 띄워주긴함.
	if (!MuzzleParticleSystem.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("MuzzleParticleSystem Find Error!"));
	}
	
	m_MuzzleComponent->SetRelativeScale3D(FVector(10.0, 10.0, 10.0));

}

void AUR_SPMuzzleFlash::BeginPlay()
{
	Super::BeginPlay();
	
	// 스폰엑터디퍼드로 생성을한다음 피니쉬스폰을 하기 전에 해당 타입을 설정해주면
	// 씬에 출력되기전에(BeginPlay 동작하기 전) 타입을 설정되기 때문에 BeginPlay에서
	// 타입에대한 Template를 설정해준다.
	switch (m_MuzzleType)
	{
	case SPMuzzle_Type::EvadeShoot:
		m_MuzzleComponent->SetTemplate(m_MuzzleFlashFX);
		break;
	}
}

// Called every frame
void AUR_SPMuzzleFlash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}
}

