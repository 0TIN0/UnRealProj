// Fill out your copyright notice in the Description page of Project Settings.


#include "URCharacter.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AURCharacter::AURCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("URCharacter"));

}

AActor* AURCharacter::TargetSearch(FName _Name, float _Range)
{
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _Name, Actors);

	if (Actors.IsEmpty())
	{
		return nullptr;
	}

	if (0.f >= _Range)
	{
		return Actors[0];
	}

	FVector Location = GetActorLocation();

	size_t Size = Actors.Num();

	for (size_t i = 0; i < Size; ++i)
	{
		// 플레이어와 엑터들간의 위치값을 이용해서 거리를 구한다.
		float Length = (Location - Actors[i]->GetActorLocation()).Size();

		if (_Range > Length)
		{
			return Actors[i];
		}
	}

	return nullptr;
}

TArray<AActor*> AURCharacter::TargetsSearch(FName _Name, float _Range)
{
	TArray<AActor*> Actors;
	TArray<AActor*> SelectActors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _Name, Actors);

	if (Actors.IsEmpty())
	{
		return Actors;
	}

	if (0 >= _Range)
	{
		return Actors;
	}

	FVector Location = GetActorLocation();

	for (size_t i = 0; i < Actors.Num(); i++)
	{
		float Len = (Location - Actors[i]->GetActorLocation()).Size();

		if (_Range > Len)
		{
			SelectActors.Add(Actors[i]);
		}
	}

	return SelectActors;
}

// Called when the game starts or when spawned
void AURCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_AnimationInstance = Cast<UURAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr == m_AnimationInstance || false == m_AnimationInstance->IsValidLowLevel())
	{
		return;
	}

	if (m_Animations.IsEmpty())
	{
		return;
	}

	for (auto& Anim : m_Animations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}
	
	m_AnimationInstance->ChangeAnimMontage(DefaultAnimation::Idle);
}

// Called every frame
void AURCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AURCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

