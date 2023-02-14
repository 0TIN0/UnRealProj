// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_BlackHole.generated.h"

UCLASS()
class UNREALPROJ_API AUR_BlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_BlackHole();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* m_BlackHole;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_DistCollision;

	class UNiagaraSystem* m_NiagaraFX;

	class AWarriorCharacter* m_Player;

	USoundBase* m_SpawnSound;

	float m_PullDist;

	bool m_IsCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

private:
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
		int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result);

	UFUNCTION()
	void OnCollisionEnd(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
		int32 _OtherBodyIndex);
};
