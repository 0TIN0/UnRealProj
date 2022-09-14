// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "URSpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UURSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UURSpawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "UR")
	void DebugDraw();

private:
	// � ���͸� �����Ұų�?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AActor>> m_SpawnActorsClass;

	// �󸶸��� �����Ұų�?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_SpawnTime;

	// �ѹ��� �󸶳� ����ų�.
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_SpawnCount;

	// �ִ� ��� ���� �Ұų�?
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_MaxCount; // -1 �̶�� ���� ���� ��ӻ���

	// �������� ����(������ ����)
	UPROPERTY(Category = "Spawner Setting", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_SpawnRange; // 0 �̸� �׳� �� ��ġ�� �����Ǵ°�

	TArray<TObjectPtr<AActor>> m_SpawnActors;

		// �翬�� 
	FRandomStream m_Stream; // ���� ������.
};
