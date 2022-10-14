// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Skill/UR_LightningActor.h"
#include "Components/SphereComponent.h"
#include "../PlayCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUR_LightningActor::AUR_LightningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_SphereComponent = CreateDefaultSubobject<USphereComponent>(FName(TEXT("LightningCollision")));
	m_SphereComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	m_SphereComponent->SetCollisionProfileName(FName(TEXT("PlayerAttack")));
	RootComponent = m_SphereComponent;
	// 이 방식을 사용하면 나와 상대가 같이 충돌해서 양쪽이 동시에 들어오는 곤란한 상황이 발생하지 않는다.
	// AddDynamic이란 디파인을 통해서 해야지만 간편하게 작성할 수 있음.
	m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AUR_LightningActor::OnCollision);

}

// Called when the game starts or when spawned
void AUR_LightningActor::BeginPlay()
{
	Super::BeginPlay();

	/*APlayCharacter* Player = Cast<APlayCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!Player)
	{
		return;
	}*/
	/*APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!Controller || Controller->IsValidLowLevel())
	{
		return;
	}
	FHitResult HitResult;
	Controller->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);*/

	//SetActorLocation(HitResult.ImpactPoint);

	
}

// Called every frame
void AUR_LightningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUR_LightningActor::OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent, int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result)
{
	// 충돌했을경우 대상의 컴포넌트를 얻어올 수 있다.
	AURCharacter* Chracter = Cast<AURCharacter>(_DestActor);

	if (nullptr == Chracter)
	{
		return;
	}

	Chracter->CallDamage(m_Damage);
}

