// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Component/URSpawnComponent.h"

// Sets default values for this component's properties
UURSpawnComponent::UURSpawnComponent()	:
	m_Stream(FDateTime::Now().GetTicks())	// �õ尪�� �����ϰ� �����ؾ� ������ ���� �����ԵǴµ� ���⼭ �õ尪�� �ð����� �ִ°�.
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

	// Tick�Լ��� ȣ��Ǵ� �ð��� ���Ե� ������ �ٲ�
	// �� SpawnTime���� �ٲ��־� Tick���� �����Ǵ� �ð��� �������ִ°���.
	// m_SpawnTime�� ������ �������Ʈ���� ������ �� �ִ�.
	PrimaryComponentTick.TickInterval = m_SpawnTime;
	// ...
	
}


// Called every frame
void UURSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ����ó��
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
		FVector vecSpawnPos;

		// �������� ������� ������ floatŸ�� ���� ���´�.
		// ������ �̷������� ������ �ϸ� �簢���� ����� ��������� �ȴ�.
		vecSpawnPos.X = m_Stream.FRandRange(-m_SpawnRange, m_SpawnRange);
		vecSpawnPos.Y = m_Stream.FRandRange(-m_SpawnRange, m_SpawnRange);

		vecSpawnPos.Normalize();

		vecSpawnPos *= m_Stream.FRandRange(0.f, m_SpawnRange);

		// �⺻������ 0�� �߽����� �ϰ��ֱ� ������ ���������� ��ġ �߽����� �ٲ���
		vecSpawnPos += GetOwner()->GetActorLocation();

		// ������ �� �ִ� Ŭ������ �־��ִµ� 0 ~ Ŭ���� ���� - 1�� �־��־����
		// Ŭ������ Dragon1, Dragon2������
		int RandomSelect = m_Stream.RandRange(0, m_SpawnActorsClass.Num() - 1);

		FTransform SpawnTransform = FTransform(vecSpawnPos);

		// ����Ÿ������ ������ ������ �������� ����Ŭ���� �ε��������� �����Ͽ� �ش� �༮�� �����Ѵٰ� ����
		AActor* NewActor = GetWorld()->SpawnActorDeferred<AActor>(m_SpawnActorsClass[RandomSelect], SpawnTransform);
		NewActor->FinishSpawning(SpawnTransform);

		m_SpawnActors.Add(NewActor);

		if (m_SpawnActors.Num() >= m_MaxCount)
		{
			return;
		}
	}
}

