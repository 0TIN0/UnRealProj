// Fill out your copyright notice in the Description page of Project Settings.


#include "URCharacter.h"
#include "Components/SphereComponent.h"
#include "Global/URGameInstance.h"
#include "URItemActor.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AURCharacter::AURCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(FName("URCharacter"));


	GetMesh()->bHiddenInSceneCapture = true;

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

bool AURCharacter::GetIsRangeInTarget(AActor* _Target, float _Length)
{
	return GetTargetDir(_Target).Size() <= _Length;
}

FVector AURCharacter::GetTargetDir(AActor* _Target)
{
	return _Target->GetActorLocation() - GetActorLocation();
}

FVector AURCharacter::GetTargetDirNormalize(AActor* _Target) 
{
	return GetTargetDir(_Target).GetSafeNormal();
}

void AURCharacter::SetTargetMovementInput(AActor* _Target, float Value)
{
	AddMovementInput(GetTargetDirNormalize(_Target), 1.0f);
}

void AURCharacter::SetTargetLook(AActor* _Target)
{
	SetActorRotation(GetTargetDirNormalize(_Target).Rotation());
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

void AURCharacter::CallDamage(double _Damage)
{
	m_HP -= _Damage;
}

TArray<FHitResult> AURCharacter::CollisionCheck(const FVector& Start, const FVector& End, const FQuat& Rot, FName ProfileName, const FCollisionShape& CollisionShape)
{
	FCollisionQueryParams CollisionCheck(FName(TEXT("Collision Check")), false, this);

	TArray<FHitResult> Result = TArray<FHitResult>();

	GetWorld()->SweepMultiByProfile(Result, Start, End, Rot, ProfileName, CollisionShape, CollisionCheck);

	return Result;
}

TArray<UActorComponent*> AURCharacter::GetDamageCollision()
{
	return GetComponentsByTag(USphereComponent::StaticClass(), FName(TEXT("Damage")));
}

void AURCharacter::ItemDrop(const TArray<const struct FURItemData*>& _Array)
{
	UURGameInstance* Instance = GetWorld()->GetGameInstance<UURGameInstance>();

	if (!Instance)
	{
		return;
	}

	TSubclassOf<AActor> Object = Instance->GetGetObjectData(FName(TEXT("Item")));

	for (size_t i = 0; i < _Array.Num(); ++i)
	{
		FTransform SpawnTransform(GetActorLocation());
		AURItemActor* NewActor = GetWorld()->SpawnActor<AURItemActor>(Object, SpawnTransform);
		NewActor->SetItem(_Array[i]);
	}
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

