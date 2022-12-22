// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/NPC/UR_NPCFirst.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

AUR_NPCFirst::AUR_NPCFirst()
{
	PrimaryActorTick.bCanEverTick = true;

	{
		m_InteractionBox = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("InteractionBox")));
		m_InteractionBox->SetCollisionProfileName(FName(TEXT("InteractionCollision")));
		m_InteractionBox->SetBoxExtent(FVector(200.f, 200.f, 200.f));

		m_InteractionBox->SetupAttachment(RootComponent);
	}
}

void AUR_NPCFirst::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Anim : m_NPCAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);

	//DrawDebugBox(GetWorld(), m_InteractionBox->GetOwner()->GetActorLocation(), FVector(70.f, 70.f, 70.f), FColor::Red, false, 10.f);
}

void AUR_NPCFirst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
