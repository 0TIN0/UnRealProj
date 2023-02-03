// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_SPMuzzleFlash.generated.h"

UENUM(BlueprintType)
enum class SPMuzzle_Type : uint8
{
	Default UMETA(DisplayName = "디폴트"),
	EvadeShoot UMETA(DisplayName = "회피Shoot")
};

UCLASS()
class UNREALPROJ_API AUR_SPMuzzleFlash : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_SPMuzzleFlash();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* m_MuzzleComponent;

	class UParticleSystem* m_MuzzleFlashFX;

	SPMuzzle_Type m_MuzzleType;

	float m_DestroyTime;

public:
	void SetMuzzleType(SPMuzzle_Type _Type)
	{
		m_MuzzleType = _Type;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

};
