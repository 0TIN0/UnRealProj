// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_LightningActor.generated.h"

UCLASS()
class UNREALPROJ_API AUR_LightningActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_LightningActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	class USphereComponent* m_SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		class UParticleSystemComponent* m_FXComponent;

	const struct FURMonsterDataInfo* m_Data;

	USoundBase* m_LightningSound;

	float m_DestroyTime;

public:

private:
	UFUNCTION()
		void OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
			int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result);
};
