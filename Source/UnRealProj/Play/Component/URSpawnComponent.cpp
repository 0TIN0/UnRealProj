// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Component/URSpawnComponent.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UURSpawnComponent::UURSpawnComponent()	:
	m_Stream(FDateTime::Now().GetTicks())	// 시드값을 랜덤하게 설정해야 랜덤한 값이 나오게되는데 여기서 시드값을 시간으로 주는것.
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UURSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	// Tick함수가 호출되는 시간이 대입된 값으로 바뀜
	// 즉 SpawnTime으로 바꿔주어 Tick에서 스폰되는 시간을 조절해주는것.
	// m_SpawnTime은 에디터 블루프린트에서 설정할 수 있다.
	PrimaryComponentTick.TickInterval = m_SpawnTime;
	// ...

	switch (m_SpawnType)
	{
	case SPAWN_TYPE::Kraken:
	case SPAWN_TYPE::Lich:
	case SPAWN_TYPE::Sparrow:
	case SPAWN_TYPE::Khaimera:
	{
		FVector vecSpawnPos = GetOwner()->GetActorLocation();

		FRotator Rot = GetOwner()->GetActorRotation();
		FTransform SpawnTransform = FTransform(Rot, vecSpawnPos);

		AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(m_SpawnActorsClass[0], SpawnTransform);
		UCapsuleComponent* CapsulComponent = NewActor->FindComponentByClass<UCapsuleComponent>();
		vecSpawnPos.Z += CapsulComponent->GetScaledCapsuleHalfHeight();
		NewActor->FinishSpawning(FTransform(Rot, vecSpawnPos));
	}
		break;
	}
	
}


// Called every frame
void UURSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if WITH_EDITOR
	DebugDraw();
#endif
	switch (m_SpawnType)
	{
	case SPAWN_TYPE::Monster:
	{
		// 예외처리
		if (0 == m_MaxCount)
		{
			return;
		}

		if (m_SpawnActorsClass.IsEmpty())
		{
			return;
		}

		if (m_SpawnActors.Num() >= m_MaxCount)
		{
			return;
		}

		for (size_t i = 0; i < m_SpawnCount; ++i)
		{
			UURGameInstance* Inst = GetWorld()->GetGameInstance<UURGameInstance>();
			FVector vecSpawnPos;

			// 범위값을 기반으로 랜덤한 float타입 값을 얻어온다.
			// 하지만 이런식으로 구성을 하면 사각형의 모양이 만들어지게 된다.
			vecSpawnPos.X = m_Stream.FRandRange(-m_SpawnRange, m_SpawnRange);
			vecSpawnPos.Y = m_Stream.FRandRange(-m_SpawnRange, m_SpawnRange);
			vecSpawnPos.Z = 0.f;

			vecSpawnPos.Normalize();

			vecSpawnPos *= m_Stream.FRandRange(0.f, m_SpawnRange);

			// 기본적으로 0을 중심으로 하고있기 때문에 스폰엑터의 위치 중심으로 바꿔줌
			vecSpawnPos += GetOwner()->GetActorLocation();

			// 스폰할 수 있는 클래스를 넣어주는데 0 ~ 클래스 개수 - 1을 넣어주어야함
			// 클래스란 Dragon1, Dragon2등등같은것
			int RandomSelect = m_Stream.RandRange(0, m_SpawnActorsClass.Num() - 1);

			FRotator Rot = FRotator();

			Rot.Yaw += m_Stream.FRandRange(0.0, 360.0);

			FTransform SpawnTransform = FTransform(Rot, vecSpawnPos);

			// 엑터타입으로 위에서 설정한 랜덤값을 스폰클래스 인덱스값으로 설정하여 해당 녀석을 스폰한다고 얻어옴
			AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(m_SpawnActorsClass[RandomSelect], SpawnTransform);

			UCapsuleComponent* CapsulComponent = NewActor->FindComponentByClass<UCapsuleComponent>();
			vecSpawnPos.Z += CapsulComponent->GetScaledCapsuleHalfHeight();
			//NewActor->SetActorRotation(Quat);
			NewActor->FinishSpawning(FTransform(Rot, vecSpawnPos));

			m_SpawnActors.Add(NewActor);

			if (m_SpawnActors.Num() >= m_MaxCount)
			{
				return;
			}
		}
	}
		break;
	case SPAWN_TYPE::Kraken:
	case SPAWN_TYPE::Lich:
		break;
	}
	
}

void UURSpawnComponent::DebugDraw()
{
	if (UURBlueprintFunctionLibrary::IsDebug())
	{
		DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), m_SpawnRange, 50, FColor::Red, false, m_SpawnTime);
	}
}

