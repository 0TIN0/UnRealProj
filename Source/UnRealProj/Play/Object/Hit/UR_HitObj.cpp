// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/Hit/UR_HitObj.h"

// Sets default values
AUR_HitObj::AUR_HitObj()	:
	m_DestroyTime(1.5f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUR_HitObj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_HitObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_DestroyTime -= DeltaTime;

	if (m_DestroyTime <= 0.f)
	{
		Destroy();
	}
}

