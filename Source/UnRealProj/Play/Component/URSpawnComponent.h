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

private:
	// 어떤 액터를 생성할거냐?
	UPROPERTY(Category = FIDSpawner, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AActor>> m_SpawnActors;

	// 얼마만에 생성할거냐?
	UPROPERTY(Category = FidSpawner, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_SpawnTime;

	// 한번에 얼마나 만들거냐.
	UPROPERTY(Category = FidSpawner, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_SpawnCount;

	// 최대 몇마리 까지 할거냐?
	UPROPERTY(Category = FIDSpawner, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int m_MaxCount; // -1 이라면 제한 없음 계속생성

	// 원형으로 생각(원형의 범위)
	UPROPERTY(Category = FIDSpawner, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float m_SpawnRange; // 0 이면 그냥 그 위치에 생성되는거

		// 당연히 
	FRandomStream m_Stream; // 난수 생성기.
};
