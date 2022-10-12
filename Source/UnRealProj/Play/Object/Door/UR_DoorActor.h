// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_DoorActor.generated.h"

UCLASS()
class UNREALPROJ_API AUR_DoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_DoorActor();

	FORCEINLINE TObjectPtr<class UStaticMeshComponent> GetDoorComponent()
	{
		return m_DoorComponent;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> m_DoorComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class UBoxComponent> m_TriggerCollision;

	bool m_Enable;
	float m_MoveTime;

private:
	UFUNCTION()
		void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
};
