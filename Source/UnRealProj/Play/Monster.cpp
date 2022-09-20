// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "URMonsterController.h"
#include "Components/CapsuleComponent.h"

AMonster::AMonster()
{
	AIControllerClass = AURMonsterController::StaticClass();

	Tags.Add(FName("Monster"));

	UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

	if (Component)
	{
		Component->SetCollisionProfileName(FName(TEXT("Monster")));
	}
}

const FURMonsterDataInfo* AMonster::MonsterDataInit()
{
	m_MonsterData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(m_MonsterStatusKey);

	if (!m_MonsterData)
	{
		UE_LOG(LogTemp, Error, TEXT("MonterData Empty"));
	}

	return m_MonsterData;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
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
