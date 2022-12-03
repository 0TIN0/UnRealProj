// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_CircleActor.generated.h"

UCLASS()
class UNREALPROJ_API AUR_CircleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_CircleActor();

private:
	int m_RandomSkillNumb;
	bool m_IsCollision;
	float m_DamageTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	class USphereComponent* m_SphereComponent;

	class AURCharacter* m_Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnCollisionBegin(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
	int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result);

	UFUNCTION()
	void OnCollisionEnd(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
	int32 _OtherBodyIndex);

	void TickDamage(class AURCharacter* _Actor, float DeltaTime);


};
